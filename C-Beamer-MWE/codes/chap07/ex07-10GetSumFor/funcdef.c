// 函数定义
int GetSum(int n)
{
    int i = 0; // 循环变量
    int sum = 0; // 累加器

    for(i = 0; i < n; i++)
    {
        sum += (i + 1); // 注意i + 1
    }

    return sum;
}
