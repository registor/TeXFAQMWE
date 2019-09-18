/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示异质链表的基本操作。
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

// 节点数据类型的枚举常量
typedef enum datatype
{
    INT,
    DOUBLE,
    STRING,
    PT2D
} DataType;

// 二维点结构体类型
typedef struct pointer
{
    int x;
    int y;
} Point2D;

// 链表节点结构体类型
typedef struct node
{
    void *data;                    // 数据域指针，指向该节点存储的数据(首地址)
    DataType dataType;      // 数据域数据类型的枚举值
    struct node *next;         // 指向下一个链表节点

    void (*pPrintFun)(const void *); // 输出节点的数据函数指针
    void (*pFreeFun)(void *);   // 销毁节点占有的内存的函数指针
} ListNode;

// 函数原型
// 链表操作函数
ListNode *CreateLinkList(); // 创建带有头节点的链表

ListNode * CreateNewNode(void *, DataType); // 建立新节点

void AddHeadWithDummyNode(ListNode *, void *, DataType); // 有头节点的链表的头插法
void TraverseList(ListNode *); // 遍历链表函数原型
void DestroyList(ListNode **); // 销毁链表

// 数据输出函数
void stringOutput(const void *);
void intOutput(const void *);
void doubleOutput(const void *);
void pointOutput(const void *);

// 内存释放函数
void stringFree(void *data);
void intFree(void *data);
void doubleFree(void *data);
void pointFree(void *data);

// 函数指针全局数组，每个元素赋值为函数名称(首地址)
void (*pfP[])(const void *) =
{
    intOutput,
    doubleOutput,
    stringOutput,
    pointOutput
};

void (*pfF[])(void *) =
{
    intFree,
    doubleFree,
    stringFree,
    pointFree
};

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

    pHead = CreateLinkList();
    TraverseList(pHead);
    DestroyList(&pHead);

    return 0;
}

//-----------------------------------------------------------------------------------------------
// 名称：void TraverseList(ListNode * pHead)
// 功能：遍历链表
// 参数：
//       [ListNode * pHead] --- 链表头节点指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
void TraverseList(ListNode * pHead)
{
    ListNode * p = pHead->next; // 跳过头节点

    while(p != NULL) //节点p不为空，循环
    {
        p->pPrintFun(p->data); // 通过结构体中存储的函数指针调用输出节点中的数据的函数
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
void DestroyList(ListNode **pHead)
{
    ListNode *p;

    while(*pHead != NULL)
    {
        p = (*pHead)->next;
        if((*pHead)->data != NULL)
        {
            // 数据域指针不为NULL，销毁其指向的数据区
            (*pHead)->pFreeFun((*pHead)->data);
        }
        free(*pHead);
        *pHead = p;
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void AddHeadWithDummyNode(ListNode *pHead, void * pData, DataType dataType)
// 功能：头插法插入一个节点(有头节点或哑元节点或Dummy Node)
// 参数：
//       [ListNode *pHead] --- 指向链表头节点的指针
//       [void * pData] --- 插入节点的数据指针
//       [DataType dataType] --- 链表节点数据类型枚举
// 返回：无
// 作者：耿楠
// 日期：2017年11月06日
//-----------------------------------------------------------------------------------------------
void AddHeadWithDummyNode(ListNode *pHead, void * pData, DataType dataType)
{
    ListNode *pNewNode = CreateNewNode(pData, dataType); // 创建新节点

    if(pNewNode == NULL)
    {
        return;
    }

    pNewNode->next = pHead->next;
    pHead->next = pNewNode;  // 哑元头节点指向了新节点
}

//-----------------------------------------------------------------------------------------------
// 名称：ListNode *CreateLinkList()
// 功能：创建带有头节点的链表
// 参数：
//       无
// 返回：[ListNode *] --- 链表头指针
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
ListNode *CreateLinkList()
{
    char *pStr;
    int *pInt;
    double * pDouble;
    Point2D * pt;

    ListNode * pHead = NULL;

    pHead = (ListNode *)malloc(sizeof(ListNode));
    pHead->data = NULL;
    pHead->dataType = INT;
    pHead->next = NULL;
    pHead->pPrintFun = NULL;
    pHead->pFreeFun = NULL;

    // string型节点
    pStr = (char* )malloc(81 * sizeof(char));
    strcpy(pStr, "Hello heterogeneous linked list!");
    AddHeadWithDummyNode(pHead, (void *)pStr, STRING);

    // int型节点
    pInt = (int* )malloc(sizeof(*pInt));
    *pInt = 10;
    AddHeadWithDummyNode(pHead, (void *)pInt, INT);

    // double型节点
    pDouble = (double* )malloc(sizeof(*pDouble));
    *pDouble = 3.14;
    AddHeadWithDummyNode(pHead, (void *)pDouble, DOUBLE);

    // 结构体型节点
    pt = (Point2D* )malloc(sizeof(*pt));
    pt->x = 34;
    pt->y = 108;
    AddHeadWithDummyNode(pHead, (void *)pt, PT2D);

    return pHead;
}

//-----------------------------------------------------------------------------------------------
// 名称：ListNode * CreateNewNode(void *pData, DataType dataType)
// 功能：创建新节点
// 参数：
//       [void *pData] --- 数据区指针
//       [DataType dataType] --- 数据类型枚举
// 返回：[ListNode *] --- 一个节点的指针
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
ListNode * CreateNewNode(void *pData, DataType dataType)
{
    // 动态分配内存
    ListNode *pNewNode = (ListNode *)malloc(sizeof(*pNewNode));

    // 赋值
    pNewNode->data = pData;
    pNewNode->dataType = dataType;
    pNewNode->next = NULL;
    pNewNode->pPrintFun = pfP[dataType];
    pNewNode->pFreeFun = pfF[dataType];

    return pNewNode;
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
    if(pData != NULL)
    {
        printf("%s\n", (char*)(pData));
    }
    else
    {
        printf("empty node data.\n");
    }
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
    if(pData != NULL)
    {
       printf("%d ", *(int*)(pData));
    }
    else
    {
        printf("empty node data.\n");
    }
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
    if(pData != NULL)
    {
       printf("%.4f ", *(double*)(pData));
    }
    else
    {
        printf("empty node data.\n");
    }
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
    if(pData != NULL)
    {
       printf("(%d, %d) ", ((Point2D*)pData)->x, ((Point2D*)pData)->y);
    }
    else
    {
        printf("empty node data.\n");
    }
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
