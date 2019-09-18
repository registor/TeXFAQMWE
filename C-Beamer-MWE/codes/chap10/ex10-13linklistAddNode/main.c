/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示无头节点(哑元节点或Dummy Node)的动态链表的
*           创建和遍历操作。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月06日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月06日
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 节点结构体类型声明
typedef struct node
{
    int data;
    struct node *next; // 自身结构体地址类型的指针成员
} ListNode;

// 函数原型
// 头插和尾插
ListNode * AddHeadRetHead(ListNode *, int); // 头插法插入一个节点，返回头指针
ListNode * AddTailRetHead(ListNode *, int); // 尾插法插入一个节点，返回头指针
void AddHeadModifyHead(ListNode **, int); // 头插法插入一个节点，修改头指针
void AddTailModifyHead(ListNode **, int); // 尾插法插入一个节点，修改头指针
void AddHeadWithDummyNode(ListNode *, int); // 有头结点的头插法
void AddTailWithDummyNode(ListNode *, int); // 有头结点的尾插法

//创建链表
ListNode *CreateWithRetHead(ListNode * (*)(ListNode *, int)); // 利用返回头指针的方式创建链表
ListNode *CreateWithModifyHead(void (*)(ListNode **, int)); // 利用修改头指针的方式创建链表
ListNode *CreateWithDummyNode(void (*)(ListNode *, int)); // 创建带有头节点链表
ListNode *CreateSortedLinkListWithoutDummyNode(bool (*)(int, int)); // 创建无头节点的有序链表
ListNode *CreateSortedLinkListWithDummyNode(bool (*)(int, int)); // 创建有头节点的有序链表

// 遍历和搜索链表
void TraverseList(ListNode *, void (*)(const ListNode *) ); // 遍历链表函数原型
ListNode * SearchList(ListNode *, int, void (*)(ListNode *)); // 搜索链表
// 遍历和搜索链表用到的功能函数
void OutputNode(const ListNode *); //  输出一个节点的数据
void Pow2Node(ListNode *); //  对节点的数据域执行平方运算
// 销毁链表
void DestroyList(ListNode **); // 销毁链表

// 获取前驱节点和其前驱节点的指针
void GetPrevCurByIdx(ListNode *, int, ListNode **, ListNode **); // 根据检索位置得到当前节点的指针和其前驱节点的指针
void GetPrevCurByKey(ListNode *, int, ListNode **, ListNode **); // 根据关键字得到当前节点的指针和其前驱节点的指针
void GetPrevCurByRank(ListNode *, int, bool (*)(int, int), ListNode **, ListNode **); // 根据升降序到当前节点的指针和其前驱节点的指针
//用于比较两个整型数的比较函数
bool Greater(int, int); // 大于
bool Lesser(int, int); // 小于

// 在链表中插入节点
ListNode * InsertByIdxWithoutDummyNode(ListNode *, int, int);  // 无头节点，在检索位置前插入节点
ListNode * InsertByKeyWithoutDummyNode(ListNode *, int, int);  // 无头节点，在关键字位置前插入节点
void InsertByIdxWithDummyNode(ListNode *, int, int); // 有头节点，在检索位置前插入节点
void InsertByKeyWithDummyNode(ListNode *, int, int); // 有头节点，在关键字位置前插入节点

