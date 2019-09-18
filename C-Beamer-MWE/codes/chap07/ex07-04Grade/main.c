#include <stdio.h>
#include <stdlib.h>

// 函数原型
char GetGrade(int);

int main()
{
    int iScore;
    char chGrade;

    scanf("%d", &iScore);

    // 调用函数
    chGrade = GetGrade(iScore);

    if(chGrade != 0)
    {
        printf("Grade is %c\n", chGrade);
    }
    else
    {
        printf("Error!\n");
    }


    return 0;
}

//函数定义
char GetGrade(int iScore)
{
    char chResult;

    if (iScore < 60)
    {
        chResult = 'F';
    }
    else if (iScore < 70)
    {
        chResult = 'D';
    }
    else if (iScore < 80)
    {
        chResult = 'C';
    }
    else if (iScore < 90)
    {
        chResult = 'B';
    }
    else if (iScore <= 100)
    {
        chResult = 'A';
    }
    else
    {
        chResult = 0;
    }

    return chResult;
}

