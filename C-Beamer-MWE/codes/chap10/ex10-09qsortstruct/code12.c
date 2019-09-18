// 功能：创建动态数组
StuNodePt * CreateStructArray(int n)
{
    int i;
    StuNodePt *p;
    // 分配指针数组
    p = (StuNodePt *)malloc(n * sizeof(StuNodePt));
    if(p == NULL){
        return NULL;  // 内存分配出错，返回NULL
    }
    // 分配结构体变量内存
    for(i = 0; i < n; i++)
    {
        p[i] = (StuNodePt)malloc(1 * sizeof(StuNode));
        if(p[i] == NULL)
        {
            return NULL;  // 内存分配出错，返回NULL
        }
        Input(p[i]); // 为一个变量读入数据
    }
    return p;
}
// 功能：销毁当前元素中的动态数据及自身占用的内存
void DestroyNode(StuNodePt pNode)
{
    // 释放节点中动态分配的内存
    free(pNode->name);
    pNode->name = NULL; // 防止野指针
    free(pNode->gender);
    pNode->name = NULL; // 防止野指针
    // 释放自己
    free(pNode);
    pNode = NULL; // 防止野指针
}
// 功能：调用qsort函数的包装器函数
void QSortArray(StuNodePt *pa, int n,
  int (*pf)(const void *, const void *))
{
    // 调用qsort函数排序
    qsort(pa, n, sizeof(pa[0]), pf); 
}
