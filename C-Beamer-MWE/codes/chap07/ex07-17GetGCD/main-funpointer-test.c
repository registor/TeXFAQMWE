/*
求解两个数的最大公约数
两个数的最大公约数是指能同时整除它们的最大正整数。

求解两个数的最大公约数的一种常用算法是辗转相除法，又被称为欧几里德（Euclidean）算法。
辗转相除法首次出现于欧几里得的《几何原本》（第VII卷，命题i和ii）中，而在中国则可以追溯至东汉出现的《九章算术》。

辗转相除法的基本原理是：两个数的最大公约数等于它们中较小的数和两数之差的最大公约数，
			        既可以用除法实现，也可以用减法实现。
例如，252和105的最大公约数是21（252 = 21 × 12；105 = 21 × 5）；
	因为252 - 105 = 147，所以147和105的最大公约数也是21。
	在这个过程中，较大的数缩小了，所以继续进行同样的计算可以不断缩小这两个数直至其中一个变成零。
	这时，所剩下的还没有变成零的数就是两数的最大公约数。
	由辗转相除法也可以推出，两数的最大公约数可以用两数的整数倍相加来表示，如：
	21 = 5 × 105 + (?2) × 252。这个重要的等式叫做贝祖等式（Bézout's identity）。

两个数m，n的最大公约数记为GCD(m, n)。m，n的最大公约数是两个数的公共素数因子的乘积。如：
	462可以分解成2 × 3 × 7 × 11；1071可以分解成3 × 3 × 7 × 17。
	462和1071的最大公约数等于它们共有的素数因子的乘积3 × 7 = 21。

如果两数没有公共的素数因子，那么它们的最大公约数是1，也即这两个数互素，即GCD(m, n)=1。

另，设g=GCD(m, n)，则m=ag, n=bg，其中a，b均为正整数。
由上述分析可知，a，b互素。因为a，b没有公共素因子，GCD(a, b)=1。

除了辗转相除法外，求解两个数的最大公约数还有穷举法、递归法，二进制位运算方法等
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

// 函数原型

// 辗转相除法,  又称欧几里得算法(Euclidean algorithm)
int EuclidSubGCD(int, int); // 利用减法， while实现
int EuclidWhileGCD(int, int); // 利用求余，while实现
int EuclidForGCD(int, int); // 利用求余，for实现
int EuclidWithoutSwapGCD(int, int);  // 利用求余，不使用交换
int EuclidRecGCD(int, int); // 利用求余，递归算法

// 二进制算法
int BiGCD(int, int); // 更相减损术：出自于中国古代的《九章算术》
int BiProgArtGCD(int, int); // 《计算机编程的艺术》第二卷算法
int BiRecGCD(int, int); // 递归算法

// 穷举法
int ExhmustionIncGCD(int, int); // 递增法
int ExhmustionDecGCD(int, int); // 递减法

//// 测试函数(直接声明)
//void TestTimeConsuming(int, int, int (*)(int, int), char *); // 测试时间效率
//void TestCorrectness(int, int, int (*)(int, int), char *); // 测试正确性

// GCD函数类型重定义
typedef int(*GCDFooType)(int, int);

// 测试函数(用typedef重定义类型声明)
void TestTimeConsuming(int, int, GCDFooType, char *); // 测试时间效率
void TestCorrectness(int, int, GCDFooType, char *); // 测试正确性

// 测试数据
/*
GCD(1402580, 2203040) = 20
GCD(2, 8) = 2
GCD(7, 1) = 1
*/

