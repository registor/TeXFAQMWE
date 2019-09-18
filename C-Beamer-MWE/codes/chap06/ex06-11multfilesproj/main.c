#include <stdio.h>
#include <stdlib.h>

#include "getmax.h"
#include "getmin.h"
#include "getval.h"

//主函数
int main()
{
    /*声明变量并初始化*/
    int a = 10, b = 20;
    int c;

    c = GetVal(a, b, Max);
    printf("Max=%d\n", c);

    c = GetVal(a, b, Min);
    printf("Min=%d\n", c);

    return 0;
}

