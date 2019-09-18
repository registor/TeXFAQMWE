#include <stdio.h>
#include <stdlib.h>

int main()
{
    int iV;
    double dfV;
    char ch;

    scanf("%d", &ch); /*%d用于整型！*/
    scanf("%d", &iV);
    scanf("%lf", &dfV);

    printf("%c %d %f\n", ch, iV, dfV);

    return 0;
}
