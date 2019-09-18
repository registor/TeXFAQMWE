#include <stdio.h>
#include <stdlib.h>

#define STR_LEN 80

// 函数原型
// 字符串遍历
void Traversal(char *, void (*)(char *));
// 功能函数
void lower(char *);
void upper(char *);

int main(void)
{
    char str[STR_LEN + 1] = "Hello World!";

    printf("%s\n", str); // 原字符串

    Traversal(str, lower); // 大写字母变小写
    printf("%s\n", str);

    Traversal(str, upper); // 小写字母变大写
    printf("%s\n", str);

    return 0;
}

// 函数定义
// 字符串遍历
void Traversal(char *s, void (*pf)(char *))
{
    // 以空字符'\0'为结束条件
    while(*s != '\0')
    {
        pf(s);
        s++;
    }
}
// 大写字母变小写
void lower(char *pch)
{
    if((*pch >= 'A' && *pch <= 'Z'))
    {
        *pch = *pch + ('a' - 'A'); /* 小字变大写 */
    }
}
// 小写字母变大写
void upper(char *pch)
{
    if((*pch >= 'a' && *pch <= 'z'))
    {
        *pch = *pch - ('a' - 'A'); /* 小字变大写 */
    }
}
