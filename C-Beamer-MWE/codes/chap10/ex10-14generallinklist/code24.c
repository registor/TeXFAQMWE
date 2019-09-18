// 功能：创建结构体类型链表(有头节点)
void CreatePt2DLinkList(ListNode * pHead)
{
    Point2D *p;

    // 置随机种子
    srand(time(NULL));

    for(int i = 0; i < 10; i++)
    {
        p = (Point2D* )malloc(sizeof(*p)); // 申请内存空间
        // 取[a,b)之间的随机整数（包括a，但不包括b)，
        // 使用通用公式：  (rand() % (b - a)) + a
        p->x = rand() % 20 - 10;;
        p->y = rand() % 20 - 10;;
        // 头插法插入到链表(注意：需要把数据指针转换为void*类型的指针)
        AddHeadWithDummyNode(pHead, (void *)p);
    }
}