int main()
{
    // 函数指针数组(直接声明)
//    int(*pGCDFoo[])(int, int) =
//    {
//        EuclidSubGCD,                   // 辗转相除法, 利用减法， while实现
//        EuclidWhileGCD,                // 辗转相除法, 利用求余，while实现
//        EuclidForGCD,                   // 辗转相除法, 利用求余，for实现
//        EuclidWithoutSwapGCD,   // 辗转相除法, 利用求余，不使用交换
//        EuclidRecGCD,                  // 辗转相除法, 利用求余，递归算法
//        BiGCD,                              // 二进制算法，更相减损术：出自于中国古代的《九章算术》
//        BiProgArtGCD,                  // 二进制算法，《计算机编程的艺术》第二卷算法
//        BiRecGCD,                        // 二进制算法，递归算法
//        ExhmustionIncGCD,          // 穷举法，递增
//        ExhmustionDecGCD,         // 穷举法，递减
//        NULL
//    };

    // 函数指针数组(用typedef重定义类型声明)
    GCDFooType pGCDFoo[] =
    {
        EuclidSubGCD,                   // 辗转相除法, 利用减法， while实现
        EuclidWhileGCD,                // 辗转相除法, 利用求余，while实现
        EuclidForGCD,                   // 辗转相除法, 利用求余，for实现
        EuclidWithoutSwapGCD,   // 辗转相除法, 利用求余，不使用交换
        EuclidRecGCD,                  // 辗转相除法, 利用求余，递归算法
        BiGCD,                              // 二进制算法，更相减损术：出自于中国古代的《九章算术》
        BiProgArtGCD,                  // 二进制算法，《计算机编程的艺术》第二卷算法
        BiRecGCD,                        // 二进制算法，递归算法
        ExhmustionIncGCD,          // 穷举法，递增
        ExhmustionDecGCD,         // 穷举法，递减
        NULL
    };

    // 函数名称数组
    char *pGCDName[] =
    {
        "01. EuclidSubGCD",                   // 辗转相除法, 利用减法， while实现
        "02. EuclidWhileGCD",                // 辗转相除法, 利用求余，while实现
        "03. EuclidForGCD",                   // 辗转相除法, 利用求余，for实现
        "04. EuclidWithoutSwapGCD",   // 辗转相除法, 利用求余，不使用交换
        "05. EuclidRecGCD",                  // 辗转相除法, 利用求余，递归算法
        "06. BiGCD",                              // 二进制算法，更相减损术：出自于中国古代的《九章算术》
        "07. BiProgArtGCD",                  // 二进制算法，《计算机编程的艺术》第二卷算法
        "08. BiRecGCD",                        // 二进制算法，递归算法
        "09. ExhmustionIncGCD",          // 穷举法，递增
        "10. ExhmustionDecGCD",         // 穷举法，递减
        NULL
    };

    int x, y;
    int i;

    // 随机数测试算法正确性
    // 置随机种子
    srand( (unsigned)time( NULL ) );

    // 要取[a,b)之间的随机整数（包括a，但不包括b)，使用：
    // (rand() % (b - a)) + a
    x = rand() % (50000 + 1);
    y = rand() % (50000 + 1);

//    // 测试正确性
//    i = 0;
//    while(pGCDFoo[i] != NULL)
//    {
//        TestCorrectness(x, y, pGCDFoo[i], pGCDName[i]);
//        i++;
//    }

    // 测试时间效率
    i = 0;
    while(pGCDFoo[i] != NULL)
    {
        TestTimeConsuming(x, y, pGCDFoo[i], pGCDName[i]);
        i++;
    }

    return 0;
}

// 函数定义

// 测试正确性
void TestCorrectness(int m, int n, int (*pf)(int, int), char *pfn)
{
    int gcd;

    gcd = pf(m, n);

    printf("%s(%d, %d) = %d\n", pfn, m, n, gcd);
}

// 测试时间效率
void TestTimeConsuming(int m, int n, int (*pf)(int, int), char *pfn)
{
    int i;
    int gcd;
    clock_t start;  // 开始时间
    clock_t end; // 结束时间
    double duration = 0.0; // 程序执行时间，单位秒

    // 测试结果
    // 基准时间(基本while辗转相除法)
    start = clock();
    for(i = 0; i < N; i++)
    {
        pf(m, n);
    }
    end = clock();

    //CLOCKS_PER_SEC是一个常数，表示机器时钟每秒所使用的CPU时钟单元
    duration = (double)(end - start) / CLOCKS_PER_SEC;

    gcd = pf(m, n);

    printf("%s(%d, %d) = %d, consuming time =  %lfs\n", pfn, m, n, gcd, duration);
}

