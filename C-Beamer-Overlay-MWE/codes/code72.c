// 功能：将一个节点插入到指定关键字节点之前(无头节点)
ListNode * InsertByKeyWithoutDummyNode(ListNode *pList, int nKey, int nVal)
{
    // pCur记录当前节点指针，pPrev记录前驱节点的指针
    ListNode *pCur = NULL, *pPrev = NULL;
    // 获得插入点当前节点指针和前驱节点的指针
    GetPrevCurByKey(pList, nKey, &pPrev, &pCur);
    if(pCur == NULL){  // 没有找到    
        return pList;
    }

    if(pPrev == NULL){ // 第1个节点    
        pList = AddHeadRetHead(pList, nVal); // 头插法插入一个节点
    }
    else{ // 其它节点
        ListNode *pNewNode = (ListNode *)malloc(sizeof(ListNode));
        if(pNewNode == NULL){
            return pList; // 创建新节点失败，返回原头指针
        }
        pNewNode->data = nVal;
        pNewNode->next = pPrev->next;
        pPrev->next = pNewNode;
    }
    return pList;
}
