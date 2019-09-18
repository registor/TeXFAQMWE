
#include <stdio.h>
#include <stdlib.h>

#define STR_LEN 80

// 函数原型
int read_line(char [], int);

int main(void)
{
    char str[STR_LEN + 1];

    read_line(str, STR_LEN);

    puts(str);

    return 0;
}

// 函数定义
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
