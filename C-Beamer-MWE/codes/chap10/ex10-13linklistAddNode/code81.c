// 功能：根据关键字，删除一个节点(无头节点)
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
