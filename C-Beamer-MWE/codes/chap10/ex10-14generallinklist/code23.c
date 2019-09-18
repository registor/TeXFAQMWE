// 名称：void CreateStrLinkList(ListNode * pHead)
void CreateStrLinkList(ListNode * pHead)
{
    char *p;

    p = (char* )malloc(10 * sizeof(char));
    strcpy(p, "hello ");
    // 头插法插入到链表(注意：需要把数据指针转换为void*类型的指针)
    AddHeadWithDummyNode(pHead, (void *)p);

    p = (char* )malloc(10 * sizeof(char));
    strcpy(p, "void ");
    // 头插法插入到链表(注意：需要把数据指针转换为void*类型的指针)
    AddHeadWithDummyNode(pHead, (void *)p);

    p = (char* )malloc(10 * sizeof(char));
    strcpy(p, "Pointer! ");
    // 头插法插入到链表(注意：需要把数据指针转换为void*类型的指针)
    AddHeadWithDummyNode(pHead, (void *)p);
}
