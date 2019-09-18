#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 10
#define N 9

// 函数原型
void Output(char **,int n);//也可以用(char *s[],int n);
void SwapAddr(char **, char **);
int StringBubbleSort(char **, int);

int main(void)
{
    char *planets[] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter",
                              "Saturn", "Uranus", "Neptune", "Pluto"};

    Output(planets, N);
    printf("\nsorting...\n\n");

    StringBubbleSort(planets, N);

    Output(planets, N);

    return 0;
}
// 函数定义
// 输出字符数组
void Output(char **str,int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        puts(str[i]);
    }
}

// 交换两个字符串数组
void SwapAddr(char **p1, char **p2)
{
    char *pt;
    pt = *p1;
    *p1 = *p2;
    *p2 = pt;
}

// 采用冒泡排序对字符串数组排序
int StringBubbleSort(char **str, int n)
{
    int i = 0, j = 0;
    int counter = 0;

    for(i = 0; i < n - 1; i++ )
    {
        // j<n-1确保数据不越界
        // -i为了减少循环次数
        for(j = 0; j < n - 1 - i; j++)
        {
            if(strcmp(str[j], str[j + 1]) > 0)
            {
                // 交换指向两个字符串的指针，改变指向
                SwapAddr(&str[j], &str[j + 1]);
            }
            counter++; //循环计数
        }
    }
    return counter;
}
