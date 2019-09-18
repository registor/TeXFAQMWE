// 功能：将一个节点插入到指定关键字节点之前(有头节点)
void InsertByKeyWithDummyNode(ListNode *pList, int nKey, int nVal)
{
    // pCur记录当前节点指针，pPrev记录前驱节点的指针
    ListNode *pPrev = NULL, *pCur = NULL;

    // 获得插入点当前节点指针和前驱节点的指针
    GetPrevCurByKey(pList->next, nKey, &pPrev, &pCur);

    if(pPrev == NULL)  // 前驱节点为空，将其指向头节点
    {
        pPrev = pList;
    }

    ListNode *pNewNode = (ListNode *)malloc(sizeof(ListNode));

    if(pNewNode == NULL)
    {
        return; // 创建新节点失败，返回
    }

    pNewNode->data = nVal;
    pNewNode->next = pPrev->next; // 指向下一个节点
    pPrev->next = pNewNode; // 前驱节点指向插入的节点
}
