// 功能：尾插法插入一个节点(有头节点或哑元节点或Dummy Node)
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
