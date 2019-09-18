// 求两个数的最大值
int Max(int x, int y) /*函数头*/
{
    return x > y ? x : y;
}

// 求两个数的最小值
int Min(int x, int y) /*函数头*/
{
    return x < y ? x : y;
}

// 使用函数指针得到最大或最小值
int GetVal(int x, int y, int (*pf)(int, int))
{
    return pf(x, y); /*调用传入的函数*/
}

