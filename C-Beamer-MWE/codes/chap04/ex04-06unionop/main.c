#include <stdio.h>
#include <stdlib.h>

union uNode
{
    double dfV;
    unsigned char hex[8];
};

int main()
{
    union uNode uV;

    uV.dfV = 2017.0;

    printf("%02x%02x%02x%02x %02x%02x%02x%02x\n",
     uV.hex[7], uV.hex[6], uV.hex[5], uV.hex[4],
     uV.hex[3], uV.hex[2], uV.hex[1], uV.hex[0]);

    return 0;
}
