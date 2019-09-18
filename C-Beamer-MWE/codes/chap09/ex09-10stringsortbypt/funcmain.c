#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 10
#define N 9

// 函数原型
void Output(char **,int n);//也可用(char *s[],int n);
void SwapAddr(char **, char **);
int StringBubbleSort(char **, int);

int main(void)
{
    char *planets[] = {"Mercury", "Venus", "Earth", "Mars", 
        "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"};

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
