...
#include <string.h>
...
char *strcat(char *s1, const char *s2)
{
    char *p = s1;

    // 确定字符串s1的末尾位置
    while (*p != '\0')
        p++;

    // strlen(s2) + 1确保复制空字符'\0'
    memcpy(p, s2, strlen(s2) + 1 );

    // 返回s1的指针
    return s1;
}
