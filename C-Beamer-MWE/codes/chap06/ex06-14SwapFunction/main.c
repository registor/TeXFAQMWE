#include <stdio.h>
#include <stdlib.h>

// 函数原型
void SwapWithTemp(int *, int *); // 通过中间变量交换两个数
void SwapWithAddMinus(int *, int *); // 通过加减交换两个数
void SwapWithMulDiv(int *, int *); // 通过乘除交换两个数
void SwapWithXor(int *, int *); // 通过异或操作交换两个数

int main()
{
    int a = 10, b = 20;
    printf("Orig: %d, %d\n", a, b);

    SwapWithTemp(&a, &b);
    printf("WithTemp: %d, %d\n",  a, b);
    SwapWithAddMinus(&a, &b);
    printf("WithAddMinus: %d, %d\n", a, b );
    SwapWithMulDiv(&a, &b);
    printf("WithMulDiv: %d, %d\n",  a, b);
    SwapWithXor(&a, &b);
    printf("WithXor: %d, %d\n",  a, b);
    return 0;
}

void SwapWithTemp(int *pa, int *pb) // 通过中间变量交换两个数
{
    int temp;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void SwapWithAddMinus(int *pa, int *pb) // 通过加减交换两个数
{
    *pa = *pa + *pb;
    *pb = *pa - *pb;
    *pa = *pa - *pb;
}
void SwapWithMulDiv(int *pa, int *pb) // 通过乘除交换两个数
{
    *pa = *pa * *pb;
    *pb = *pa / *pb;
    *pa = *pa / *pb;
}
void SwapWithXor(int *pa, int *pb) // 通过异或操作交换两个数
{
    *pa ^= *pb;
    *pb ^= *pa;
    *pa ^= *pb;
}


