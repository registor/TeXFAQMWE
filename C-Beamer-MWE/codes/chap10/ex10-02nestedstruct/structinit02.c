#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 日期结构体类型
struct Date
{
    int year;    // 年
    int month;  // 月
    int day;     // 日
};
// 学生结构体类型
struct StuNode
{
    int ID;                       // 学号
    char name[20];            // 姓名
    char gender[13];         // 性别
    struct Date birthday;  // 生日
};
int main(void)
{
    struct StuNode st = {
      .ID = 101,
      .name = "Alise", 
      .gender = "female",
      .birthday.year = 1998,
      .birthday.month = 10,
      .birthday.day = 23};
    ...
    return 0;
}

