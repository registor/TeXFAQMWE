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

// 函数定义
int CalcPiece(int x)
{
    int result;

    if(x != 0)
    {
        if(x > 0)
        {
            result = 1;
        }
        else
        {
            result = -1;
        }
    }
    else
    {
        result = 0;
    }

    return result;
}
