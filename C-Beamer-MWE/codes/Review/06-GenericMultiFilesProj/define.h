#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

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
    char *name;            // 姓名
    char *gender;         // 性别
    Date birthday;  // 生日
} StuNode, *StuNodePt; // typedef重定义新名称


#endif // DEFINE_H_INCLUDED
