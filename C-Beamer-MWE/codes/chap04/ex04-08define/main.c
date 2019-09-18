#include <stdio.h>
#include <stdlib.h>

#define  PI  3.14159

int main()
{
    float r;

    scanf("%f", &r);

    printf("area = %f\n", PI * r * r);
    printf("circumference = %f\n", 2 * PI * r);

    return 0;
}
