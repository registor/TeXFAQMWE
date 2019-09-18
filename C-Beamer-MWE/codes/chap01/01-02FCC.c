#include <stdio.h>
#include <stdlib.h>

int main()
{
    float f;
    float c;

    scanf("%f", &f);

    c = (f - 32) * 5.0 / 9.0; //华氏温度转换为摄氏温度

    printf("%f\n", c);

    return 0;
}
