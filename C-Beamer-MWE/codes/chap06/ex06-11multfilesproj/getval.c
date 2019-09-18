#include "getval.h"

// 使用函数指针得到最大或最小值
int GetVal(int x, int y, int (*pf)(int, int))
{
    return pf(x, y); /*调用传入的函数*/
}

