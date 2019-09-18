    pf = Min; /*指向Min函数*/
    c = (*pf)(a, b); /*调用函数*/
    printf("Min=%d\n", c);

    return 0;
}
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
