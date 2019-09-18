#include <stdio.h>
#include <stdlib.h>

int main()
{
    int ch;
    int iV;
    double dfV;

    int * pch = &ch;
    int *piV = &iV;
    double *pdfV = &dfV;

    scanf("%d", pch);
    scanf("%d", piV);
    scanf("%lf", pdfV);

    printf("%c %d %f\n", ch, iV, dfV);

    return 0;
}
