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
