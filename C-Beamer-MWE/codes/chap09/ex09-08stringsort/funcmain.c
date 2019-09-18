#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 9

// 函数原型
void SwapString(char *, char *);
void Output(char [][8], int);
int StringBubbleSort(char [][8], int);

int main(void)
{
    char planets[][8] = {"Mercury", "Venus", "Earth", "Mars",
              "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"};

    Output(planets, N);
    printf("\n");

    StringBubbleSort(planets, N);

    Output(planets, N);

    return 0;
}

// 函数定义
// 输出字符数组
void Output(char str[][8], int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        puts(str[i]);
    }
}
