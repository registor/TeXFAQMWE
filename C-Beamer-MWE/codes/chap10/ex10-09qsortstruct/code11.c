// 名称：int main(void)
int main(void)
{
    StuNodePt *pStu = NULL; // 防止野指针
    ...
    // 动态创建数组
    pStu = CreateStructArray(N);
    ...
    // 升序排序
    QSortArray(pStu, N, Greater);
    ...
    // 降序排序
    QSortArray(pStu, N, Lesser);
    ....
    // 遍历释放各个元素及其字符串内存
    Traversal(pStu, N, DestroyNode);
    // 释放指针数组
    free(pStu);
    pStu = NULL; // 防止野指针
    return 0;
}
// 功能：qsort函数用到的升序比较函数
int Greater(const void *pa, const void *pb)
{
    // 需要先转换为(StuNodePt*)指针
    StuNodePt *p1 = (StuNodePt *)pa;
    StuNodePt *p2 = (StuNodePt *)pb;

    // 必须在(*p1)和(*p2)使用小括号，否则有优先级问题
    return ((*p1)->ID - (*p2)->ID); 
}
// 功能：qsort函数用到的降序比较函数
int Lesser(const void *pa, const void *pb)
{
    // 需要先转换为(StuNodePt*)指针
    StuNodePt *p1 = (StuNodePt *)pa;
    StuNodePt *p2 = (StuNodePt *)pb;

    // 必须在(*p1)和(*p2)使用小括号，否则有优先级问题
    return ((*p2)->ID - (*p1)->ID); 
}
