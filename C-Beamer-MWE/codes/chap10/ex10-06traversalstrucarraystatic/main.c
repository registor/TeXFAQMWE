#include <stdio.h>
#include <stdlib.h>

#define N 5

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

// 函数原型
// 数组遍历，注意函数指针的使用
void Traversal(StuNodePt, int, void (*pf)(StuNodePt));
// 功能函数
void ModifyID(StuNodePt); // 修改一个元素的ID
void Output(StuNodePt); //  输出一个元素的数据

int main()
{
    // 创建数组，注意name和gender指向字符串常量，不可更改
    StuNode Stu[N] = {{101, "zhang", "male", {1998, 10, 23}},
                                 {102, "wang", "male", {1999, 1, 2}},
                                 {103, "li", "female", {2000, 11, 12}},
                                 {104, "zhao", "male", {1997, 7, 10}},
                                 {105, "xie", "female", {2001, 9, 10}}
                                 };
    // 输出
    Traversal(Stu, N, Output);
    printf("\n");
    // 修改ID
    Traversal(Stu, N, ModifyID);
    // 输出
    Traversal(Stu, N, Output);

    return 0;
}

// 函数定义
// 遍历数组
void Traversal(StuNodePt pa, int n, void (*pf)(StuNodePt))
{
    StuNodePt p;

    // 遍历数组，使用指针进行操作
    for(p = pa; p < pa + n; p++)
    {
        pf(p); // 调用传入的函数
    }
}

// 输出数据
void Output(StuNodePt pData)
{
    // 输出一个节点的数据
    printf("%d\t%s\t%s\t%d/%d/%d\n", pData->ID, pData->name,
           pData->gender, pData->birthday.year,
           pData->birthday.month, pData->birthday.day);
}

// 修改ID数据
void ModifyID(StuNodePt pData)
{
    pData->ID += 2017000;
}
