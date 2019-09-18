/*简单变量的动态内存分配与使用*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *piV;
    char *pcV;
    float *pfV;

    /*动态内存分配*/
    piV = (int*)malloc(1 * sizeof(int));
    pcV = (char*)malloc(1 * sizeof(char));
    pfV = (float*)malloc(1 * sizeof(float));

    /*使用分配的内存*/
    scanf("%d", piV);
    scanf(" %c", pcV); /*注意%c的前导空格*/
    scanf("%f", pfV);

    printf("Inputted value are: %d,%c,%.2f\n",
                            *piV, *pcV, *pfV);

    /*释放内存空间*/
    free(piV);
    free(pcV);
    free(pfV);

    return 0;
}
