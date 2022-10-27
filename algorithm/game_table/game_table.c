#include<stdlib.h>
#include<math.h>
#include <stdio.h>

int **GameTable(int k) {
    int ** A = (int **) malloc(sizeof (int *)*( (int)pow(2,k)+1) );
    int i,j,t;
    for (i=1; i<=(int)pow(2,k); i++ ) {
        A[i] = (int*)malloc(sizeof(int)* ((int)pow(2,k)+1) );
    }
    int n=2;
    A[1][1]=1;
    A[1][2]=2;
    A[2][1]=2;
    A[2][2]=1;
    for (t=1; t<k; t++) {
        int temp = n;
        n *= 2;
        for (i=temp+1; i<=n; i++)
            for(j=1; j<=temp; j++)
                A[i][j] = A[i-temp][j] + temp;
        for (i=1; i<=temp; i++)
            for (j=temp+1; j<=n;j++)
                A[i][j] = A[i][j-temp]+temp;
        for (i=temp+1; i<=n; i++)
            for (j=temp+1; j<=n; j++)
                A[i][j] = A[i-temp][j-temp];
    }
    return A;
}

int main() {
    int **A = GameTable(3);
    printf("A:%p\n", A);

    return 0;
}