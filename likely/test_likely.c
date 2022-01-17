#include <stdlib.h>

/* 未使用likely或unlikely选项 */
int main(int argc, char *argv[])
{
     int i = atoi(argv[1]); /* init i with the value that GCC can't optimize */

     if (i > 0){
            i--;
    }else{
            i++;
   }

    return i;
}
