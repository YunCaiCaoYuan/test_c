#include "stdio.h"

int main() {
    int sz = sizeof(unsigned long);
    printf("sz：%d\n", sz); // sz：8
    int sz2 = sizeof(long);
    printf("sz2：%d", sz2); // sz2：8
}
