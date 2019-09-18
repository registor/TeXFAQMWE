#include <stdio.h>
#include <stdlib.h>

// 函数原型
void Swap(int*, int*);
void Sort(int*, int*, int*);

int main()
{
    int iVal1, iVal2, iVal3; 

    scanf("%d%d%d", 
           &iVal1, &iVal2, &iVal3);
    printf("before: %d %d %d", 
            iVal1, iVal2, iVal3);

    Sort(&iVal1, &iVal2, &iVal3);

    printf("after: %d %d %d", 
            iVal1, iVal2, iVal3);
    return 0;
}
