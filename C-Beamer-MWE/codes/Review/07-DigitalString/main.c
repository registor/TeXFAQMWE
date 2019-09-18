#include <stdio.h>
#include <stdlib.h>
#include "digitalstring.h"
int main()
{

    long n = 45593285;
    char str[81] = {0};

    ItoaRevers(str, n);

    puts(str);

    return 0;
}
