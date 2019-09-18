#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9

// 函数原型
// 输出函数
void Output(char (*)[8], int n);
// 比较函数
int comp(const void *s1, const void *s2);

int main(void)
{
    char planets[][8] = {"Mercury", "Venus", "Earth", "Mars",
      "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"};

    Output(planets, MAX);
    printf("\nsorting...\n\n");
