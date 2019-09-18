#include <stdio.h>
#include <stdlib.h>

int gval1, gscale; // 全局变量
void swap(int *, int *);

int main(void)
{
    int a = 10, b = 20; // 局部变量

    int *p = (int *)malloc(10*sizeof(int));    

    swap(&a, &b); 

    free(p);

    return 0;
}

void swap(int * px, int *py)
{
    int temp; // 临时变量
    temp = *px;
    *px = *py;
    *py = temp;
}
