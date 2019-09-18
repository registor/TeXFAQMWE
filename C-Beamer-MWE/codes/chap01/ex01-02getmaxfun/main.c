#include <stdio.h>
#include <stdlib.h>

int Max(int x, int y);

int main()
{
    int a, b, c;

    a = 10;
    b = 20;

    c =Max(a, b);

    printf("Max(a, b)=%d.\n", c);

    return 0;
}

int Max(int x, int y)
{
    int z;

    if(x > y)
    {
        z = x;
    }
    else
    {
        z = y;
    }

    return (z);
}
