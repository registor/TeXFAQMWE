#include <stdio.h>
#include <stdlib.h>

// 求两个数的最大值
int Max(int x, int y) /*函数头*/
{
    int z;  /*内部变量*/

    if(x > y)
    {
        z = x;
    }
    else
    {
        z = y;
    }

    return z; /*返回结果*/
}
