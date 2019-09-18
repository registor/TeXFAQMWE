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
    int ID;               // 学号
    char *name;        // 姓名
    char *gender;    // 性别
    Date birthday;  // 生日
} StuNode, *StuNodePt;

// 函数原型
void CreateNode(StuNodePt *pNode);
void DestroyNode(StuNodePt *pNode);
void Output(StuNodePt pNode);

int main(void)
{
    StuNodePt pst = NULL;

    // 创建对象
    CreateNode(&pst);
    Output(pst);
    // 释放内存
    DestroyNode(&pst);

    return 0;
}