// 在链表中删除节点
ListNode * DeleteByIdxWithoutDummyNode(ListNode *, int); // 无头节点，删除检索位置节点
ListNode * DeleteByKeyWithoutDummyNode(ListNode *, int);  // 无头节点，删除关键字位置节点
void DeleteByIdxWithDummyNode(ListNode *, int); // 有头节点，删除检索位置节点
void DeleteByKeyWithDummyNode(ListNode *, int); // 有头节点，删除关键字位置节点


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
    ListNode * pList = NULL; // 防止野指针

    printf("Add before head with return...\n");
    pList = CreateWithRetHead(AddHeadRetHead);
    TraverseList(pList, OutputNode);
    printf("\n");
    DestroyList(&pList);

    printf("Add afert tail with return...\n");
    pList = CreateWithRetHead(AddTailRetHead);
    TraverseList(pList, OutputNode);
    printf("\n");

    printf("Insert before 4...\n");
    pList = InsertByKeyWithoutDummyNode(pList, 4, 15);
    TraverseList(pList, OutputNode);
    printf("\n");

    printf("Delete 3...\n");
    pList = DeleteByKeyWithoutDummyNode(pList, 7);
    TraverseList(pList, OutputNode);
    printf("\n");

    printf("Insert before No.4...\n");
    pList = InsertByIdxWithoutDummyNode(pList, 7, 15);
    TraverseList(pList, OutputNode);
    printf("\n");

    printf("Delete No.3...\n");
    pList = DeleteByIdxWithoutDummyNode(pList, 4);
    TraverseList(pList, OutputNode);
    printf("\n");


    DestroyList(&pList);

    printf("Add before head with double pointer...\n");
    pList = CreateWithModifyHead(AddHeadModifyHead);
    TraverseList(pList, OutputNode);
    printf("\n");
    DestroyList(&pList);

    printf("Add after tail with double pointer...\n");
    pList = CreateWithModifyHead(AddTailModifyHead);
    TraverseList(pList, OutputNode);
    printf("\n");
    DestroyList(&pList);

    printf("Add before head with dummy node...\n");
    pList = CreateWithDummyNode(AddHeadWithDummyNode);
    TraverseList(pList->next, OutputNode);
    printf("\ntotal nodes = %d\n", pList->data);
    DestroyList(&pList);

    printf("Add after tail with dummy node...\n");
    pList = CreateWithDummyNode(AddTailWithDummyNode);
    TraverseList(pList->next, OutputNode);
    printf("\ntotal nodes = %d\n", pList->data);
    //DestroyList(&pList);

    printf("Search list with 3...\n");
    SearchList(pList->next, 3, Pow2Node);
    TraverseList(pList->next, OutputNode);
    printf("\n");

    printf("Insert before 9...\n");
    InsertByKeyWithDummyNode(pList, 9, 16);
    TraverseList(pList->next, OutputNode);
    printf("\n");

    printf("Delete Dummy 16...\n");
    DeleteByKeyWithDummyNode(pList, 16);
    TraverseList(pList->next, OutputNode);
    printf("\n");

    printf("Insert before No.2...\n");
    InsertByIdxWithDummyNode(pList, 10, 16);
    TraverseList(pList->next, OutputNode);
    printf("\n");

    printf("Delete Dummy No.4...\n");
    DeleteByIdxWithDummyNode(pList, 4);
    TraverseList(pList->next, OutputNode);
    printf("\n");
    DestroyList(&pList);

    printf("Create SortedList Without Dummy Node: Lesser...\n");
    pList = CreateSortedLinkListWithoutDummyNode(Lesser);
    TraverseList(pList, OutputNode);
    printf("\n");
    DestroyList(&pList);

    printf("Create SortedList Without Dummy Node: Greater...\n");
    pList = CreateSortedLinkListWithoutDummyNode(Greater);
    TraverseList(pList, OutputNode);
    printf("\n");
    DestroyList(&pList);

    printf("Create SortedList With Dummy Node: Lesser...\n");
    pList = CreateSortedLinkListWithDummyNode(Lesser);
    TraverseList(pList->next, OutputNode);
    printf("\n");
    DestroyList(&pList);

    printf("Create SortedList With Dummy Node: Greater...\n");
    pList = CreateSortedLinkListWithDummyNode(Greater);
    TraverseList(pList->next, OutputNode);
    printf("\n");
    DestroyList(&pList);


    return 0;
}

