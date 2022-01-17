#include "b.h"
// a.c
extern int shared;

int main()
{
    int a = 100;
    swap(&a, &shared);
}
