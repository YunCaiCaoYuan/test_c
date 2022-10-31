#include<stdlib.h>
#include<math.h>
#include<stdio.h>

int **Matrix_Chain_Order(int *p, int Length) {
    int Multip_times = Length-1;
    int ** m = (int **)malloc(sizeof(int *)*Length);
    int ** s = (int **)malloc(sizeof(int *)*Length);
    int i;
    for (i=0; i<Length; i++) {
        m[i]=(int*) malloc(sizeof(int)*Length);
        s[i]=(int*) malloc(sizeof(int)*Length);
    }
    for(i=1;i<Multip_times;i++)
        m[i][i]=0;

    int l;
    for(l=2;l<=Multip_times;l++){
        for(i=1;i<=Multip_times-l+1;i++){
            int j =i+l-1;
            m[i][j]=INT_MAX;
            int k;
            for(k=i;k<j;k++){
                int q = m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                if(q<m[i][j]) {
                    m[i][j]=q;
                    s[i][j]=k;
                }
            }
        }
    }
    return s;
}

void Print_Optimal_Parens(int **s, int i, int j) {
    if (i==j){
        printf("A%d", i);
    } else {
        printf("(");
        Print_Optimal_Parens(s,i,s[i][j]);
        Print_Optimal_Parens(s,s[i][j]+1,j);
        printf(")");
    }
}

int main() {
    const int Length = 7;
    int p[7]={30,35,15,5,10,20,25};
    int **s = Matrix_Chain_Order(p, Length);
    Print_Optimal_Parens(s, 1,6);
    return 0;
}