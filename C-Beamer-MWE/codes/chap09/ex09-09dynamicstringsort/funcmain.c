#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 7
#define N 9

// 函数原型
int read_line(char [], int);
void Output(char **, int);
void SwapString(char *, char *);
char **CreateStringArray(int);
void DestroyString(char **, int);
int StringBubbleSort(char **, int);

int main(void)
{
    char **planets;

    planets = CreateStringArray(N);

    Output(planets, N);
    printf("\nsorting...\n\n");

    StringBubbleSort(planets, N);

    Output(planets, N);

    // 释放空间
    DestroyString(planets, N);
    // 将不用的指针赋值为NULL，防止野指针
    planets = NULL;

    return 0;
}
// 函数定义
// 输出字符数组
void Output(char **str, int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        puts(str[i]);
    }
}
