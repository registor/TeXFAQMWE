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
