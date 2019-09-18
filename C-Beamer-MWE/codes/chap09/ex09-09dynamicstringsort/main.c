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

// 读入一行字符
int read_line(char str[], int n)
{
    int ch, i = 0;

    // 读入字符，直到遇到换行符
    while ((ch = getchar()) != '\n')
    {
        if(i < n) /* 最大字符数 */
        {
            str[i++] = ch;
        }
    }
    str[i] = '\0'; /* 添加空字符'\0' */

    return i;    /* 返回读入的字符数 */
}

// 交换两个字符串数组
void SwapString(char *s1, char *s2)
{
    char tempStr[STR_LEN + 1];
    strcpy(tempStr, s1);
    strcpy(s1, s2);
    strcpy(s2, tempStr);
}

// 动态创建字符串数组
char **CreateStringArray(int n)
{
    char strTemp[STR_LEN + 1];
    char **p;
    int i;

    /*分配n个sizeof(char *)字节的
    连续空间存储每个字符串的首地址*/
    p = (char **)malloc(n * sizeof(char *));
    if(NULL == p) // 内存申请失败的处理
    {
        printf("Not enough strpointer memory!\n");
        exit(1);
    }

    // 把输入重定向到文件"data.txt"
    freopen("data.txt", "r", stdin);

    /*再为每一行分配n个strlen(strTemp) + 1个字节
    的连续空间存储每一个字符串*/
    for (i = 0; i < n; i++)
    {        
        read_line(strTemp, STR_LEN); // 读入一个字符串到临时数组
        p[i] = (char *)malloc((STR_LEN + 1) * sizeof(char));
        if(NULL == p[i]) // 内存申请失败的处理
        {
            printf("Not enough str's memory!\n");
            exit(1);
        }
	memset(p[i], '\0', STR_LEN + 1);
        // 复制字符串
        strcpy(p[i], strTemp);
    }

    // 把输入重定向回键盘
    freopen("CON", "r", stdin);
    return p;
}

void DestroyString(char **p, int n)
{
    int i;
    /*释放每一行的空间*/
    for (i = 0; i < n; i++)
    {
        free(p[i]);
        p[i] = NULL; // 赋值为NULL，防止野指针
    }

    /*释放存储每一行首地址的内存空间*/
    free(p);
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
            if(strcmp(str[j], str[j + 1]) > 0) // 升序
            {
                SwapString(str[j], str[j + 1]);
            }
            counter++; //循环计数
        }
    }
    return counter;
}
