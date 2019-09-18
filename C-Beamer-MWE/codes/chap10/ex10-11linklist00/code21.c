...
struct node a1, a2, a3, a4, a5, a6;
struct node *phead = &a1;
a1.pnext = &a2;
a2.pnext = &a3;
a3.pnext = &a4;
a4.pnext = &a5;
a5.pnext = &a6;
a6.pnext = NULL; // NULL是一个宏(#define NULL 0)，称为空指针
...
// 声明结构体类型变量，并初始化
struct node a7 = {7, NULL};
...
// 插入一个节点
a3.pnext = &a7;
a7.pnext = &a4;
