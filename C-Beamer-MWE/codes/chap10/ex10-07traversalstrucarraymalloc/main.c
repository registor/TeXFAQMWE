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

// 函数原型
// 数组遍历
void Traversal(StuNodePt, int, void (*pf)(StuNodePt));
// 功能函数
void Input(StuNodePt); // 输入一个元素的数据
void Output(StuNodePt); //  输出一个元素的数据
void DestroyNode(StuNodePt); // 销毁一个元素中的动态内存
// 初始化一个元素
bool InitNode(StuNodePt, int, const char *, const char *, int, int, int);
// 深拷贝
bool CopyStu(StuNodePt const, const StuNodePt);
// 读入一行字符
int read_line(char*, int);

int main()
{
    StuNode Stu[N] = {0};

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

// 输入数据
void Input(StuNodePt pData)
{
    // 输入一个节点的数据
    int id;
    char name[81], gender[15];
    int year, month, day;

    // 读入学号
    scanf("%d", &id);

    // 跳过剩下的其它字符及'\n'
    while(getchar() != '\n')
        ;

    // 读入字符串
    read_line(name, 80);
    read_line(gender, 15);

    // 读入日期数组
    scanf("%d%d%d", &year, &month, &day);

    // 给一个节点各成员赋值(字符串需要动态分配)
    InitNode(pData, id, name, gender, year, month, day);
}
// 输出数据
void Output(StuNodePt pData)
{
    // 输出一个节点的数据
    printf("%d\t%s\t%s\t%d/%d/%d\n", pData->ID, pData->name, pData->gender,
           pData->birthday.year, pData->birthday.month, pData->birthday.day);
}

// 创建一个节点的数据
bool InitNode(StuNodePt pNode, int ID, const char *pname, const char *pgender, int year, int month, int day)
{
    if(pNode == NULL || pname == NULL || pgender == NULL)
    {
        return false; // 空指针，无法后续操作，返回假值
    }

    // ID赋值
    pNode->ID = ID;

    // 为姓名和性别成员动态开避内存并赋值
    pNode->name = (char *)malloc((strlen(pname) + 1) * sizeof(char));
    pNode->gender = (char *)malloc((strlen(pgender) + 1) * sizeof(char));
    if(pNode->name == NULL || pNode->gender == NULL)
    {
        pNode->ID = -1;
        return false;  // 内存分配出错，返回假值
    }
    // 动态内存赋值
    strcpy(pNode->name, pname);
    strcpy(pNode->gender, pgender);

    // 其它成员赋值
    pNode->birthday.year = year;
    pNode->birthday.month = month;
    pNode->birthday.day = day;

    return true; // 一切正常，返回真值
}

bool CopyStu(StuNodePt const pTarget, const StuNodePt pSource)
{
    if(pSource == NULL || pSource->name == NULL || pSource->gender == NULL || pTarget == NULL)
    {
        return false; // 确保指针正确，否则返回假
    }

    if(pTarget->name != NULL)
    {
        free(pTarget->name); // 若指针不为NULL，释放内存
    }

    if(pTarget->gender != NULL)
    {
        free(pTarget->gender); // 若指针不为NULL，释放内存
    }

    // 分配内存
    pTarget->name = (char *)malloc((strlen(pSource->name)+1) * sizeof(char));
    pTarget->gender = (char *)malloc((strlen(pSource->gender)+1) * sizeof(char));
    if(pTarget->name == NULL || pTarget->gender == NULL)
    {
        pTarget->ID = -1;
        return false;  // 分配内存出错，返回假值
    }

    // 复制
    pTarget->ID = pSource->ID;
    strcpy(pTarget->name, pSource->name);
    strcpy(pTarget->gender, pSource->gender);
    pTarget->birthday.year = pSource->birthday.year;
    pTarget->birthday.month = pSource->birthday.month;
    pTarget->birthday.day = pSource->birthday.day;

    return true; // 一切正常返回真值
}

void DestroyNode(StuNode *pNode)
{
    // 释放节点中动态分配的内存
    free(pNode->name);
    pNode->name = NULL;
    free(pNode->gender);
    pNode->name = NULL;
}
// 读入一行字符串
int read_line(char *str, int n)
{
    int ch, i = 0;

    // 读入字符，直到遇到换行符
    while ((ch = getchar()) != '\n')
    {
        if(i < n) /* 最大字符数 */
        {
            str[i++] = ch;
        }
    }
    str[i] = '\0'; /* 添加空字符'\0' */

    return i;    /* 返回读入的字符数 */
}
