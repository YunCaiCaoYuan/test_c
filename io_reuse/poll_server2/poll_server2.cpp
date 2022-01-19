#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>
#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include <map>
#include <string>

using namespace std;

#define BUFSIZE 10
#define CLIENTSIZE 1

// fixme：找不到POLLRDHUP， MacOS不支持

int createSocket()
{
    struct sockaddr_in servaddr;
    int listenfd = -1;

    if (-1 == (listenfd = socket(PF_INET, SOCK_STREAM, 0)))
    {
        fprintf(stderr, "socket: %d, %s\n", errno, strerror(errno));
        exit(1);
    }

    int reuseaddr = 1;
    if (-1 == setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr)))
    {
        fprintf(stderr, "setsockopt: %d, %s\n", errno, strerror(errno));
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = PF_INET;
    servaddr.sin_port = htons(8008);
    inet_pton(PF_INET, "0.0.0.0", &servaddr.sin_addr);

    if (-1 == bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)))
    {
        fprintf(stderr, "bind: %d, %s\n", errno, strerror(errno));
        exit(1);
    }

    if (-1 == listen(listenfd, 5))
    {
        fprintf(stderr, "listen: %d, %s\n", errno, strerror(errno));
        exit(1);
    }

    return listenfd;
}

int setnoblock(int fd)
{
    int oldopt = fcntl(fd, F_GETFL);
    int newopt = oldopt | O_NONBLOCK;
    fcntl(fd, F_SETFL, newopt);
    return oldopt;
}

int main()
{
    struct pollfd fds[CLIENTSIZE];
    int listenfd = createSocket();

    map<int, string> mapdata;

    fds[0].fd = listenfd;
    fds[0].events = POLLIN | POLLERR;
    fds[0].revents = 0;
    int conncount = 0;

    while (1)
    {
        int ret = poll(fds, conncount + 1, -1);
        if (ret < 0)
        {
            fprintf(stderr, "poll: %d, %s\n", errno, strerror(errno));
            exit(1);
        }

        for (int i = 0; i < conncount + 1; i++)
        {
            // 客户端关闭，或者错误。错误的原因是由于客户端关闭导致的，这里一并处理
            if ((fds[i].revents & POLLHUP) || (fds[i].revents & POLLERR))
            {
                int fd = fds[i].fd;
                fds[i] = fds[conncount];
                i--;
                conncount--;
                mapdata.erase(fd);
                close(fd);
                printf("delete connection: %d\n", fd);
            }
            // 新的连接
            else if ((fds[i].fd == listenfd) && (fds[i].revents & POLLIN))
            {
                struct sockaddr_in client;
                socklen_t lenaddr = sizeof(client);
                int conn = -1;

                if (-1 == (conn = accept(listenfd, (struct sockaddr*)&client, &lenaddr)))
                {
                    fprintf(stderr, "accept: %d, %s\n", errno, strerror(errno));
                    exit(1);
                }
                printf("get connection %d from %s:%d\n", conn, inet_ntoa(client.sin_addr), client.sin_port);
                conncount++;
                setnoblock(conn);
                fds[conncount].fd = conn;
                fds[conncount].events = POLLIN | POLLHUP | POLLERR;
                fds[conncount].revents = 0;
            }
            // 有可读数据
            else if (fds[i].revents & POLLIN)
            {
                char buf[BUFSIZE] = {0};

                int lenrecv = recv(fds[i].fd, buf, BUFSIZE-1, 0);
                if (lenrecv > 0)
                {
                    mapdata[fds[i].fd] = buf;
                    fds[i].events &= (~POLLIN);
                    fds[i].events |= POLLOUT;
                }
                else if (lenrecv == 0)
                {
                    printf("------- client %d exit (not print) --------\n", fds[i].fd);
                }
                else
                {
                    fprintf(stderr, "recv: %d, %s\n", errno, strerror(errno));
                    exit(1);
                }
            }
            // 可写数据
            else if (fds[i].revents & POLLOUT)
            {
                if (send(fds[i].fd, mapdata[fds[i].fd].c_str(), mapdata[fds[i].fd].size(), 0) < 0)
                {
                    if (ECONNRESET == errno)
                    {
                        continue;
                    }
                    fprintf(stderr, "send: %d, %s\n", errno, strerror(errno));
                    exit(1);
                }
                fds[i].events &= (~POLLOUT);
                fds[i].events |= POLLIN;
            }
        }
    }
}