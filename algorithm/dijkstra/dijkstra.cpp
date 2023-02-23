#include <cstdio>

#define MAX 1000000

using namespace std;

int arcs[10][10]={
        {1000000,1000000,10,1000000,30,100},
        {1000000,1000000,5,1000000,1000000,1000000},
        {1000000,1000000,1000000,50,1000000,1000000},
        {1000000,1000000,1000000,1000000,1000000,10},
        {1000000,1000000,1000000,20,1000000,60},
        {1000000,1000000,1000000,1000000,1000000,1000000},
};
int D[10];
int p[10][10];
int final[10];
int n = 6; // 代表点数
int v0 = 0;
int v,w;

// 最短路径（实质是动态规划）
void ShortestPath_DIJ() {
    for (v=0; v<n;v++)
    {
        final[v]=0;
        D[v]=arcs[v0][v];
        for (w=0; w<n; w++)
            p[v][w]=0;
        if (D[v]<MAX)
        {
            p[v][v0]=1;
            p[v][v]=1;
        }
    }
    D[v0]=0;
    final[v0]=1;
    for (int i=1; i<n; i++)
    {
        int min=MAX;
        for(w=0;w<n;w++)
        {
            if(!final[w])
            {
                if (D[w]<min) {
                    v=w;
                    min=D[w];
                }
            }
        }
        final[v]=1;
        for (w=0; w<n; w++){
            if (!final[w] && (min+arcs[v][w]<D[w]))
            {
                D[w]=min+arcs[v][w];
                p[w][w]=1;
            }
        }
    }

}

// 输出最短路径？？？

int main() {
    ShortestPath_DIJ();
    for (int i=0; i<n; i++)
    {
        printf("D[%d]=%d\n", i, D[i]);
    }
    return 0;
}

