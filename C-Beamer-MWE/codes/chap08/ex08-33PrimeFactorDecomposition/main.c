//#include<stdio.h>
//int* PrimeFactor(int n);
//int main()
//{
////    int n;
////    printf("输入合数:");
////    scanf("%d",&n);
////    printPrimeFactor(n);
////    int* PrimeFactor1=PrimeFactor(n);
////    //打印动态数组里面存储的质因数
////    printPrimeFactor1(PrimeFactor1);
//    int* PrimeFactor2 = PrimeFactor(45); //分解45的质因数，并且返回动态数组
//    printPrimeFactor1(PrimeFactor2);
//    int* PrimeFactor3 = PrimeFactor(30);
//    printPrimeFactor1(PrimeFactor3);
////    free(PrimeFactor1);//释放空间
//    free(PrimeFactor2);
//    free(PrimeFactor3);
//    return 0;
//}
//void printPrimeFactor(int n)//对数n分解质因数
//{
//    printf("分解质因数：%d=", n);
//    int factor = 2; //最小的质因数为2
//    int flag = 0;
//    while (factor <= n)//合数大于等于因数
//    {
//        if (n % factor == 0)//刚开始是除以2这个质数，一直除到到没有2的质数因数为止
//        {
//            n = n / factor;//除以这个质数
//            if(flag == 0) //if/else语句只是为了不输出第一个乘号“*”
//                flag = 1;
//            else
//                printf("*");//输出乘号
//            printf("%d", factor); //输出质因数
//        }
//        else
//        {
//            factor++;//质因数加一，
//        }
//    }
//}
//int* PrimeFactor(int n)//对数n分解质因数
//{
//    int length = 1;
//    int* PrimeFactor = (int*)malloc(sizeof(int) * length); //申请一个空间
//    printf("分解质因数：%d=", n);
//    int factor = 2; //最小的质因数为2
//    int flag = 0;
//    int i = 0;
//    while (factor <= n)//合数大于等于因数
//    {
//        if (n % factor == 0)//刚开始是除以2这个质数，一直除到到没有2的质数因数为止
//        {
//            n = n / factor;//除以这个质数
////            if(flag==0)//if/else语句只是为了不输出第一个乘号“*”
////                flag=1;
////            else
////                printf("*");//输出乘号
////            printf("%d",factor);//输出质因数
//
//            PrimeFactor[i++] = factor; //把这个存到动态数组中
//            length++;//动态数组长度加一，是这样的话那动态数组最后一个元素多久永远用不到了。。。
//            PrimeFactor = (int*)realloc(PrimeFactor, length); //重新分配空间，并拷贝之前的数据到新的空间里
//            PrimeFactor[i] = -1; //写入一个负数表示动态一维数组的尾部
//        }
//        else
//        {
//            factor++;//质因数加一，
//        }
//    }
//    return PrimeFactor;//返回这个动态的数组
//}
//void printPrimeFactor1(int *PrimeFactor1)
//{
//    int flag = 0;
//    while(*PrimeFactor1 != -1)
//    {
//        if(flag)//如果flag==1
//            printf("*");
//        else
//            flag = 1; //如果flag==0,
//        printf("%d", *PrimeFactor1++); //先从动态数组中取出值，然后指针前移
//    }
//}


#include <stdio.h>

int is(int i)
{
    int ret = 1;
    int j ;
    for(j = 2; j < i; j++)
    {
        if(i % j == 0)
        {
            ret = 0;
            break;
        }
    }
    return ret;
}//判断i是否是素数

int main()
{
    int x;//记录读入的数
    int n = 1;
    int i;
    scanf("%d", &x);
    printf("%d=", x);
    if(is(x))
    {
        printf("%d", x);
    }
    else
    {
        while(x != 1)
        {
            for(i = 2 ; i <= x ; i++)
            {
                if(is(i) && x % i == 0)
                {
                    printf("%d", i);
                    if(i != x )
                    {
                        printf("x");
                    }
                    x = x / i;
                    i = 1;
                }
            }

        }
    }
    return 0;
}


//#include<iostream>
//#include<math.h>
//using namespace std;
//int isprime(int n)
//{
//    for(int i = 2; i <= sqrt(n); i++)
//    {
//        if(n % i == 0)
//            return 0;
//    }
//    return 1;
//}
//void prime_num(int n )
//{
//    int i, j = 0, m = n;
//    cout << n << "=";
//    for(i = 2; i <= n; i++)
//    {
//        if(n % i == 0 && isprime(i)) //判断i是n的质因数
//        {
//            while(m % i == 0)
//            {
//                if(m / i != 1)
//                    cout << i << "*";
//                else
//                    cout << i << endl;
//                m = m / i;
//            }
//        }
//    }
//}
//int main()
//{
//    int a, b;
//    cin >> a >> b;
//    for(int k = a; k <= b; k++)
//    {
//        prime_num(k);
//    }
//    return 0;
//}


//#include <iostream>
//#include <algorithm>
//using namespace std;
//
//int main()
//{
//	int n ;
//	while (cin >> n){
//		for (int i = 2;i*i <= n;i ++){
//			if (n % i == 0){
//				while (n % i == 0)
//					n /= i;
//				cout << i << " ";
//			}
//		}
//		if (n != 1)cout << n << " ";
//		cout << endl;
//	}
//	return 0;
//}

//private static List<Integer> getPrimeFactor(int num) {
//    List<Integer> primeFactorList = new ArrayList<>();
//    for (int i = 2; i * i < num; i++) {
//        if (num % i == 0) {
//            primeFactorList.add(i);
//            while (num % i == 0) num = num / i;
//        }
//    }
//    if (num > 1) primeFactorList.add(num);
//    return primeFactorList;
//}
