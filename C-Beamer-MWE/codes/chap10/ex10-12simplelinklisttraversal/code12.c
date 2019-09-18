//--------------------------------------------------
// 名称：void TraverseList(struct node * pHead,
//            void (*pf)(const struct node *))
// 功能：遍历链表
// 参数：
//   [struct node * pHead] --- 链表头节点指针
//   [void (*pf)(const struct node *)] --- 函数指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月03日
//------------------------------------------------
void TraverseList(struct node * pHead, 
             void (*pf)(const struct node *))
{ 
    //将头节点的指针给予临时节点指针p
    struct node * p = pHead; 

    while(p != NULL) //节点p不为空，循环
    {
        pf(p);
        p = p->pnext;
    }

    return ;
}
// 功能：输出节点数据
void OutputNode(const struct node * pNode)
{
    printf("%d ", pNode->data);
}
