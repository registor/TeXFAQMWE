#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define N 10

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
// 数组遍历
void Traversal(StuNodePt, int, void (*pf)(StuNodePt));
// 功能函数
void Input(StuNodePt); // 输入一个元素的数据
void Output(StuNodePt); //  输出一个元素的数据
void DestroyNode(StuNodePt); // 销毁一个元素中的动态内存
// 初始化一个元素
bool InitNode(StuNodePt, int, const char *, const char *, 
              int, int, int);
// 深拷贝
bool CopyStu(StuNodePt const, const StuNodePt);
// 读入一行字符
int read_line(char*, int);

int main()
{
    StuNode Stu[N] = {0}; // 主要为指针赋NULL
    // 把输入重定向到文件"data.txt"
    freopen("data.txt", "r", stdin);
    Traversal(Stu, N, Input);
    // 把输入重定向回键盘
    freopen("CON", "r", stdin);
    Traversal(Stu, N, Output);
    printf("\n");
    Traversal(Stu, N, DestroyNode);

    return 0;
}
