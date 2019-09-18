// 功能：根据关键字得到当前节点的指针和前驱节点的指针
void GetPrevCurByKey(ListNode *pList, int nKey, 
                ListNode **pPrev, ListNode **pCur)
{
    // p记录当前节点指针，q记录前驱节点的指针
    ListNode *p = pList, *q = NULL;

    while(p != NULL && p->data != nKey)
    {
        q = p; // 调整前驱节点的指针为当前节点
        p = p->next; // 指向下一个节点
    }

    *pPrev = q; // 更新传入的指针指向内存的内容
    *pCur = p; // 更新传入的指针指向内存的内容
}
