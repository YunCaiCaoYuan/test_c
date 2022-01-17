#include <stdlib.h>

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

int main(int argc, char *argv[])
{
         int i = atoi(argv[1]); /* init i with the value that GCC can't optimize */

         if (likely(i > 0)){
                 i--;
         }else{
                 i++;
         }

         return i;
 }
