#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // 学生结构体类型
    struct
    {
        int ID;                   // 学号
        char name[20];        // 姓名
        char gender[13];     // 性别
        // 日期结构体类型
        struct
        {
            int year;    // 年
            int month;  // 月
            int day;     // 日
        }birthday;  // 生日
    }  st = {101,
        "Alise", "female", 
        {1998, 10, 23}};
    ...
    return 0;
}

