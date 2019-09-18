// 功能：根据数据域的关键字在链表中进行搜索
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

// 功能：对节点的数据域执行平方运算
void Pow2Node(ListNode * pNode)
{
    pNode->data *= pNode->data ;
}


