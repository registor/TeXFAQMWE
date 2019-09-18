#include <stdio.h>

// 节点结构体类型声明
struct node
{
    int data;
    struct node *pnext; // 指针成员
};

// 函数原型
void TraverseList(struct node *, 
              void (*)(const struct node *) ); 
void OutputNode(const struct node *); 
int main(void)

{
    // 声明结构体类型变量
    struct node a1, a2, a3, a4, a5, a6;
    // 声明链表头节点指针
    struct node *phead = &a1;
    // 声明结构体类型变量，并初始化
    struct node a7 = {7, NULL};
    printf("creating...\n");
    ...
    a6.pnext = NULL;
    TraverseList(phead, OutputNode); // 遍历链表
    printf("\n");
    ...
    return 0;
}
