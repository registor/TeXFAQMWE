// 递归计算n!
int Fact(int n)
{
    // 简单情况
    if(n <= 1)
        return 1;
    else
        //递归调用，分而治之
        return n * Fact(n - 1);
}
