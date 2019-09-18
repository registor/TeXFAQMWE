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
