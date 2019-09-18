...
struct node
{
    int data;
    struct node *pnext;
};
...
struct node a1,a2,a3,a4,a5,a6;
struct node *phead = &a1;
a1.pnext = &a2;
a2.pnext = &a3;
a3.pnext = &a4;
a4.pnext = &a5;
a5.pnext = &a6;
a6.pnext = NULL;
...
