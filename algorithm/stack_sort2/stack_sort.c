#include "stdio.h"

#define MAXITEM 100

void Heapify(int R[MAXITEM], int v, int n) {
    int i, j;
    i = v;
    j = 2 * i;
    R[0] = R[i];
    while (j <= n) {
        if (j < n && R[j] < R[j + 1]) {
            j++;
        }
        if (R[i] < R[j]) { // 1
            R[i] = R[j];
            i = j;
            j = 2 * i;
        } else {
            j = n + 1;
        }
        R[i] = R[0];
    }
}

void HeapSort(int R[MAXITEM], int n) {
    int i;
    for (i = n / 2; i >= 1; i--) {
        Heapify(R, i, n); // 2
    }
    for (i = n; i > 1; i--) { // 3
        R[0] = R[i];
        R[i] = R[1];
        R[1] = R[0]; // 4
        Heapify(R, 1, i - 1);
    }
}

int main() {
    int arr[] = {9, 5, 6, 3, 5, 3, 1, 0, 96, 66};
    HeapSort(arr, sizeof(arr) / sizeof(arr[0]));
    printf("排序后为：");
    for (int i = 1; i < sizeof(arr) / sizeof(arr[0]); i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}

// 排序后为：0 1 3 3 5 5 6 66 96