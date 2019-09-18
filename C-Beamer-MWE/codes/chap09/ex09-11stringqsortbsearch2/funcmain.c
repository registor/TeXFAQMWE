#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9

// 输出函数
void Output(char **, int n);
// 查找
char **Search(const char *, char **);
// 输出查找结果
void SearchOut(char **);
// 比较函数
int comp(const void *s1, const void *s2);

int main(void)
{
    ...
    /* 排序(实际是根据字符串大小对指针数组排序). */
    qsort(planets, MAX, sizeof(planets[0]), comp);
    ...
    ptr = Search("Neptune", planets);
    ...
    return(0);
}
