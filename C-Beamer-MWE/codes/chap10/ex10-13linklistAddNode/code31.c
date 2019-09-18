//----------------------------------------------------------
// 名称：void AddHeadWithDummyNode(ListNode *pHead, int iVal)
// 功能：头插法插入一个节点(有头节点或哑元节点或Dummy Node)
// 参数：
//       [ListNode *pHead] --- 指向链表头节点的指针
//       [int iVal] --- 插入节点的数据
// 返回：无
// 作者：耿楠
// 日期：2017年11月06日
//----------------------------------------------------------
void AddHeadWithDummyNode(ListNode *pHead, int iVal)
{
    ListNode *pNewNode = (ListNode*)malloc(sizeof(ListNode));

    if(pNewNode == NULL)
    {
        return;
    }

    pNewNode->data = iVal;
    pNewNode->next = pHead->next;
    pHead->next = pNewNode;  // 哑元头节点指向了新节点
}