//  用减法实现辗转相除法
/*
设有两个整数m和n：
    ① 若m>n，则m=m-n
    ② 若m<n，则n=n-m
    ③ 若m==n，则m(或n)即为两数的最大公约数
    ④ 若m≠n，则再回去执行①

例如： 有两个数12 18, 它们的最大公约数为6
	12 = 6 * m---12肯定是它最大公约数的倍数
	18 = 6 * n---18也肯定是它最大公约数的倍数
	18 - 12 = 6 *(n - m)---由结果可看出它们的差值肯定也是最大公约数的倍数
	12 - 6 = 6 ---直到减数和差值相同时, 则这个相同的数就是它们的最大公约数。
*/
int EuclidSubGCD(int m, int n)
{
    while (1)
    {
        // 大数减小数
        if (m > n)
        {
            m -= n;
        }
        else if(m < n)
        {
            n -= m;
        }
        else // 相等则是GCD
        {
            return m; // 利用return退出循环
        }
    }
}

// 用求余实现辗转相除法，while实现
/*
设有两个整数m和n：
    ① 求两个数m和n的余数rem；
    ② 若余数rem为0，则较小数即为最大公约数；否则执行③；
    ③ 用较小的数替换较大的数，用余数rem替换较小的数；
    ④ 返回① .
*/
int EuclidWhileGCD(int m, int n)
{
    int rem = n;

    while (rem != 0)
    {
        rem = m % n;
        m = n;
        n = rem;
    }

    return m;
}

// 用求余实现辗转相除法，for实现
/*
设有两个整数m和n：
    ① 求两个数m和n的余数rem；
    ② 若余数rem为0，则较小数即为最大公约数；否则执行③；
    ③ 用较小的数替换较大的数，用余数rem替换较小的数；
    ④ 返回① .
*/
int EuclidForGCD(int m, int n)
{
    int rem;

    for(rem = m % n; rem != 0; rem = m % n)
    {
        m = n;
        n = rem;
    }

    return n;
}

// 用求余实现辗转相除法，不交换
/*
设有两个整数m和n：
    ① 求两个数m和n的余数rem；
    ② 若余数rem为0，则较小数即为最大公约数；否则执行③；
    ③ 用较小的数替换较大的数，用余数rem替换较小的数；
    ④ 返回① .
*/
int EuclidWithoutSwapGCD(int m, int n)
{
    // 两个整数相等直接返回m
    if(m == n)
    {
        return m;
    }

    while ((m * n) != 0)// 当其中一个为0时, 终止循环
    {
        if (m > n) // 辗转相除, 直到两个数相等
        {
            m %= n;
        }
        else if(m < n)
        {
            n %= m;
        }
        else
        {
            break; // 两个数相等，跳出循环。
        }
    }
    return m > n ? m : n;
}


// 用求余实现辗转相除法，递归求解
/*
设有两个整数m和n：
    ① 求两个数m和n的余数rem；
    ② 若余数rem为0，则较小数即为最大公约数；否则执行③；
    ③ 用较小的数替换较大的数，用余数rem替换较小的数；
    ④ 返回① .
*/
int EuclidRecGCD(int m, int n)
{
    return n == 0 ? m : EuclidRecGCD(n, m % n);
}

