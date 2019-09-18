#include <stdio.h>
#include <stdlib.h>

// 函数原型
void PrintGrade(int);

int main()
{
    int iScore;

    scanf("%d", &iScore);

    PrintGrade(iScore);

    return 0;
}

//函数定义
void PrintGrade(int iScore)
{
    switch(iScore / 10)
    {
    case 10: case 9: case 8: case 7: case 6:
        printf("Passing\n");
        break;
    case 5:  case 4:  case 3:
    case 2:  case 1: case 0:
        printf("Failing\n");
        break;
    default:
        printf("Illegal score\n");
        break;
    }
}
