#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// �궨��
#define EPSILON 1e-6

// ��������
double GetPower(double, int); // �۳�����
double GetRootBi(double, int); // ���ַ��󿪷�
double GetRootNewton(double, int); // ţ�ٷ��󿪷�

float InvSqrt(float); // Լ����������������Ŀ��ټ���ƽ�����ĵ���

unsigned int GetFact(unsigned int); // ���˷���׳�

// ��������ֻ�������
int main()
{
    double r, x;
    int n;

    x = 4.0;
    n = 2;

    // �����۳����ݺ���
    r = GetPower(x, n);
    printf("%f^%d=%f\n", x, n, r);

    // ���Զ��ַ��󿪷�����
    r = GetRootBi(x, n);
    printf("root^%d(%f)=%f\n", n, x, r);

    // ����ţ�ٷ��󿪷�����
    r = GetRootNewton(x, n);
    printf("root^%d(%f)=%f\n", n, x, r);

    // ����������׳˺���
    n = 10;
    printf("InvSqrt = %f\n", InvSqrt(n));
    printf("pow = %f\n", pow(n, -0.5));

    // ����Լ����������������Ŀ��ټ���ƽ�����ĵ���

    return 0;
}

// ��������

// �۳����ݺ���
double GetPower(double x, int n)
{
    double result = 1.0;

    int i;

    for(i = 0; i < n; i++)
    {
        result *= x;
    }

    return result;
}

// ���ַ��󿪷�����
double GetRootBi(double x, int n)
{
    // �ߵͽ�
    double low = x > 1.0 ? 1.0 : x;
    double high = x >= 1.0 ? x : 1.0;

    // ������ֵ
    double mid = (low + high) / 2.0;

    // ��ֵ��n����
    double f = GetPower(mid, n);

    // ѭ��
    while(fabs(f - x) > EPSILON)
    {
        if(f > x)
        {
            high = mid; // ��x����ȥ�߶�
        }
        else
        {
            low = mid; // ��xС����ȥ�Ͷ�
        }
        mid = (low + high) / 2.0; // �۰�

        f = GetPower(mid, n); // ��ֵ��n����
    }

    return mid;
}

// ţ�ٷ��󿪷�����
double GetRootNewton(double x, int n)
{
    // ��ֵ
    double x_n = x;
    // ����
    double f = GetPower(x_n, n) - x;

    // ���ݾ��ȿ���ѭ��
    while(fabs(f) > EPSILON)
    {

        // ԭ������ǰֵ
        double fx_n = GetPower(x_n, n) - x;
        // ��������ǰֵ
        double dfx_n = n * GetPower(x_n, n - 1);
        // ţ�ٵ���������
        x_n = x_n - fx_n / dfx_n;
        // ���
        f = GetPower(x_n, n) - x;
    }

    return x_n;
}

// ������׳˺���
unsigned int GetFact(unsigned int n)
{
    unsigned int result = 1;

    // 0�Ľ׳���1
    if(n == 0)
    {
        return 1;
    }

    int i;
    for(i = 1; i <= n; i++)
    {
        result *= i;
    }

    return result;
}

// Լ����������������Ŀ��ټ���ƽ�����ĵ���
/*
����һ�������㷨�����㷨���类��Ϊ����Լ�����������������
�������ĵ�����ʾ�����㷨����֮ǰ���ڼ����ͼ��ѧ��Ӳ���������������Ӧ�á�
�����ٶ�Ҫ�ȱ�׼��ţ�ٵ��������� 4 ����
�����еĹؼ���һ�����صĴ����һ��Ī�����������0x5f3759df��
�նȴ�ѧ����ѧ��Lomont���úܺ��棬
����Ҫ�о�һ�¿����Ū����������²�ֵ��ʲô���ء�
LomontҲ�Ǹ�ţ�ˣ��ھ����о�֮���������Ҳ�Ƶ���һ����Ѳ²�ֵ��
�Ϳ���˵����ַǳ��ӽ�, 0x5f37642f��
�������ţ�������������𣿴��沢û�������������
Lomont���������Ժ�ǳ����⣬
�������Լ����������ʼֵ�Ϳ���˵�����������������
����˭�������ܹ��������ȷ�����ƽ������
����ǿ����Ӯ��...

˭Ҳ��֪�����������ô�ҵ�������ֵġ�
���Lomontŭ�ˣ����ñ�������һ������һ�������Թ�����
�����ҵ�һ���ȿ��������Ҫ������ôһ��������֣�
��Ȼʵ���������������������Ľ���ǳ����ƣ�
��������ó���������0x5f375a86��
*/

// ע����㷨ֻ�ܼ���float���͵�����
float InvSqrt(float x)
{
    float xhalf = 0.5f * x;
    int i = *(int*)&x;       // get bits for floating value
    i = 0x5f3759df - (i >> 1); // gives initial guess y0
    x = *(float*)&i;         // convert bits back to float
    x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy

    return x;
}