// 更相减损术，源自《九章算术》
/*?
东汉出现的《九章算术》中的“更相减损术”可以用来求两个数的最大公约数，其原文是：
    可半者半之，不可半者，副置分母、子之数，以少减多，更相减损，求其等也。以等数约之。
白话文译文：
    （如果需要对分数进行约分，那么）可以折半的话，就折半（也就是用2来约分）。
    如果不可以折半的话，那么就比较分母和分子的大小，用大数减去小数，互相减来减去，
    一直到减数与差相等为止，用这个相等的数字来约分。

根据最大公约数的特点可知更相减损术基基本原理为：
    对于m和n来说，如果m=k * m1，n=k * n1。那么有GCD(m,  n)=k * GCD(m1, n1)。
    另外，如果m = p * m1，并且p是素数，同时n % p != 0(即n不能被p整除)，那么：
    GCD(m, n)=GCD(p * m1, n)= GCD(m1, n)。

注意到这两点后，就可以利用这两点对算法进行改进。
众所周知，2是一个素数，同时对于二进制表示的大整数而言，可以很容易地将除以2和乘以2的运算转换成移位运算，
从而避免大整数除法，由此就可以利用2这个数字来进行最大公约数计算。取p = 2，则：
	若m, n均为偶数，GCD(m, n)= 2 *GCD(m/2, n/2)= 2 * GCD(m>>1, n>>1)
	若m为偶数，n为奇数，GCD(m, n)=GCD(m/2, n)= GCD(m>>1, n)
	若m为奇数，n为偶数，GCD(m, n)= GCD(m,n/2)= GCD(m, n>>1)
	若m, n均为奇数，GCD(m, n)= GCD(m, m -n)，
	那么在GCD(m, n)= GCD(m, m - n)之后，(m - n)是一个偶数，下一步一定会有除以2的操作。

显然，使用位运算可以提高算法的执行效率。
*/
int BiGCD(int m, int n)
{
    int i, j;

    // 有一个0, 直接返回另一个数
    if(m == 0)
    {
        return n;
    }
    if(n == 0)
    {
        return m;
    }

    // 利用& 0x01判断是不是偶数
    for(i = 0; (m & 0x01) == 0; ++i)
    {
        m >>= 1; // m / 2
    }
    for(j = 0; (n & 0x01) == 0; ++j)
    {
        n >>= 1; // n / 2
    }

    // 不同时为偶数时，除2的次数
    if(j < i)
    {
        i = j;
    }

    while(1)
    {
        // 如果第1个比第2个数小, 交换两个数(用异或位运算实现)
        if(m < n)
        {
            m ^= n;
            n ^= m;
            m ^= n;
        }

        // 更相减损术
        if((m -= n) == 0)
        {
            // n * 2的i次方
            return n << i;
        }

        // 判断是不是偶数
        while((m & 0x01) == 0)
        {
            m >>= 1; // m / 2
        }
    }
}

// 二进制迭代算法(《计算机编程的艺术》第二卷算法)
/*?先用移位的方式对两个数除2,
	直到两个数不同时为偶数。
	然后将剩下的偶数(如果有的话)做同样的操作,
	这样做的原因是如果m和n中m为偶数, n为奇数,
	则有GCD(m, n)=GCD(m / 2, n)。
	到这时, 两个数都是奇数,
	将两个数相减得到偶数t(因为GCD(m, n) = GCD(n, m - n)，更相减损术。),
	对t移位直到t为奇数。
	每次将最大的数用t替换。
*/
int BiProgArtGCD(int m, int n)
{
    // 若为负数则变成正数
    m = (m < 0) ? -m : m;
    n = (n < 0) ? -n : n;

    // 若有一个数为0, 则另一个数为最大公约数
    if(m == 0)
    {
        return n;
    }
    if(n == 0)
    {
        return m;
    }

    int k = 0; // 记数

    // 通过右移1位除2, 直到两个数不同时为偶数。
    while((m & 0x01) == 0 && (n & 0x01) == 0)
    {
        // 除?2??
        m >>= 1;
        n >>= 1;
        k++;
    }

    // 此时, 仅有一个奇数
    int t = -n; // 初始化为负数, 以便后续比较(t>0)??
    if((n & 0x01) == 1) // n奇数
    {
        t = m;
    }

    // t 可能是一个偶数
    while(t != 0)
    {
        while((t & 0x01) == 0)
        {
            // 除 2 直到t不是偶数
            t >>= 1;
        }
        if(t > 0)
        {
            // m?>?n?(大数用|t|代替)
            m = t;
        }
        else
        {
            // m< n?(大数用|t|代替)
            n = -t;
        }
        // 此时 m?和?n?都是奇数, 则?m - n?是偶数(更相减损法)
        t = m - n;
    }
    // 移位2的k次方
    return m * (1 << k);
}

