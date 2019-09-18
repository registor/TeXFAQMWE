#include <stdio.h>
#include <stdlib.h>

int main()
{
    int ch;
    double dfV;
    int iV;

    scanf("%d", &ch);
    scanf("%d", &iV);
    scanf("%lf", &dfV);

    printf("%c %d %f\n", ch, iV, dfV);

    return 0;
}
