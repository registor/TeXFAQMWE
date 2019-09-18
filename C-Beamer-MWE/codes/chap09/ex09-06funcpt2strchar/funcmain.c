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
    char str[STR_LEN+1]="Hello World!";

    printf("%s\n", str); // 原字符串

    Traversal(str, lower); // 大写变小写
    printf("%s\n", str);

    Traversal(str, upper); // 小写变大写
    printf("%s\n", str);

    return 0;
}
