//----------------------------------------
// 名称：void DestroyList(ListNode **pHead)
// 功能：销毁链表
// 参数：
//  [ListNode **pHead] --- 链表头指针的指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月06日
//----------------------------------------
void DestroyList(ListNode **pHead)
{
    ListNode *p;

    while(*pHead != NULL)
    {
        p = (*pHead)->next;
        free(*pHead);
        *pHead = p;
    }
}
