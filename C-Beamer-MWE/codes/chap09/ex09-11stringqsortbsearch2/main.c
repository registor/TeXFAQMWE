#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9

// 函数原型
// 输出函数
void Output(char **, int n); //也可以用(char *s[],int n);
// 查找
char **Search(const char *, char **);
// 输出查找结果
void SearchOut(char **);
// 比较函数
int comp(const void *s1, const void *s2);

int main(void)
{
    char **ptr;

    char *planets[] = {"Mercury", "Venus", "Earth", "Mars",
     "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"};

    Output(planets, MAX);
    printf("sorting...\n");

    /* 字符串排序(实际是根据字符串大小对指针数组排序). */
    qsort(planets, MAX, sizeof(planets[0]), comp);

    Output(planets, MAX);

    // 查找
    ptr = Search("Neptune", planets);
    SearchOut(ptr);

    return(0);
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

// 比较函数，根据两个字符串大小返回负、0、正数
int comp(const void *s1, const void *s2)
{
    // 需要先将void指针强制转换成char**指针，
    // 再取内容*(char**)s1指向字符串
    return (strcmp(*(char **)s1, *(char **)s2));
}

// 查找
char **Search(const char *key, char **s)
{
    const char **pkey;
    char **ptr;
    /* 让pkey指向key */
    pkey = &key;
    /* 在字符串查找 */
    ptr = bsearch(pkey, s, MAX, sizeof(s[0]), comp);

    return ptr;
}
// 输出查找结果
void SearchOut(char **ptr)
{
    if (ptr != NULL)
        printf("%s found.\n", *ptr);
    else
        printf("not found.\n");
}
