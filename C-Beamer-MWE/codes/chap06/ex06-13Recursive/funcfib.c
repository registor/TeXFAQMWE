// 求n阶费波那契数列
int Fib(int n)
{
    if(n < 2)
        return n;
    else
        return Fib(n - 1) + Fib(n - 2);
}
