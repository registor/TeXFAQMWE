/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示链表的基本概念和遍历操作。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月05日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月05日
------------------------------------------------------------------------------------*/
#include <stdio.h>

// 节点结构体类型声明
struct node
{
    int data;
    struct node *pnext; // 自身结构体地址类型的指针成员
};

// 函数原型
void TraverseList(struct node *, void (*)(const struct node *) ); // 遍历链表函数原型
void OutputNode(const struct node *); //  输出一个节点的数据

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
    // 声明结构体类型变量
    struct node a1, a2, a3, a4, a5, a6;
    // 声明链表头节点指针
    struct node *phead = &a1;
    // 声明结构体类型变量，并初始化
    struct node a7 = {7, NULL};

    printf("creating...\n");
    // 节点数据赋值
    a1.data = 1;
    a1.pnext = &a2;
    a2.data = 2;
    a2.pnext = &a3;
    a3.data = 3;
    a3.pnext = &a4;
    a4.data = 4;
    a4.pnext = &a5;
    a5.data = 5;
    a5.pnext = &a6;
    a6.data = 6;
    a6.pnext = NULL; // NULL是一个宏(#define NULL 0)，称为空指针


    TraverseList(phead, OutputNode); // 调用遍历链表函数
    printf("\n");

    printf("inserting...\n");
    // 插入一个节点
    a3.pnext = &a7;
    a7.pnext = &a4;
    TraverseList(phead, OutputNode); // 调用遍历链表函数
    printf("\n");

    printf("deleting...\n");
    // 删除一个节点
    a4.pnext = &a6;
    a5.pnext = NULL;
    TraverseList(phead, OutputNode); // 调用遍历链表函数
    printf("\n");

    return 0;
}

//-----------------------------------------------------------------------------------------------
// 名称：void TraverseList(struct node * pHead, void (*pf)(const struct node *))
// 功能：遍历链表
// 参数：
//       [struct node * pHead] --- 链表头节点指针
//       [void (*pf)(const struct node *)] --- 处理节点的函数指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月03日
//-----------------------------------------------------------------------------------------------
void TraverseList(struct node * pHead, void (*pf)(const struct node *))
{
    struct node * p = pHead; //将头节点的指针给予临时节点指针p

    while(p != NULL) //节点p不为空，循环
    {
        pf(p);
        p = p->pnext;
    }

    return ;
}

//-----------------------------------------------------------------------------------------------
// 名称：void OutputNode(const struct node * pNode)
// 功能：输出节点数据
// 参数：
//       [const struct node * pNode] --- 链表节点指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月03日
//-----------------------------------------------------------------------------------------------
void OutputNode(const struct node * pNode)
{
    printf("%d ", pNode->data);
}

