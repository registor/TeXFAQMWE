// 功能：遍历链表
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
// 功能：销毁链表
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
