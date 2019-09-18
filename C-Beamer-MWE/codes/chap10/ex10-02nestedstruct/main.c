#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    StuNode st = {101,
                  "Alise", "female",
    {1998, 10,  23}
                 };

    StuNodePt pst;

    pst = &st;

//    st.ID = 101;
//    strcpy(st.name, "Alise");
//    strcpy(st.gender, "female");
//    st.birthday.year = 1998;
//    st.birthday.month = 10;
//    st.birthday.day = 23;

    printf("ID = %d\nname = %s\ngender = %s\n", pst->ID, st.name, st.gender);
    printf("birthday = %d/%d/%d\n", st.birthday.year, st.birthday.month, st.birthday.day);

    return 0;
}
