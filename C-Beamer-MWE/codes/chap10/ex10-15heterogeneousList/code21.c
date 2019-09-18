//---------------------------------------------------------------
// 名称：ListNode * CreateNewNode(void *pData, DataType dataType)
// 功能：创建新节点
// 参数：
//       [void *pData] --- 数据区指针
//       [DataType dataType] --- 数据类型枚举
// 返回：[ListNode *] --- 一个节点的指针
// 作者：耿楠
// 日期：2017年11月08日
//---------------------------------------------------------------
ListNode * CreateNewNode(void *pData, DataType dataType)
{
    // 动态分配内存
    ListNode *pNewNode = (ListNode *)malloc(sizeof(*pNewNode));

    // 赋值
    pNewNode->data = pData;
    pNewNode->dataType = dataType;
    pNewNode->next = NULL;
    pNewNode->pPrintFun = pfP[dataType];
    pNewNode->pFreeFun = pfF[dataType];

    return pNewNode;
}
