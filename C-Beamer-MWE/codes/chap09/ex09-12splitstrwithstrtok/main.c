/* 使用strtok的例子 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char str[] = "- This, a sample string.";
    char * pch;
    printf ("Splitting string \"%s\" into tokens:\n", str);

    // 分割，以" ,.-"中的字符为分割标志
    pch = strtok(str, " ,.-");
    while (pch != NULL)
    {
        printf ("%s\n", pch);
        pch = strtok(NULL, " ,.-");
    }

    return 0;
}
