// 函数定义
// 遍历数组
void Traversal(int *pa, int n, void (*pf)(int *))
{
    int *p;

    // 遍历数组，使用指针进行操作
    for(p = pa; p < pa + n; p++)
    {
        pf(p); // 调用传入的函数
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
    // 输出
    printf("%d ", *pData);
}

// 清0
void Set2Zero(int * pData)
{
    *pData = 0; // 清0
}

// 奇数元素求平方
void PowOdd(int * pData)
{
    if(*pData % 2 != 0)
    {
        *pData *= *pData;
    }
}
