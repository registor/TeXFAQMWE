// 功能：根据关键字，删除一个节点(有头节点)
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
