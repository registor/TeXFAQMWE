// 函数定义
int isPrime(int n)
{
    int divisor;
    // 小于1的数不是素数
    if ( n <= 1)
    {
        return 0;
    }
    // 只需要检索到sqrt(n)即可，
    // divisor * divisor <= n
    //是为了避免浮点数运算
    for(divisor = 2; 
        divisor * divisor <= n;
        divisor++)
    {
        // 发现整除则不是素数
        if(n % divisor == 0) 
        {
            return 0;
        }
    }
    return 1;
}
