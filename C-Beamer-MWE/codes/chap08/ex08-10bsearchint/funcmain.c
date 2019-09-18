#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10000
// 函数原型
...
// 查找函数
int *Search(int *, int *, int);
// 输出查找结果
void SearchOut(int *, int);
...
// 比较函数
int cmp(const void *, const void *);

int main(void)
{
    int iArray[MAX];
    int iKey = 2356;
    int *pSearch;
    ...    
    // 调用快速排序函数，注意比较函数指针的使用
    qsort(iArray, MAX, sizeof(iArray[0]), cmp);
    ...    
    // 二分查找
    pSearch = Search(&iKey, iArray, MAX);
    // 输出查找结果
    SearchOut(pSearch, iKey);

    return(0);
}
