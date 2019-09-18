#include <stdio.h>
#include <stdlib.h>

#define N 10

//函数原型
// 数组遍历
void Traversal(int *, int, void (*pf)(int *));
// 选择排序（函数指针用于实现比较升/降序）
void SelectionSort(int *, int, int (*)(int, int));
// 插入排序（函数指针用于实现比较升/降序）
void InsertSort(int *, int, int (*)(int, int));
// 递归快速排序
void QuickSort(int *, int, int, int (*)(int, int));
// 快速排序中的分割函数
int Split(int *, int, int, int (*)(int, int));

// 二分查找
int BiSearch(int *, int, int, int (*)(int, int));
// 递归二分查找
int ReBiSearch(int *, int, int, int, int (*)(int, int));

// 功能函数
void Input(int *);
void Output(int *);
// 交换数据
void Swap(int *, int *);
// 比较函数
int Greater(int, int);
int Lesser(int, int);

int main()
{
    int iArray[N];

    // 把输入重定向到文件"data.txt"
    freopen("data.txt", "r", stdin);
    Traversal(iArray, N, Input);
    // 把输入重定向回键盘
    freopen("CON", "r", stdin);
    Traversal(iArray, N, Output);
    printf("\n");

//    // 升序排序
//    SelectionSort(iArray, N, Greater);
//    Traversal(iArray, N, Output);
//    printf("\n");
//
//    // 降序排序
//    SelectionSort(iArray, N, Lesser);
//    Traversal(iArray, N, Output);
//    printf("\n");
//    // 升序排序
//    InsertSort(iArray, N, Greater);
//    Traversal(iArray, N, Output);
//    printf("\n");
//
//    // 降序排序
//    InsertSort(iArray, N, Lesser);
//    Traversal(iArray, N, Output);
//    printf("\n");

    // 升序排序
    QuickSort(iArray, 0, N - 1, Greater);
    Traversal(iArray, N, Output);
    printf("\n");

    printf("pos = %d\n", ReBiSearch(iArray, 0, N - 1, 9, Greater));

    // 降序排序
    QuickSort(iArray, 0, N - 1, Lesser);
    Traversal(iArray, N, Output);
    printf("\n");

    printf("pos = %d\n", ReBiSearch(iArray, 0, N - 1, 9, Lesser));

    return 0;
}

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

// 交换两个数
void Swap(int *pa, int *pb)
{
    int temp;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

// 比较两个整数
int Greater(int a, int b)
{
    return (a > b) ? 1 : 0;
}

int Lesser(int a, int b)
{
    return (a < b) ? 1 : 0;
}

// 采用选择排序对数组排序
void SelectionSort(int *pa, int n, int (*pf)(int, int))
{
    int i, j;
    int pos = 0; // 选择的位置

    for(i = 0; i < n - 1; i++)
    {
        pos = i; // 每次将pos置为无序数组的起始位置
        for(j = i + 1; j < n; j++) // 遍历无序数组，找到位置
        {
            // 调用传入的比较函数
            if(pf(pa[pos], pa[j]))
            {
                pos = j; // 更新位置
            }
        }
        // 如果不是无序数组的起始位置，则交换
        if(pos != i)
        {
            // 利用指针操作数组
            Swap(pa + i, pa + pos);
        }
    }
}

// 采用插入排序对数组排序
void InsertSort(int *pa, int n, int (*pf)(int, int))
{
    int i, j;
    int temp = 0; // 临时变量

    // 假定第1个元素是有序的，需要进行n-1次插入
    for(i = 1; i < n; i++)
    {
        // 把待排序的元素赋给temp
        temp = pa[i];
        // 初始化j
        j = i - 1;
        // 利用while循环将不符合位置的元素后移一个位置
        while((j >= 0) && pf(temp, pa[j]))
        {
            // 顺序比较和移动
            pa[j + 1] = pa[j];
            j--;
        }
        // 将元素插入空位
        pa[j + 1] = temp;
    }
}

// 递归快速排序
void QuickSort(int *pa, int low, int high, int (*pf)(int, int))
{
    int splitpos; //分割元素位置

    if (low >= high) // 递归结束条件（简单情景）
    {
        return;
    }

    // 分割数组，将分割元素调整到合适的位置
    // 并返回分割元素在数组中的位置
    splitpos = Split(pa, low, high, pf);
    // 对low和splitpos - 1之间的元素递归排序
    QuickSort(pa, low, splitpos - 1, pf);
    // 对splitpos + 1和high之间的元素递归排序
    QuickSort(pa, splitpos + 1, high, pf);
}
// 快速排序中的分割函数
int Split(int *pa, int low, int high, int (*pf)(int, int))
{
    // 把pa[low]复制到分割元素，留出空位
    int part_element = pa[low];

    // 无限循环(通过判断利用break跳出)
    for (;;)
    {
        // 从hight到low，查找小于（大于）分割元素的元素
        while (low < high && pf(part_element, pa[high]))
        {
            high--;
        }
        // 调整结束，退出循环
        if (low >= high)
        {
            break;
        }
        // 将小于（大于）分割元素的元素调整到low位
        // 然后将low + 1
        pa[low++] = pa[high];
        // 从low到hight，查找大于（小于）分割元素的元素
        while (low < high && pf(pa[low], part_element))
        {
            low++;
        }
        // 调整结束，退出循环
        if (low >= high)
        {
            break;
        }
        // 将大于（小于）分割元素的元素调整到high位
        // 然后将high - 1
        pa[high--] = pa[low];
    }

    // 将分割元素置于找到的位置(空位)
    // 此时左边的所有元素小于(大于)分割元素
    // 右边的所有元素大于(小于)分割元素
    pa[high] = part_element;

    // 返回分割元素的位置
    return high;
}

// 二分查找
int BiSearch(int *pa, int n, int key, int (*pf)(int, int))
{
    int low, high, mid;
    int pos = -1;
    low = 0;
    high = n - 1;

    while (low <= high)
    {
        // 中间位置
        mid = (low + high) / 2;
        // 如果key比中间元素小，则将high置为中间元素左边第1元素
        if (pf(key, pa[mid]))
        {
            high = mid - 1;
        }
        // 如果key比中间元素大，则将low置为中间元素右边第1元素
        else if (pf(pa[mid], key))
        {
            low = mid + 1;
        }
        // 如果x与中间元素相等，即找到了值相等的元素
        else
        {
            pos =  mid;
            break;
        }
    }
    // 返回位置，没有找到则返回 -1 */
    return pos;
}

// 递归二分查找
int ReBiSearch(int *pa, int low, int high, int key, int (*pf)(int, int))
{
    // 二分位置
    int mid = -1;

    if(low <= high)
    {
        // 计算二分位置
        mid = (low + high) / 2;
        if(pf(key, pa[mid])) // 小(大)于是间位置，在低半段查找
        {
            // 递归调用
            mid = ReBiSearch(pa, low, mid - 1, key, pf);
        }
        else if(pf(pa[mid], key))// 大(小)于是间位置，在高半段查找
        {
            // 递归调用
            mid = ReBiSearch(pa, mid + 1, high, key, pf);
        }
    }

    return mid;
}
