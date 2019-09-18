#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  printbit(b) \
printf("%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u\n",\
b.a0,b.a1,b.a2,b.a3,b.a4,b.a5,b.a6,b.a7,\
b.a8,b.a9,b.a10,b.a11,b.a12,b.a13,b.a14,b.a15)

#define  sumbites1(b) \
printf("%d",\
b.a0+b.a1+b.a2+b.a3+b.a4+b.a5+b.a6+b.a7+\
b.a8+b.a9+b.a10+b.a11+b.a12+b.a13+b.a14+b.a15)

