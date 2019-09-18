#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000

// 函数原型
// 创建数组
void CreateArray(int *, int);
// 查找函数
int *Search(int *, int *, int);
// 输出查找结果
void SearchOut(int *, int);
// 数组输出函数
void Output(int *, int);
// 比较函数
int cmp(const void *, const void *);

int main(void)
{
    int iArray[MAX];
    int iKey = 2356;
    int *pSearch;

    CreateArray(iArray, MAX);
    Output(iArray, MAX);

    printf("\nSorting...\n\n");
    // 调用快速排序函数，注意比较函数指针的使用
    qsort(iArray, MAX, sizeof(iArray[0]), cmp);
    Output(iArray, MAX);

    // 二分查找
    pSearch = Search(&iKey, iArray, MAX);
    // 输出查找结果
    SearchOut(pSearch, iKey);

    return(0);
}

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

    pResult = (int*)bsearch(pKey, pa, n,  sizeof(pa[0]), cmp);

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

// 采用随机函数创建数组
void CreateArray(int *pa, int n)
{
    int i;

    // 用时间做随机种子，产生不同随机数
    srand((unsigned)time(NULL));

    for (i = 0; i < n; i++)
    {
        // 产生[0, n)之间的随机数
        pa[i] = rand() % n;
    }
}

// 输出数据
void Output(int * pData, int n)
{
    int i;

    // n - 1不输出最后一个数
    for(i = 0; i < n - 1; i++)
    {
        printf("%d ", pData[i]);
    }
    // 最后不输出空格，并输出\n
    printf("%d\n", pData[i]);
}
