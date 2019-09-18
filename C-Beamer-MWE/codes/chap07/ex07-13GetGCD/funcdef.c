// 求两个正整数的最大公约数
int GetGCD(int m, int n)
{
    int r; // 余数

    // 如果m<n，则交换m和n的值
    if(m < n)
    {
        m ^= n;//采用异或处理
        n ^= m;//只能交换整数
        m ^= n;
    }

    // 辗转相除法
    while(n != 0)
    {
        r = m % n;
        m = n;
        n = r;
    }

    return m;
}
