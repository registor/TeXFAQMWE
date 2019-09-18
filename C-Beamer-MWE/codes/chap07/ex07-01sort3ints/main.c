#include <stdio.h>
#include <stdlib.h>

// 函数原型
void Swap(int*, int*);
void Sort(int*, int*, int*);

int main()
{
    int iVal1, iVal2, iVal3; // 声明变量

    // 输入数据
    scanf("%d%d%d", &iVal1, &iVal2, &iVal3);
    printf("before: %d %d %d", iVal1, iVal2, iVal3);

    // 排序
    Sort(&iVal1, &iVal2, &iVal3);

    // 输出数据
    printf("after: %d %d %d", iVal1, iVal2, iVal3);
    return 0;
}

// 交换两个数
void Swap(int *pa, int *pb)
{
    int temp;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}
// 对3个整型数进行排序
void Sort(int *pa, int *pb, int *pc)
{
    // 交换a和b的值
    if(*pa < *pb)
    {
        Swap(pa, pb);
    }
    // 交换a和c的值
    if(*pa < *pc)
    {
        Swap(pa, pc);
    }
    // 交换b和c的值
    if(*pb < *pc)
    {
        Swap(pb, pc);
    }
}
