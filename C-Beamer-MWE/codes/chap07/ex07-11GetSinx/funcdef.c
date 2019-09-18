// 函数定义
double GetSinx(double x)
{
    double sum = x;  // 计算结果
    double x_pow = x; // x的幂
    double item = 0.0; // 累加项
    int n = 1; // 计数
    long long int fact = 1; // 阶乘
    int sign = 1; // 符号
    do
    {
        // 计算阶乘，作分母
        fact = fact * (n + 1) * (n + 2);
        // x_pow是x的幂，作分子
        x_pow *= x * x;
        // 当前项的符号
        sign = -sign;
        // 计算当前累加项
        item =  sign * x_pow / fact;
        // 累加
        sum += item;
        // 递增
        n += 2;
    }while(fabs(item) > epsilon);
    return sum;
}
