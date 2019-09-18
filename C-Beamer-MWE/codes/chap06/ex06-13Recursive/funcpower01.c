int Power(int x, int n)
{
    // 简单情况
    if(n == 0)
        return 1;
    else
        //递归调用，分而治之
        return x * Power(x, n - 1);
}
