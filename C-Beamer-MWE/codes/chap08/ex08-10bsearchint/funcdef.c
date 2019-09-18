// 函数定义
// 比较函数
int cmp(const void *a, const void *b)
{
    // 需要先转换为(int*)指针
    // 然后用*(int*)取内容
    return(*(int *)a - * (int *)b);
}
// 查找函数
int *Search(int *pKey, int *pa, int n)
{
    int *pResult;

    pResult = (int*)bsearch(pKey, pa, n,  
               sizeof(pa[0]), cmp);
    return pResult;
}
// 输出查找结果
void SearchOut(int *pSearch, int iKey)
{
    if(pSearch != NULL)
    {
        printf("%d was found!\n", iKey);
    }
    else
    {
        printf("%d was not found!\n", iKey);
    }
}
...
