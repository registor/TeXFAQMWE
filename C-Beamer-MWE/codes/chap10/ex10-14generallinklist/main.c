/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示泛型链表的操作。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月08日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月08日
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef enum datatype
{
    STRING,
    INT,
    DOUBLE,
    PT2D
} DataType;

typedef struct pointer // 点结构体
{
    int x;
    int y;
} Point2D;

typedef struct node    // 链表节点
{
    void *data;              // 数据域指针，可以指向任意类型
    struct node *next;   // 指向下一个链表节点
} ListNode;

// 函数原型
// 链表操作函数
ListNode *CreateLinkList(DataType); // 创建带有头节点链表
void CreateIntLinkList(ListNode *); // 创建整型链表
void CreateDoubleLinkList(ListNode *); // 创建浮点型链表
void CreateStrLinkList(ListNode *); // 创建字符串型链表
void CreatePt2DLinkList(ListNode *); //创建结构体类型链表

void AddHeadWithDummyNode(ListNode *, void *); // 有头节点的头插法
void TraverseList(ListNode *, void (*)(const void *) ); // 遍历链表函数原型
void DestroyList(ListNode **, void (*)(void *)); // 销毁链表

// 数据输出函数
void stringOutput(const void *);
void intOutput(const void *);
void doubleOutput(const void *);
void pointOutput(const void *);

// 内存释放函数
void stringFree(void *);
void intFree(void *);
void doubleFree(void *);
void pointFree(void *);

//-----------------------------------------------------------------------------------------------
// 名称：int main(void)
// 功能：主函数，程序入口
// 参数： 无
// 返回：int  --- 成功返回0，其它返回非0
// 作者：耿楠
// 日期：2017年11月03日
//-----------------------------------------------------------------------------------------------
int main(void)
{
    ListNode *pHead = NULL;

    pHead = CreateLinkList(INT);
    TraverseList(pHead, intOutput);
    DestroyList(&pHead, intFree);

    pHead = CreateLinkList(DOUBLE);
    TraverseList(pHead, doubleOutput);
    DestroyList(&pHead, doubleFree);

    pHead = CreateLinkList(STRING);
    TraverseList(pHead, stringOutput);
    DestroyList(&pHead, stringFree);

    pHead = CreateLinkList(PT2D);
    TraverseList(pHead, pointOutput);
    DestroyList(&pHead, pointFree);

    return 0;
}

//-----------------------------------------------------------------------------------------------
// 名称：void TraverseList(ListNode * pHead, void (*pf)(const ListNode *))
// 功能：遍历链表
// 参数：
//       [ListNode * pHead] --- 链表头节点指针
//       [void (*pf)(const void *)] --- 处理节点的函数指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
void TraverseList(ListNode * pHead, void (*pf)(const void *))
{
    ListNode * p = pHead->next; // 跳过头节点

    while(p != NULL) //节点p不为空，循环
    {
        pf(p->data); // 通过函数指针调用传入的函数，输出节点中的数据
        p = p->next;
    }

    printf("\n");
}

