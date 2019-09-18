// 功能：用于整数的比较小于函数
int GreaterInt(const void *a, const void *b)
{
    return (*(int*)a > *(int*)b) ? 1 : 0;
}
// 功能：用于整数的比较小于函数
int LesserInt(const void *a, const void *b)
{
    return (*(int*)b > * (int*)a) ? 1 : 0;
}
// 功能：用于浮点数的比较大于函数
int GreaterDf(const void *a, const void *b)
{
    return (*(double*)a > * (double*)b) ? 1 : 0;
}
// 功能：用于浮点数的比较小于函数
int LesserDf(const void *a, const void *b)
{
    return (*(double*)b > * (double*)a) ? 1 : 0;
}
