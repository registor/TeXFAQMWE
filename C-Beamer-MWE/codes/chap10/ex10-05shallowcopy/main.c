#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 学生结构体类型
struct StuInfo
{
    int ID;                       // 学号
    char *name;            // 姓名
} ;

// 与声明分开使用typedef
typedef struct StuInfo StuNode;

// 函数原型
bool InitNode(StuNode *, int, const char *);
bool CopyStu(StuNode * const, const StuNode *);
void DestroyNode(StuNode *);
void Output(const StuNode *);

int main(void)
{
    StuNode stu1 = {0}, stu2 = {0};

    // 创建对象
    InitNode(&stu1, 101, "Alise");
    Output(&stu1);
    //stu2 = stu1;
    CopyStu(&stu2, &stu1);
    Output(&stu2);
    // 释放内存
    DestroyNode(&stu2);
    Output(&stu1);
    DestroyNode(&stu1);

    return 0;
}

void Output(const StuNode * pNode)
{
    // 输出成员内容
    printf("ID = %d\nname = %s\n",
                      pNode->ID, pNode->name);
}

bool InitNode(StuNode *pNode, int ID, const char *pname)
{
    if(pNode == NULL || pname == NULL)
    {
        return false; // 空指针，无法后续操作
    }

    // 普通成员赋值
    pNode->ID = ID;

    // 为成员动态开避内存并赋值
    pNode->name = (char *)malloc((strlen(pname) + 1) * sizeof(char));
    if(pNode->name == NULL)
    {
        pNode->ID = -1;
        return false;  // 分配内存出错，返回假值
    }
    // 动态内存赋值
    strcpy(pNode->name, pname);

    return true; // 返回真值
}

bool CopyStu(StuNode * const pTarget, const StuNode * pSource)
{
    if(pSource == NULL || pSource->name == NULL || pTarget == NULL)
    {
        return false; // 确保指针正确，否则返回假
    }

    if(pTarget->name != NULL)
    {
        free(pTarget->name); // 若已分配了内存空间，则需要先释放
    }

    // 分配内存
    pTarget->name = (char *)malloc((strlen(pSource->name)+1) * sizeof(char));
    if(pTarget->name == NULL)
    {
        pTarget->ID = -1;
        return false;  // 分配内存出错，返回假值
    }

    // 复制字符串
    pTarget->ID = pSource->ID;
    strcpy(pTarget->name, pSource->name);

    return true;
}

void DestroyNode(StuNode *pNode)
{
    // 释放内存
    free(pNode->name);
    pNode->name = NULL;
}
