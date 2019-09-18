#include <stdio.h>
#include <stdlib.h>

int main()
{
    int iV;
    double dfV;
    char ch;

    scanf("%c", &ch);
    scanf("%d", &iV);
    scanf("%lf", &dfV);

    printf("%c %d %f\n", ch, iV, dfV);

    return 0;
}
