#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a = 0;
    int n = 100;
    int i = 0;

    do
    {
        a += 10;
        i = i * 2;
    } while(i < n)

    return 0;
}
