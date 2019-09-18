// 功能：创建带有头节点的链表
ListNode *CreateLinkList()
{
    char *pStr;
    int *pInt;
    double * pDouble;
    Point2D * pt;

    ListNode * pHead = NULL;

    pHead = (ListNode *)malloc(sizeof(ListNode));
    pHead->data = NULL;
    pHead->dataType = INT;
    pHead->next = NULL;
    pHead->pPrintFun = NULL;
    pHead->pFreeFun = NULL;

    // string型节点
    pStr = (char* )malloc(81 * sizeof(char));
    strcpy(pStr, "Hello heterogeneous linked list!");
    AddHeadWithDummyNode(pHead, (void *)pStr, STRING);

    // int型节点
    pInt = (int* )malloc(sizeof(*pInt));
    *pInt = 10;
    AddHeadWithDummyNode(pHead, (void *)pInt, INT);

    // double型节点
    pDouble = (double* )malloc(sizeof(*pDouble));
    *pDouble = 3.14;
    AddHeadWithDummyNode(pHead, (void *)pDouble, DOUBLE);

    // 结构体型节点
    pt = (Point2D* )malloc(sizeof(*pt));
    pt->x = 34;
    pt->y = 108;
    AddHeadWithDummyNode(pHead, (void *)pt, PT2D);

    return pHead;
}
