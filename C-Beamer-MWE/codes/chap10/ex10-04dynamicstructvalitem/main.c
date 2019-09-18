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
    char *name;            // 姓名
    char *gender;         // 性别
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

void Output(StuNodePt pNode)
{
    // 输出成员内容
    printf("ID = %d\nname = %s\ngender = %s\n",
                      pNode->ID, pNode->name, pNode->gender);
    printf("birthday = %d/%d/%d\n", pNode->birthday.year,
                    pNode->birthday.month, pNode->birthday.day);
}

void CreateNode(StuNodePt *pNode)
{
    // 动态分配内存
    (*pNode) = (StuNodePt)malloc(1 * sizeof(StuNode));
    // 成员赋值
    (*pNode)->ID = 101;
    // 为成员开避内存并赋值
    (*pNode)->name = (char *)malloc((strlen("Alise") + 1) * sizeof(char));
    strcpy((*pNode)->name, "Alise");
    (*pNode)->gender = (char *)malloc((strlen("female") + 1) * sizeof(char));
    strcpy((*pNode)->gender, "female");
    // 结构体成员赋值
    (*pNode)->birthday.year = 1998;
    (*pNode)->birthday.month = 10;
    (*pNode)->birthday.day = 23;
}

void DestroyNode(StuNodePt *pNode)
{
    // 释放内存
    free((*pNode)->name);
    (*pNode)->name = NULL;
    free((*pNode)->gender);
    (*pNode)->gender = NULL;
    free((*pNode));
    (*pNode) = NULL;
}