//-----------------------------------------------------------------------------------------------
// 名称：void TraverseList(ListNode * pList, void (*pf)(const ListNode *))
// 功能：遍历链表
// 参数：
//       [ListNode * pList] --- 链表头节点指针
//       [void (*pf)(const ListNode *)] --- 处理节点的函数指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月06日
//-----------------------------------------------------------------------------------------------
void TraverseList(ListNode * pList, void (*pf)(const ListNode *))
{
    ListNode * p = pList; //将头节点的指针给予临时节点指针p

    while(p != NULL) //节点p不为空，循环
    {
        pf(p);
        p = p->next;
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：ListNode * SearchList(ListNode * pList, int key, void (*pf)(const ListNode *))
// 功能：根据数据域的关键字在链表中进行搜索
// 参数：
//       [ListNode * pList] --- 链表头节点指针
//       [int key] --- 查找关键字
//       [void (*pf)(ListNode *)] --- 处理节点的函数指针
// 返回：[ListNode *] --- 指向数组域与关键字相同的节点的指针，未找到返回NULL
// 作者：耿楠
// 日期：2017年11月07日
//-----------------------------------------------------------------------------------------------
ListNode * SearchList(ListNode * pList, int key, void (*pf)(ListNode *))
{
    // 进行查找判断
    while(pList != NULL && pList->data != key )
    {
        pList = pList->next; // 调整指针位置
    }

    if(pList != NULL && pf != NULL)
    {
        pf(pList); // 若找到，则对找到的节点应用传入的处理函数
    }

    return pList; // 未找到，则移到了链表尾，一定是NULL
}

//-----------------------------------------------------------------------------------------------
// 名称：void OutputNode(const ListNode * pNode)
// 功能：输出节点数据
// 参数：
//       [const ListNode * pNode] --- 链表节点指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月06日
//-----------------------------------------------------------------------------------------------
void OutputNode(const ListNode * pNode)
{
    printf("%d ", pNode->data);
}

//-----------------------------------------------------------------------------------------------
// 名称：void Pow2Node(ListNode * pNode)
// 功能：对节点的数据域执行平方运算
// 参数：
//       [ListNode * pNode] --- 链表节点指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月06日
//-----------------------------------------------------------------------------------------------
void Pow2Node(ListNode * pNode)
{
    pNode->data *= pNode->data ;
}

//-----------------------------------------------------------------------------------------------
// 名称：void DestroyList(ListNode **pHead)
// 功能：销毁链表
// 参数：
//       [ListNode **pHead] --- 链表头指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月06日
//-----------------------------------------------------------------------------------------------
void DestroyList(ListNode **pHead)
{
    ListNode *p;

    while(*pHead != NULL)
    {
        p = (*pHead)->next;
        free(*pHead);
        *pHead = p;
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：ListNode * AddHeadRetHead(ListNode *pList, int iVal)
// 功能：头插法插入一个节点(返回链表头指针)
// 参数：
//       [ListNode *pList] --- 链表头指针
//       [int iVal] --- 插入节点的数据
// 返回：[ListNode *] --- 插入节点后链表头指针
// 作者：耿楠
// 日期：2017年11月06日
//-----------------------------------------------------------------------------------------------
ListNode * AddHeadRetHead(ListNode *pList, int iVal) //
{
    ListNode *pNewNode = NULL; // 防止野指针

    pNewNode = (ListNode*)malloc(sizeof(ListNode)); //分配内存

    if(pNewNode == NULL)
    {
        return pList; // 分配内存出错，返回原头指针
    }

    pNewNode->data = iVal; // 数据域赋值
    pNewNode->next = pList; // 指针域指向链表头

    return pNewNode; // 返回新插入的结点作为新的链表头
}

//-----------------------------------------------------------------------------------------------
// 名称：ListNode * AddTailRetHead(ListNode *pList, int iVal)
// 功能：尾插法插入一个节点(返回链表头指针)
// 参数：
//       [ListNode *pList] --- 链表头指针
//       [int iVal] --- 插入节点的数据
// 返回：[ListNode *] --- 插入节点后链表头指针
// 作者：耿楠
// 日期：2017年11月06日
//-----------------------------------------------------------------------------------------------
ListNode * AddTailRetHead(ListNode *pList, int iVal)
{
    ListNode *pNewNode = NULL; // 防止野指针

    pNewNode = (ListNode*)malloc(sizeof(ListNode)); //分配内存

    if(pNewNode == NULL)
    {
        return pList; // 分配内存出错，返回原链表头指针
    }

    pNewNode->data = iVal; // 数据域赋值
    pNewNode->next = NULL; // 指针域赋NULL，表示链表结束

    if (pList == NULL)
    {
        return pNewNode; // 如果是空链表，则新节点就是链表头
    }

    ListNode *p = pList;

    while (p->next != NULL)   // 移动指针到最后一个节点
    {
        p = p->next;
    }

    p->next = pNewNode; // 在最后一个节点后进行插入

    return pList;
}

//-----------------------------------------------------------------------------------------------
// 名称：void AddHeadModifyHead(ListNode **pHead, int iVal)
// 功能：头插法插入一个节点(通过传入的链表头指针的地址修改链表头指针)
// 参数：
//       [ListNode **pHead] --- 指向链表头指针的指针
//       [int iVal] --- 插入节点的数据
// 返回：无
// 作者：耿楠
// 日期：2017年11月06日
//-----------------------------------------------------------------------------------------------
void AddHeadModifyHead(ListNode **pHead, int iVal)
{
    ListNode *pNewNode = NULL; // 防止野指针

    pNewNode = (ListNode*)malloc(sizeof(ListNode)); //分配内存

    if(pNewNode == NULL)
    {
        return; // 分配内存出错，返回
    }

    pNewNode->data = iVal; // 数据域赋值
    pNewNode->next = *pHead; // 指针域指向链表头

    *pHead = pNewNode;
}

//-----------------------------------------------------------------------------------------------
// 名称：void AddTailModifyHead(ListNode **pHead, int iVal)
// 功能：尾插法插入一个节点(通过传入的链表头指针的地址修改链表头指针)
// 参数：
//       [ListNode **pHead] --- 指向链表头指针的指针
//       [int iVal] --- 插入节点的数据
// 返回：无
// 作者：耿楠
// 日期：2017年11月06日
//-----------------------------------------------------------------------------------------------
void AddTailModifyHead(ListNode **pHead, int iVal)
{
    ListNode *pNewNode = NULL;

    pNewNode = (ListNode*)malloc(sizeof(ListNode)); //分配内存

    if(pNewNode == NULL)
    {
        return; // 分配内存出错，返回NULL
    }

    pNewNode->data = iVal; // 数据域赋值
    pNewNode->next = NULL; // 指针域赋NULL，表示链表结束

    ListNode *p = *pHead;

    if(p == NULL)
    {
        *pHead = pNewNode; // 如果头指针为空，则直接让头指针指向该节点
    }
    else
    {
        while (p->next != NULL)   // 移动指针到最后一个节点
        {
            p = p->next;
        }

        p->next = pNewNode; // 在最后一个节点后进行插入
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void AddHeadWithDummyNode(ListNode *pHead, int iVal)
// 功能：头插法插入一个节点(有头节点或哑元节点或Dummy Node)
// 参数：
//       [ListNode *pHead] --- 指向链表头节点的指针
//       [int iVal] --- 插入节点的数据
// 返回：无
// 作者：耿楠
// 日期：2017年11月06日
//-----------------------------------------------------------------------------------------------
void AddHeadWithDummyNode(ListNode *pHead, int iVal)
{
    ListNode *pNewNode = (ListNode*)malloc(sizeof(ListNode)); // 创建新节点

    if(pNewNode == NULL)
    {
        return;
    }

    pNewNode->data = iVal;
    pNewNode->next = pHead->next;
    pHead->next = pNewNode;  // 哑元头节点指向了新节点
}

//-----------------------------------------------------------------------------------------------
// 名称：void AddTailWithDummyNode(ListNode *pHead, int iVal)
// 功能：尾插法插入一个节点(有头节点或哑元节点或Dummy Node)
// 参数：
//       [ListNode *pHead] --- 指向链表头节点的指针
//       [int iVal] --- 插入节点的数据
// 返回：无
// 作者：耿楠
// 日期：2017年11月06日
//-----------------------------------------------------------------------------------------------
void AddTailWithDummyNode(ListNode *pHead, int iVal)
{
    ListNode *pNewNode = (ListNode*)malloc(sizeof(ListNode));

    if(pNewNode == NULL)
    {
        return;
    }

    pNewNode->data = iVal;
    pNewNode->next = NULL;

    if (pHead->next == NULL)
    {
        pHead->next = pNewNode;
        return;
    }

    ListNode *p = pHead;

    while (p->next != NULL) // 将指针移动到最后一个节点
    {
        p = p->next;
    }

    p->next = pNewNode; // 在最后一个节点后插入节点
}

//-----------------------------------------------------------------------------------------------
// 名称：ListNode *CreateWithRetHead(ListNode * (*pf)(ListNode *, int))
// 功能：利用返回头指针的方式创建链表
// 参数：
//       [ListNode * (*pf)(ListNode *, int)] --- 头插或尾插节点的函数指针
// 返回：[ListNode *] --- 链表头指针
// 作者：耿楠
// 日期：2017年11月07日
//-----------------------------------------------------------------------------------------------
ListNode *CreateWithRetHead(ListNode * (*pf)(ListNode *, int))
{
    ListNode * pHead = NULL;

    int numbs[] = {1, 2, 3, 4, 5}; // 可以用scanf输入数据
    int i;

    /* 如果没有头节点(哑元节点或Dummy Node)，则第1个节点则是头节点，
       需要用一个指向这一个节点的指针表示链表的起始。
       如果一个函数需要修改链表的头节点(插入或删除)，
       则需要修改这个指向头节点的指针的值，需要函数返
       回一个新的头节点指针。
    */
    for (i = 0; i < 5; i++)
    {
        pHead  = pf(pHead, numbs[i]); // 用返回值更新链表头指针
    }

    return pHead;
}

//-----------------------------------------------------------------------------------------------
// 名称：ListNode *CreateWithModifyHead(void (*pf)(ListNode **, int))
// 功能：利用修改头指针的方式创建链表
// 参数：
//       [void (*pf)(ListNode **, int)] --- 头插或尾插节点的函数指针
// 返回：[ListNode *] --- 链表头指针
// 作者：耿楠
// 日期：2017年11月07日
//-----------------------------------------------------------------------------------------------
ListNode *CreateWithModifyHead(void (*pf)(ListNode **, int))
{
    ListNode * pHead = NULL;

    int numbs[] = {1, 2, 3, 4, 5}; // 可以用scanf输入数据
    int i;

    /* 如果没有头节点(哑元节点或Dummy Node)，第1个节点则是头节点，
       需要用一个指向这一个节点的指针表示链表的起始。
       如果一个函数需要修改链表的头指针(插入或删除)，
       则需要修改这个指向头节点的指针的值，也就是说
       需要给函数传入一个指向这一指针的指针(指针的指针)。
    */
    for (i = 0; i < 5; i++)
    {
        pf(&pHead, numbs[i]); // 用指针的指针更新链表头指针
    }

    return pHead;
}

//-----------------------------------------------------------------------------------------------
// 名称：ListNode *CreateWithDummyNode(void (*pf)(ListNode *, int))
// 功能：创建带有头节点的链表
// 参数：
//       [void (*pf)(ListNode *, int)] --- 头插或尾插节点的函数指针
// 返回：[ListNode *] --- 链表头指针
// 作者：耿楠
// 日期：2017年11月07日
//-----------------------------------------------------------------------------------------------
ListNode *CreateWithDummyNode(void (*pf)(ListNode *, int))
{
    ListNode * pHead = NULL;

    pHead = (ListNode *)malloc(sizeof(ListNode));

    if(pHead == NULL)
    {
        return NULL;
    }

    pHead->data = 0;
    pHead->next = NULL;

    int numbs[] = {1, 2, 3, 4, 5}; // 可以用scanf输入数据
    int i;

    /* 使用头节点(哑元节点或Dummy Node)：
       此时可以给任何函数传入指向哑元节点的指针，
       在函数中能够修改哑元节点的next指针。
       所以不需要使用指向指针的指针进行操作。
    */
    for (i = 0; i < 5; i++)
    {
        pf(pHead, numbs[i]); // 传入头节点的地址
        pHead->data++;
    }

    return pHead;
}

//-----------------------------------------------------------------------------------------------
// 名称：ListNode *CreateSortedLinkListWithoutDummyNode(bool (*pf)(int, int))
// 功能：创建无头节点的有序链表
// 参数：
//           [bool (*pf)(int, int)] --- 比较函数的指针
// 返回：[ListNode *] --- 链表头指针
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
ListNode *CreateSortedLinkListWithoutDummyNode(bool (*pf)(int, int))
{
    ListNode * pHead = NULL;

    // pCur记录当前节点指针，pPrev记录前驱节点的指针
    ListNode *pCur = NULL, *pPrev = NULL;

    int numbs[] = {3, 1, 10, 2, 5}; // 可以用scanf输入数据
    int i;

    for (i = 0; i < 5; i++)
    {
        if(pHead == NULL)
        {
            pHead = AddTailRetHead(pHead, numbs[i]); // 空链表尾插一个节点
        }
        else
        {
            // 获得插入点当前节点指针和前驱节点的指针
            GetPrevCurByRank(pHead, numbs[i], pf, &pPrev, &pCur);

            if(pPrev == NULL) // 第1个节点
            {
                pHead = AddHeadRetHead(pHead, numbs[i]); // 头插法插入一个节点
            }
            else // 其它节点
            {
                ListNode *pNewNode = (ListNode *)malloc(sizeof(ListNode));

                if(pNewNode == NULL)
                {
                    return pHead; // 创建新节点失败，返回原头指针
                }

                pNewNode->data = numbs[i];
                pNewNode->next = pPrev->next;
                pPrev->next = pNewNode;
            }
        }
    }

    return pHead;
}

//-----------------------------------------------------------------------------------------------
// 名称：ListNode *CreateSortedLinkListWithDummyNode(bool (*pf)(int, int))
// 功能：创建有头节点的有序链表
// 参数：
//           [bool (*pf)(int, int)] --- 比较函数的指针
// 返回：[ListNode *] --- 链表头指针
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
ListNode *CreateSortedLinkListWithDummyNode(bool (*pf)(int, int))
{
    // pCur记录当前节点指针，pPrev记录前驱节点的指针
    ListNode *pCur = NULL, *pPrev = NULL;

    ListNode * pHead = NULL;

    // 创建头节点
    pHead = (ListNode *)malloc(sizeof(ListNode));
    if(pHead == NULL)
    {
        return NULL;
    }
    pHead->data = -1;
    pHead->next = NULL;

    int numbs[] = {3, 1, 10, 2, 5}; // 可以用scanf输入数据
    int i;

    for (i = 0; i < 5; i++)
    {
        // 获得插入点当前节点指针和前驱节点的指针
        GetPrevCurByRank(pHead->next, numbs[i], pf, &pPrev, &pCur);

        if(pPrev == NULL)  // 前驱节点为空，将其指向头节点
        {
            pPrev = pHead;
        }

        ListNode *pNewNode = (ListNode *)malloc(sizeof(ListNode));
        if(pNewNode == NULL)
        {
            return pHead; // 创建新节点失败，返回
        }

        pNewNode->data = numbs[i];
        pNewNode->next = pPrev->next; // 指向下一个节点
        pPrev->next = pNewNode; // 前驱节点指向插入的节点
    }

    return pHead;
}

//-----------------------------------------------------------------------------------------------
// 名称：void GetPrevCurByIdx(ListNode *pList, int nIdx, ListNode **pPrev, ListNode **pCur)
// 功能：根据检索位置得到当前节点的指针和其前驱节点的指针
// 参数：
//       [ListNode *pList] --- 链表头指针
//       [int nIdx] --- 检索的位置
//       [ListNode **pPrev] --- 指向前驱节点指针的指针
//       [ListNode **pCur] --- 指向当前节点指针的指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月07日
//-----------------------------------------------------------------------------------------------
void GetPrevCurByIdx(ListNode *pList, int nIdx, ListNode **pPrev, ListNode **pCur)
{
    // p记录当前节点指针，q记录前驱节点的指针
    ListNode *p = pList, *q = NULL;
    int iCount = 0; // 计数器

    while(p != NULL && iCount < nIdx)
    {
        q = p; // 调整前驱节点的指针为当前节点
        p = p->next; // 指向下一个节点
        iCount++; // 计数器加1
    }

    *pPrev = q; // 更新传入的指针指向内存的内容
    *pCur = p; // 更新传入的指针指向内存的内容
}

//-----------------------------------------------------------------------------------------------
// 名称：void GetPrevCurByKey(ListNode *pList, int nKey, ListNode **pPrev, ListNode **pCur)
// 功能：根据关键字得到当前节点的指针和前驱节点的指针
// 参数：
//       [ListNode *pList] --- 链表头指针
//       [int nKey] --- 检索关键字
//       [ListNode **pPrev] --- 指向前驱节点指针的指针
//       [ListNode **pCur] --- 指向当前节点指针的指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月07日
//-----------------------------------------------------------------------------------------------
void GetPrevCurByKey(ListNode *pList, int nKey, ListNode **pPrev, ListNode **pCur)
{
    // p记录当前节点指针，q记录前驱节点的指针
    ListNode *p = pList, *q = NULL;

    while(p != NULL && p->data != nKey)
    {
        q = p; // 调整前驱节点的指针为当前节点
        p = p->next; // 指向下一个节点
    }

    *pPrev = q; // 更新传入的指针指向内存的内容
    *pCur = p; // 更新传入的指针指向内存的内容
}

//-----------------------------------------------------------------------------------------------
// 名称：void GetPrevCurByKey(ListNode *pList, int nKey,
//                      bool (*pf)(int, int), ListNode **pPrev, ListNode **pCur)
// 功能： 根据升降序条件得到当前节点的指针和其前驱节点的指针
// 参数：
//       [ListNode *pList] --- 链表头指针
//       [int nKey] --- 检索关键字
//       [bool (*pf)(int, int)] --- 用于比较两个整型数的函数指针
//       [ListNode **pPrev] --- 指向前驱节点指针的指针
//       [ListNode **pCur] --- 指向当前节点指针的指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
void GetPrevCurByRank(ListNode *pList, int nKey, bool (*pf)(int, int),
                      ListNode **pPrev, ListNode **pCur)
{
    // p记录当前节点指针，q记录前驱节点的指针
    ListNode *p = pList, *q = NULL;

    while(p != NULL && pf(p->data, nKey)) // 调用传入的函数
    {
        q = p; // 调整前驱节点的指针为当前节点
        p = p->next; // 指向下一个节点
    }

    *pPrev = q; // 更新传入的指针指向内存的内容
    *pCur = p; // 更新传入的指针指向内存的内容
}

//-----------------------------------------------------------------------------------------------
// 名称：bool Greater(int a, int b)
// 功能：用于比较两个整型数的大小
// 参数：
//       [int a] --- 第1个数
//       [int b] --- 第2个数
// 返回：[bool] --- a > b返回真，否则返回假
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
bool Greater(int a, int b)
{
    return a > b;
}

//-----------------------------------------------------------------------------------------------
// 名称：bool Lesser(int a, int b)
// 功能：用于比较两个整型数的大小
// 参数：
//       [int a] --- 第1个数
//       [int b] --- 第2个数
// 返回：[bool] --- a < b返回真，否则返回假
// 作者：耿楠
// 日期：2017年11月08日
//-----------------------------------------------------------------------------------------------
bool Lesser(int a, int b)
{
    return a < b;
}

//-----------------------------------------------------------------------------------------------
// 名称：ListNode * InsertByKeyWithoutDummyNode(ListNode *pList, int nKey, int nVal)
// 功能：将一个节点插入到指定关键字节点之前(无头节点)
// 参数：
//       [ListNode *pList] --- 链表头指针
//       [int nKey] --- 检索关键字
//       [int nVal] --- 插入节点的值
// 返回：[ListNode *] --- 链表头指针
// 作者：耿楠
// 日期：2017年11月07日
//-----------------------------------------------------------------------------------------------
ListNode * InsertByKeyWithoutDummyNode(ListNode *pList, int nKey, int nVal)
{
    // pCur记录当前节点指针，pPrev记录前驱节点的指针
    ListNode *pCur = NULL, *pPrev = NULL;

    // 获得插入点当前节点指针和前驱节点的指针
    GetPrevCurByKey(pList, nKey, &pPrev, &pCur);

    if(pCur == NULL)  // 没有找到
    {
        return pList;
    }

    if(pPrev == NULL) // 第1个节点
    {
        pList = AddHeadRetHead(pList, nVal); // 头插法插入一个节点
    }
    else // 其它节点
    {
        ListNode *pNewNode = (ListNode *)malloc(sizeof(ListNode));

        if(pNewNode == NULL)
        {
            return pList; // 创建新节点失败，返回原头指针
        }

        pNewNode->data = nVal;
        pNewNode->next = pPrev->next;
        pPrev->next = pNewNode;
    }

    return pList;
}

//-----------------------------------------------------------------------------------------------
// 名称：ListNode *  InsertByIdxWithoutDummyNode(ListNode *pList, int nIdx, int nVal)
// 功能：将一个节点插入到指定检索位置之前(无头节点)，超出长度在末尾插入
// 参数：
//       [ListNode *pList] --- 链表头指针
//       [int nIdx] --- 检索的位置
//       [int nVal] --- 插入节点的值
// 返回：[ListNode *] --- 链表头指针
// 作者：耿楠
// 日期：2017年11月07日
//-----------------------------------------------------------------------------------------------
ListNode * InsertByIdxWithoutDummyNode(ListNode *pList, int nIdx, int nVal)
{
    // pCur记录当前节点指针，pPrev记录前驱节点的指针
    ListNode *pCur = NULL, *pPrev = NULL;

    // 获得插入点当前节点指针和前驱节点的指针
    GetPrevCurByIdx(pList, nIdx, &pPrev, &pCur);

    if(pPrev == NULL && pCur == NULL)  // 没有找到
    {
        return pList;
    }

    if(pPrev == NULL) // 第1个节点
    {
        pList = AddHeadRetHead(pList, nVal); // 头插法插入一个节点
    }
    else // 其它节点
    {
        ListNode *pNewNode = (ListNode *)malloc(sizeof(ListNode));

        if(pNewNode == NULL)
        {
            return pList; // 创建新节点失败，返回原头指针
        }

        pNewNode->data = nVal;
        pNewNode->next = pPrev->next;
        pPrev->next = pNewNode;
    }

    return pList;
}

//-----------------------------------------------------------------------------------------------
// 名称：void InsertByKeyWithDummyNode(ListNode *pList, int nKey, int nVal)
// 功能：将一个节点插入到指定关键字节点之前(有头节点)
// 参数：
//       [ListNode *pList] --- 链表头指针
//       [int nKey] --- 检索关键字
//       [int nVal] --- 插入节点的值
// 返回：无
// 作者：耿楠
// 日期：2017年11月07日
//-----------------------------------------------------------------------------------------------
void InsertByKeyWithDummyNode(ListNode *pList, int nKey, int nVal)
{
    // pCur记录当前节点指针，pPrev记录前驱节点的指针
    ListNode *pPrev = NULL, *pCur = NULL;

    // 获得插入点当前节点指针和前驱节点的指针
    GetPrevCurByKey(pList->next, nKey, &pPrev, &pCur);

    if(pPrev == NULL)  // 前驱节点为空，将其指向头节点
    {
        pPrev = pList;
    }

    ListNode *pNewNode = (ListNode *)malloc(sizeof(ListNode));

    if(pNewNode == NULL)
    {
        return; // 创建新节点失败，返回
    }

    pNewNode->data = nVal;
    pNewNode->next = pPrev->next; // 指向下一个节点
    pPrev->next = pNewNode; // 前驱节点指向插入的节点
}

//-----------------------------------------------------------------------------------------------
// 名称：void InsertByIdxWithDummyNode(ListNode *pList, int nIdx, int nVal)
// 功能：将一个节点插入到指定检索位置之前(有头节点)，超出长度在末尾插入
// 参数：
//       [ListNode *pList] --- 链表头指针
//       [int nIdx] --- 检索的位置
//       [int nVal] --- 插入节点的值
// 返回：[ListNode *] --- 链表头指针
// 作者：耿楠
// 日期：2017年11月07日
//-----------------------------------------------------------------------------------------------
void InsertByIdxWithDummyNode(ListNode *pList, int nIdx, int nVal)
{
    // pCur记录当前节点指针，pPrev记录前驱节点的指针
    ListNode *pPrev = NULL, *pCur = NULL;

    // 获得插入点当前节点指针和前驱节点的指针
    GetPrevCurByIdx(pList->next, nIdx, &pPrev, &pCur);

    if(pPrev == NULL)  // 前驱节点为空，将其指向头节点
    {
        pPrev = pList;
    }

    ListNode *pNewNode = (ListNode *)malloc(sizeof(ListNode));

    if(pNewNode == NULL)
    {
        return; // 创建新节点失败，返回
    }

    pNewNode->data = nVal;
    pNewNode->next = pPrev->next; // 指向下一个节点
    pPrev->next = pNewNode; // 前驱节点指向插入的节点
}

//-----------------------------------------------------------------------------------------------
// 名称：ListNode * DeleteByKeyWithoutDummyNode(ListNode *pList, int nKey)
// 功能：根据关键字，删除一个节点(无头节点)
// 参数：
//       [ListNode *pList] --- 链表头指针
//       [int nKey] --- 检索关键字
// 返回：[ListNode *] --- 链表头指针
// 作者：耿楠
// 日期：2017年11月07日
//-----------------------------------------------------------------------------------------------
ListNode * DeleteByKeyWithoutDummyNode(ListNode *pList, int nKey)
{
    // pCur记录当前节点指针，pPrev记录前驱节点的指针
    ListNode *pCur = NULL, *pPrev = NULL;

    // 获得插入点当前节点指针和前驱节点的指针
    GetPrevCurByKey(pList, nKey, &pPrev, &pCur);

    if(pCur == NULL)  // 没有找到
    {
        return pList;
    }

    if(pPrev == NULL) // 第1个节点
    {
        pList = pList->next; // 调整头指针
    }
    else // 其它节点
    {
        pPrev->next = pCur->next;
    }

    free(pCur); // 释放空间
    return pList;
}

//-----------------------------------------------------------------------------------------------
// 名称：ListNode *  DeleteByIdxWithoutDummyNode(ListNode *pList, int nIdx)
// 功能：根据检索位置，删除一个节点(无头节点)
// 参数：
//       [ListNode *pList] --- 链表头指针
//       [int nIdx] --- 检索的位置
// 返回：[ListNode *] --- 链表头指针
// 作者：耿楠
// 日期：2017年11月07日
//-----------------------------------------------------------------------------------------------
ListNode * DeleteByIdxWithoutDummyNode(ListNode *pList, int nIdx)
{
    // pCur记录当前节点指针，pPrev记录前驱节点的指针
    ListNode *pCur = NULL, *pPrev = NULL;

    // 获得插入点当前节点指针和前驱节点的指针
    GetPrevCurByIdx(pList, nIdx, &pPrev, &pCur);

    if(pCur == NULL)  // 没有找到
    {
        return pList;
    }

    if(pPrev == NULL) // 第1个节点
    {
        pList = pList->next; // 调用头指针
    }
    else // 其它节点
    {
        pPrev->next = pCur->next;
    }

    free(pCur); // 释放内存空间
    return pList;
}

//-----------------------------------------------------------------------------------------------
// 名称：void DeleteByKeyWithDummyNode(ListNode *pList, int nKey)
// 功能：根据关键字，删除一个节点(有头节点)
// 参数：
//       [ListNode *pList] --- 链表头指针
//       [int nKey] --- 检索关键字
// 返回：无
// 作者：耿楠
// 日期：2017年11月07日
//-----------------------------------------------------------------------------------------------
void DeleteByKeyWithDummyNode(ListNode *pList, int nKey)
{
    // pCur记录当前节点指针，pPrev记录前驱节点的指针
    ListNode *pCur = NULL, *pPrev = NULL;

    // 获得插入点当前节点指针和前驱节点的指针
    GetPrevCurByKey(pList->next, nKey, &pPrev, &pCur);

    if(pCur == NULL)  // 没有找到
    {
        return;
    }

    if(pPrev == NULL) // 第1个节点
    {
        pList->next = pCur->next; // pList->next->next;
    }
    else // 其它节点
    {
        pPrev->next = pCur->next;
    }

    free(pCur); // 释放内存空间
}

//-----------------------------------------------------------------------------------------------
// 名称：void DeleteByIdxWithDummyNode(ListNode *pList, int nIdx)
// 功能：根据检索位置，删除一个节点(有头节点)
// 参数：
//       [ListNode *pList] --- 链表头指针
//       [int nIdx] --- 检索的位置
// 返回：[ListNode *] --- 链表头指针
// 作者：耿楠
// 日期：2017年11月07日
//-----------------------------------------------------------------------------------------------
void DeleteByIdxWithDummyNode(ListNode *pList, int nIdx)
{
    // pCur记录当前节点指针，pPrev记录前驱节点的指针
    ListNode *pCur = NULL, *pPrev = NULL;

    // 获得插入点当前节点指针和前驱节点的指针
    GetPrevCurByIdx(pList->next, nIdx, &pPrev, &pCur);

    if(pCur == NULL)  // 没有找到
    {
        return;
    }

    if(pPrev == NULL) // 第1个节点
    {
        pList->next = pCur->next; // pList->next->next;
    }
    else // 其它节点
    {
        pPrev->next = pCur->next;
    }

    free(pCur); // 释放内存空间
}