//-----------------------------------------------------------------------------------------------
// 名称：void DestroyList(ListNode **pHead, void (*pfun)(void *))
// 功能：销毁链表
// 参数：
//       [ListNode **pHead] --- 链表头指针的指针
//       [void (*pfun)(void *)] --- 释放节点数据域内存的函数指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
void DestroyList(ListNode **pHead, void (*pf)(void *))
{
    ListNode *p;

    while(*pHead != NULL)
    {
        p = (*pHead)->next;
        pf((*pHead)->data);
        free(*pHead);
        *pHead = p;
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void AddHeadWithDummyNode(ListNode *pHead, void * pData)
// 功能：头插法插入一个节点(有头节点或哑元节点或Dummy Node)
// 参数：
//       [ListNode *pHead] --- 指向链表头节点的指针
//       [void * pData] --- 插入节点的数据指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月06日
//-----------------------------------------------------------------------------------------------
void AddHeadWithDummyNode(ListNode *pHead, void * pData)
{
    ListNode *pNewNode = (ListNode*)malloc(sizeof(ListNode)); // 创建新节点

    if(pNewNode == NULL)
    {
        return;
    }

    pNewNode->data = pData;
    pNewNode->next = pHead->next;
    pHead->next = pNewNode;  // 哑元头节点指向了新节点
}

//-----------------------------------------------------------------------------------------------
// 名称：ListNode *CreateLinkList(DataType dataType)
// 功能：创建带有头节点的链表
// 参数：
//       [DataType dataType] --- 链表类型枚举
// 返回：[ListNode *] --- 链表头指针
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
ListNode *CreateLinkList(DataType dataType)
{
    ListNode * pHead = NULL;

    pHead = (ListNode *)malloc(sizeof(ListNode));
    pHead->data = NULL;
    pHead->next = NULL;

    switch(dataType)
    {
    case INT:
        CreateIntLinkList(pHead);
        break;

    case DOUBLE:
        CreateDoubleLinkList(pHead);
        break;

    case STRING:
        CreateStrLinkList(pHead);
        break;

    case PT2D:
        CreatePt2DLinkList(pHead);
        break;
    }

    return pHead;
}

//-----------------------------------------------------------------------------------------------
// 名称：void CreateIntLinkList(ListNode * pHead)
// 功能：创建整型链表(有头节点)
// 参数：
//       [ListNode * pHead] --- 链表头指针
// 返回：[void] --- 无
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
void CreateIntLinkList(ListNode * pHead)
{
    int *p;

    // 置随机种子
    srand(time(NULL));

    for(int i = 0; i < 10; i++)
    {
        p = (int* )malloc(sizeof(int)); // 申请空间

        // 取[a,b)之间的随机整数（包括a，但不包括b)，
        // 使用通用公式：  (rand() % (b - a)) + a
        *p = rand() % 20 - 10;; // 赋值

        // 头插法插入到链表(注意：需要把数据指针转换为void*类型的指针)
        AddHeadWithDummyNode(pHead, (void *)p);
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void CreateDoubleLinkList(ListNode * pHead)
// 功能：创建浮点型链表(有头节点)
// 参数：
//       [ListNode * pHead] --- 链表头指针
// 返回：[void] --- 无
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
void CreateDoubleLinkList(ListNode * pHead)
{
    double *p;

    // 置随机种子
    srand(time(NULL));

    for(int i = 0; i < 10; i++)
    {
        p = (double* )malloc(sizeof(double)); // 申请空间
        *p = rand() / ((double)(RAND_MAX) / 100); // 赋值， // 产生随机浮点数，比如0～100

        // 头插法插入到链表(注意：需要把数据指针转换为void*类型的指针)
        AddHeadWithDummyNode(pHead, (void *)p);
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void CreateStrLinkList(ListNode * pHead)
// 功能：创建字符串型链表(有头节点)
// 参数：
//       [ListNode * pHead] --- 链表头指针
// 返回：[void] --- 无
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
void CreateStrLinkList(ListNode * pHead)
{
    char *p;

    p = (char* )malloc(10 * sizeof(char));
    strcpy(p, "hello ");
    // 头插法插入到链表(注意：需要把数据指针转换为void*类型的指针)
    AddHeadWithDummyNode(pHead, (void *)p);

    p = (char* )malloc(10 * sizeof(char));
    strcpy(p, "void ");
    // 头插法插入到链表(注意：需要把数据指针转换为void*类型的指针)
    AddHeadWithDummyNode(pHead, (void *)p);

    p = (char* )malloc(10 * sizeof(char));
    strcpy(p, "Pointer! ");
    // 头插法插入到链表(注意：需要把数据指针转换为void*类型的指针)
    AddHeadWithDummyNode(pHead, (void *)p);
}

//-----------------------------------------------------------------------------------------------
// 名称：void CreatePt2DLinkList(ListNode * pHead)
// 功能：创建结构体类型链表(有头节点)
// 参数：
//       [ListNode * pHead] --- 链表头指针
// 返回：[void] --- 无
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
void CreatePt2DLinkList(ListNode * pHead)
{
    Point2D *p;

    // 置随机种子
    srand(time(NULL));

    for(int i = 0; i < 10; i++)
    {
        p = (Point2D* )malloc(sizeof(*p)); // 申请内存空间
        // 取[a,b)之间的随机整数（包括a，但不包括b)，
        // 使用通用公式：  (rand() % (b - a)) + a
        p->x = rand() % 20 - 10;;
        p->y = rand() % 20 - 10;;
        // 头插法插入到链表(注意：需要把数据指针转换为void*类型的指针)
        AddHeadWithDummyNode(pHead, (void *)p);
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void stringOutput(const void *pData)
// 功能：输出字符串指针指向的数据区中的数据
// 参数：
//       [const void *pData] --- 指向数据区的指针(void *万能指针)
// 返回：[void] --- 无
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
void stringOutput(const void *pData)
{
    printf("%s\n", (char*)(pData));
}

//-----------------------------------------------------------------------------------------------
// 名称：void intOutput(const void *pData)
// 功能：输出整型指针指向的数据区中的数据
// 参数：
//       [const void *pData] --- 指向数据区的指针(void *万能指针)
// 返回：[void] --- 无
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
void intOutput(const void *pData)
{
    printf("%d ", *(int*)(pData));
}

//-----------------------------------------------------------------------------------------------
// 名称：void doubleOutput(const void *pData)
// 功能：输出浮点型指针指向的数据区中的数据
// 参数：
//       [const void *pData] --- 指向数据区的指针(void *万能指针)
// 返回：[void] --- 无
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
void doubleOutput(const void *pData)
{
    printf("%.4f ", *(double*)(pData));
}

//-----------------------------------------------------------------------------------------------
// 名称：void pointOutput(const void *pData)
// 功能：输出结构体类型指针指向的数据区中的数据
// 参数：
//       [const void *pData] --- 指向数据区的指针(void *万能指针)
// 返回：[void] --- 无
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
void pointOutput(const void *pData)
{
    printf("(%d, %d) ", ((Point2D*)pData)->x, ((Point2D*)pData)->y);
}

//-----------------------------------------------------------------------------------------------
// 名称：void stringFree(void *pData)
// 功能：释放字符型指针指向的数据区
// 参数：
//       [void *pData] --- 指向数据区的指针(void *万能指针)
// 返回：[void] --- 无
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
void stringFree(void *pData)
{
    free((char*)(pData));
}

//-----------------------------------------------------------------------------------------------
// 名称：void intFree(void *pData)
// 功能：释放整型指针指向的数据区
// 参数：
//       [void *pData] --- 指向数据区的指针(void *万能指针)
// 返回：[void] --- 无
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
void intFree(void *pData)
{
    free((int*)(pData));
}

//-----------------------------------------------------------------------------------------------
// 名称：void doubleFree(void *pData)
// 功能：释放浮点型指针指向的数据区
// 参数：
//       [void *pData] --- 指向数据区的指针(void *万能指针)
// 返回：[void] --- 无
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
void doubleFree(void *pData)
{
    free((double*)(pData));
}

//-----------------------------------------------------------------------------------------------
// 名称：void pointFree(void *pData)
// 功能：释放结构体类型指针指向的数据区
// 参数：
//       [void *pData] --- 指向数据区的指针(void *万能指针)
// 返回：[void] --- 无
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
void pointFree(void *pData)
{
    free((Point2D*)(pData));
}
