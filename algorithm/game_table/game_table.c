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
    for (int i=1;i<=pow(2,3); i++)
    {
        for (int j=1; j<= pow(2,3); j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
    return 0;
}

/*
1 2 3 4 5 6 7 8
2 1 4 3 6 5 8 7
3 4 1 2 7 8 5 6
4 3 2 1 8 7 6 5
5 6 7 8 1 2 3 4
6 5 8 7 2 1 4 3
7 8 5 6 3 4 1 2
8 7 6 5 4 3 2 1
*/