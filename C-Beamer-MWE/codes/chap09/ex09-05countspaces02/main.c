#include <stdio.h>
#include <stdlib.h>

#define STR_LEN 80

// 函数原型
int count_spaces(const char *);

int main(void)
{
    char str[STR_LEN + 1] =
        "fdsa drf tewq gsdafsd";

    printf("%d\n", count_spaces(str));

    return 0;
}

// 函数定义
// const常量，只读参数
int count_spaces(const char *s)
{
    int count = 0;

    // 以空字符'\0'为结束条件
    while(*s != '\0')
    {
        if(*s == ' ')
        {
            count++;
        }
        s++;
    }
    return count;
}
