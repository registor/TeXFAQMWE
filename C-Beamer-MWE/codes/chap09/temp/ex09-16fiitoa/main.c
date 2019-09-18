#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * ft_itoa(int n);

void check(int n)
{
    printf("%i = %s\n", n, ft_itoa(n));
}

int main()
{
    check(0);
    check(-1);
    check(1);
    check(23);
    check(42);
    check(4711);
    check(1000);
    check(INT_MAX);
    check(1 + INT_MIN);
    check(INT_MIN);
}

int ft_intlen(int n)
{
    char buffer[8192];
    return snprintf(buffer, sizeof buffer, "%i", n);
}

char * ft_itoa(int n)
{
    char * s;
    size_t l, len;
    bool fix_int_min = false;

    if (!n)
    {
        return mstrcpy("0");
    }

    if (-INT_MAX != INT_MIN && n == INT_MIN)
    {
        ++n;
        fix_int_min = true;
    }

    len = ft_intlen(n);
    if (!(s = malloc(len + 1)))
    {
        return NULL;
    }
    if (n < 0)
    {
        s[0] = '-';
        n = -n;
    }
    s[l = len] = '\0';
    while (n)
    {
        s[--len] = (n % 10) + '0';
        n /= 10;
    }

    if (fix_int_min)
    {
        --l;
        while (s[l] == '9')
        {
            s[l++] = 0;
        }
        if (s[l] == '-')
        {
            // realloc +1 and write "-1[0....0]\0"
        }
        else
        {
            ++s[l];
        }
    }

    return s;
}

size_t ft_uintlen(unsigned n)
{
    size_t len = 0;
    do
    {
        ++len;
        n /= 10;
    }while(n);

    return len;
}

char *ft_itoa(int x)
{
    char    *s;
    size_t  len;
    unsigned n;
    int negative;

    negative = x < 0;
    n = negative ? 0 - (unsigned)x : (unsigned)x;
    len = ft_uintlen(n) + negative + 1;
    if (!(s = (char*)malloc(len)))
        return (NULL);

    s[--len] = '\0';
    if (negative)
        s[0] = '-';
    do
    {
        s[--len] = (n % 10) + '0';
        n /= 10;
    }
    while(n);
    return (s);
}
