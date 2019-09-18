// 名称：void CreateDoubleLinkList(ListNode * pHead)
void CreateDoubleLinkList(ListNode * pHead)
{
    double *p;

    // 置随机种子
    srand(time(NULL));

    for(int i = 0; i < 10; i++)
    {
        p = (double* )malloc(sizeof(double)); // 申请空间
        *p = rand() / ((double)(RAND_MAX) / 100); // 产生随机浮点数

        // 头插法插入到链表(注意：需要把数据指针转换为void*类型的指针)
        AddHeadWithDummyNode(pHead, (void *)p);
    }
}
