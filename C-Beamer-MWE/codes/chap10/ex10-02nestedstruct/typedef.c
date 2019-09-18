#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 日期结构体类型
typedef struct
{
    int year;    // 年
    int month;  // 月
    int day;     // 日
}Date;
// 学生结构体类型
typedef struct
{
    int ID;                       // 学号
    char name[20];            // 姓名
    char gender[13];         // 性别
    Date birthday;  // 生日
}StuNode, *StuNodePt;
int main(void)
{
    StuNode st = {101, 
        "Alise", "female",
         {1998, 10,  23}};
    StuNodePt pst; /* StuNode * pst; */   
    pst = &st;
    ...
    return 0;
}

