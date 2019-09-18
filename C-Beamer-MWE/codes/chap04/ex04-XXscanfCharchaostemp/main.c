#include <stdio.h>
#include <stdlib.h>

int main()
{
    char ch;
    int iV;
    double dfV;

    char * pch = &ch;
    int *piV = &iV;
    double *pdfV = &dfV;

    scanf("%d", pch);
    scanf("%d", piV);
    scanf("%lf", pdfV);

    printf("%c %d %f\n", ch, iV, dfV);

    return 0;
}
