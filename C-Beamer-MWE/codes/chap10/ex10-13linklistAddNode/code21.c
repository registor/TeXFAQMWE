// 功能：尾插法插入一个节点(返回链表头指针)
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
