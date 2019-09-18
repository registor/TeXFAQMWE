// 函数定义
// 遍历数组
void Traversal(int a[], int n, 
            void (*pf)(int *))
{
    int i;
    // 遍历数组
    for(i = 0; i < n; i++)
    {
        pf(&a[i]); // 调用传入的函数
    }
}
// 输入数据
void Input(int * pData)
{
    scanf("%d", pData);
}
// 输出数据
void Output(int * pData)
{
    printf("%d ", *pData);
}
// 清0
void Set2Zero(int * pData)
{
    *pData = 0;
}
// 奇数元素求平方
void PowOdd(int * pData)
{
    if(*pData % 2 != 0)
    {
        *pData *= *pData;
    }
}

