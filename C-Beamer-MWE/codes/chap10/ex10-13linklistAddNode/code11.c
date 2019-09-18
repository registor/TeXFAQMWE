//-----------------------------------------------------------
// 功能：头插法插入一个节点(返回链表头指针)
// 参数：
//       [ListNode *pList] --- 链表头指针
//       [int iVal] --- 插入节点的数据
// 返回：[ListNode *] --- 插入节点后链表头指针
//-----------------------------------------------------------
ListNode * AddHeadRetHead(ListNode *pList, int iVal) 
{
    ListNode *pNewNode = NULL; // 防止野指针

    pNewNode = (ListNode*)malloc(sizeof(ListNode)); //分配内存
    if(pNewNode == NULL)
    {
        return pList; // 分配内存出错，返回原头指针
    }
    pNewNode->data = iVal; // 数据域赋值
    pNewNode->next = pList; // 指针域指向链表头

    return pNewNode; // 返回新插入的结点作为新的链表头
}
