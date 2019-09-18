#include <stdio.h>
#include <stdlib.h>

// 函数原型
int CalcPiece(int);

int main()
{
    int iV;
    int iY;

    scanf("%d", &iV);

    // 调用函数
    iY = CalcPiece(iV);

    printf("y = %d\n", iY);

    return 0;
}
