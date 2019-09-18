#include "digitalstring.h"

char * ItoaRevers(char *str, long n)
{
    int iResidue, i;

    for(i = 0; n != 0; i++)
    {
        iResidue = n % 10;
        str[i] = (char)(iResidue + '0');
        n = n / 10;
    }
    str[i] = '\0';

    return str;
}
