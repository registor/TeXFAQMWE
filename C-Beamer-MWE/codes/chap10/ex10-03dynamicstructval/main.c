#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 日期结构体类型
typedef struct
{
    int year;    // 年
    int month;  // 月
    int day;     // 日
} Date;
// 学生结构体类型
typedef struct
{
    int ID;                       // 学号
    char name[20];            // 姓名
    char gender[13];         // 性别
    Date birthday;  // 生日
} StuNode, *StuNodePt;

int main(void)
{
    StuNodePt pst;
    // 动态分配内存
    pst = (StuNodePt)malloc(1 * sizeof(StuNode));
    // 成员赋值
    pst->ID = 101;
    strcpy(pst->name, "Alise");
    strcpy(pst->gender, "female");
    pst->birthday.year = 1998;
    pst->birthday.month = 10;
    pst->birthday.day = 23;
    // 输出成员内容
    printf("ID = %d\nname = %s\ngender = %s\n",
                      pst->ID, pst->name, pst->gender);
    printf("birthday = %d/%d/%d\n", pst->birthday.year,
                    pst->birthday.month, pst->birthday.day);
    // 释放内存
    free(pst);

    return 0;
}