// 结合辗转相除法和更相减损术以及移位运算的递归算法
/*
****众所周知, 按位异或、移位运算等位运算的性能非常快。****
根据最大公约数的特点可知更相减损术基基本原理为：
	对于m和n来说，如果m=k * m1，n=k * n1。那么有GCD(m,  n)=k * GCD(m1, n1)。
	另外，如果m = p * m1，并且p是素数，同时n % p != 0(即n不能被p整除)，那么：
	GCD(m, n)=GCD(p * m1, n)= GCD(m1, n)。

注意到这两点后，就可以利用这两点对算法进行改进。
众所周知，2是一个素数，同时对于二进制表示的大整数而言，可以很容易地将除以2和乘以2的运算转换成移位运算，
从而避免大整数除法，由此就可以利用2这个数字来进行最大公约数计算。取p = 2，则：
	若m, n均为偶数，GCD(m, n)= 2 *GCD(m/2, n/2)= 2 * GCD(m>>1, n>>1)
	若m为偶数，n为奇数，GCD(m, n)=GCD(m/2, n)= GCD(m>>1, n)
	若m为奇数，n为偶数，GCD(m, n)= GCD(m,n/2)= GCD(m, n>>1)
	若m, n均为奇数，GCD(m, n)= GCD(m, m -n)，
	那么在GCD(m, n)= GCD(m, m - n)之后，(m - n)是一个偶数，下一步一定会有除以2的操作。

在两数比较小时, 暂时看不出计算次数的优势,
当两数越大时, 计算次数的节省就越明显。
*/
int BiRecGCD(int m, int n)
{
    if (m == n)
    {
        return m;
    }

    if (m < n) // 确保大数在前
    {
        return BiRecGCD(n, m);
    }
    else
    {
        // 与1按位与用于判断奇偶
        if (!(m & 0x01) && !(n & 0x01)) // 都是偶数
        {
            // 右移1位相当除2, 左移1位相当乘2
            return BiRecGCD(m >> 1, n >> 1) << 1;
        }
        else if(!(m & 0x01) && (n & 0x01)) // m为偶数, n为奇数
        {
            return BiRecGCD(m >> 1, n);
        }
        else if((m & 0x01) && !(n & 0x01)) // m为奇数, n为偶数
        {
            return BiRecGCD(m, n >> 1);
        }
        else // 当两个数都为奇数时, 应用更相减损法
        {
            return BiRecGCD(n, m - n);
        }
    }
}


// 穷举法，递增实现
/*
设有两个整数m和n：
    ① i=1
    ② 若m，n能同时被i整除，则t＝i
    ③ i++
    ④ 若 i <= m(或n)，则再回去执行②
    ⑤ 若 i > m(或n)，则t即为最大公约数，结束
*/
int ExhmustionIncGCD(int m, int n)
{
    int i, t = 1;

    for(i = 1; i <= m; i++)
    {
        if ( m % i == 0 && n % i == 0 )
        {
            t = i;
        }
    }

    return t;
}

// 穷举法， 递减实现
/*
设有两个整数m和n：
    ① t= m(或n)
    ② 若m，n能同时被i整除，则t即为最大公约数，结束
    ③ t--，再回去执行②
*/
int ExhmustionDecGCD(int m, int n)
{
    int t;

    // 如果第1个比第2个数小, 交换两个数(用异或位运算实现)
    if(m < n)
    {
        m ^= n;
        n ^= m;
        m ^= n;
    }

    for(t = n; m % t || n % t; t--)
    {
        ; // 空循环实现操作
    }

    return t;
}
