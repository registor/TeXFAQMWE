#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define N 10


//函数原型

//泛型冒泡排序
void generic_bubble_sort(void *ptr, size_t count, size_t size, int(*comp)(const void*,const void*));
//泛型插入排序
void generic_insert_sort(void *ptr, size_t count, size_t size, int(*comp)(const void*,const void*));
//泛型快速排序
void generic_quick_sort(void *ptr, size_t count, size_t size, int(*comp)(const void*,const void*));
//泛型选择排序
void generic_selection_sort(void *ptr, size_t count, size_t size, int(*comp)(const void*,const void*));
//数组遍历
void traversal(void *ptr, size_t count, size_t size, void(*pf)(void *));
//输入整型数
void input_int(void *);
//输出整型数
void output_int(void *);
//泛型交换
void generic_swap(void *p1, void *p2, size_t size);
//比较整型数大小（>）
int greater_int(const void*, const void*);
//比较整型数大小（<）
int lesser_int(const void*, const void*);
//产生一个随机整型数组
void rand_int_array(void*ptr, size_t count, size_t size);
//分割函数
int Split(int*, int, int, int (*)(const void*, const void*));

int main()
{

    int a[N];

    rand_int_array(a, N, sizeof(a[0]));//产生int型随机数组
    printf("Unsorted array: ");
    traversal(a, N, sizeof(a[0]), output_int);//遍历输出未排序的随机数组
    printf("\n");

    printf("Ascending order\n");

    generic_bubble_sort(a, N, sizeof(a[0]), greater_int);//冒泡升序
    printf(" Bubble_sort: ");
    traversal(a, N, sizeof(a[0]), output_int);//冒泡排序输出升序数组
    printf("\n");

    generic_insert_sort(a, N, sizeof(a[0]), greater_int);//插入升序
    printf(" Insert_sort: ");
    traversal(a, N, sizeof(a[0]), output_int);//插入排序输出升序数组
    printf("\n");

    generic_selection_sort(a, N, sizeof(a[0]), greater_int);//选择升序
    printf(" Selection_sort: ");
    traversal(a, N, sizeof(a[0]), output_int);//选择排序输出升序数组
    printf("\n");

    generic_quick_sort(a, N, sizeof(a[0]), greater_int);//快排升序
    printf(" Quick_sort: ");
    traversal(a, N, sizeof(a[0]), output_int);//快速排序输出升序数组
    printf("\n");


    printf("Descending order\n");

    generic_bubble_sort(a, N, sizeof(a[0]), lesser_int);//冒泡降序
    printf(" Bubble_sort: ");
    traversal(a, N, sizeof(a[0]), output_int);//冒泡排序输出降序数组
    printf("\n");

    generic_insert_sort(a, N, sizeof(a[0]), lesser_int);//插入降序
    printf(" Insert_sort: ");
    traversal(a, N, sizeof(a[0]), output_int);//插入排序输出降序数组
    printf("\n");

    generic_selection_sort(a, N, sizeof(a[0]), lesser_int);//选择降序
    printf(" Selection_sort: ");
    traversal(a, N, sizeof(a[0]), output_int);//选择排序输出降序数组
    printf("\n");

    generic_quick_sort(a, N, sizeof(a[0]), lesser_int);//快排降序
    printf(" Quick_sort: ");
    traversal(a, N, sizeof(a[0]), output_int);//快速排序输出降序数组
    printf("\n");

    return 0;
}
/**********************************************************************
    名称： void input_int(void *)
    功能：输入一个整型数
    参数：
            void * ---- 数据起始地址的指针
    注意：函数内要进行类型转换,以便输入整数
    返回：无
**********************************************************************/
void input_int(void *pData)
{
    scanf("%d", (int*)pData);
}
/**********************************************************************
    名称： void output_int(void *)
    功能：输出一个整型数
    参数：
            void * ---- 数据起始地址的指针
    注意：函数内要进行类型转换,以便输出整数
    返回：无
**********************************************************************/
void output_int(void *pData)
{
    printf("%d ", *(int*)pData);
}
/**********************************************************************
    名称： int greater_int(const void*a, const void*b)
    功能：比较两个整型数的大小
    参数：
            const void *a ---- 第一个元素的起始地址
            const void *b ---- 第二个元素的起始地址
    注意：函数内要进行类型转换,以便进行比较
    返回：*a大于*b，返回1，否则，返回0
**********************************************************************/
int greater_int(const void*a, const void*b)
{
    return *(int*)a - *(int*)b;
}
/**********************************************************************
    名称： int lesser_int(const void*a, const void*b)
    功能：比较两个整型数的大小
    参数：
            const void *a ---- 第一个元素的起始地址
            const void *b ---- 第二个元素的起始地址
    注意：函数内要进行类型转换,以便进行比较
    返回：*a小于*b，返回1，否则，返回0
**********************************************************************/
int lesser_int(const void*a, const void*b)
{
    return *(int*)b - *(int*)a;
}
/**********************************************************************
    名称： void generic_swap(void *p1, void *p2, size_t size)
    功能：泛型交换
    参数：
            void *p1 ---- 第一个数据的起始地址指针
            void *p2 ---- 第二个数据的起始地址指针
            size_t size ---- 要交换的数据所占有的内存大小
    注意：通过内存拷贝实现交换，故需要知道数据的类型
    返回：无
**********************************************************************/
void generic_swap(void *p1, void *p2, size_t size)
{
    void *pt = malloc(size);//申请一个size大小的内存

    memset(pt, 0, size);//初始化申请到的内存

    //通过内存复制，实现交换
    memcpy(pt, p1, size);
    memcpy(p1, p2, size);
    memcpy(p2, pt, size);

    free(pt);//释放内存
    pt = NULL;

}
/**********************************************************************
    名称： void traversal(void *ptr, size_t count, size_t size, void(*pf)(void *))
    功能：数组遍历
    参数：
            void *ptr ---- 数组的首地址的指针
            size_t count ---- 数组的长度
            size_t size ---- 一个数组元素的大小
            void(*pf)(void *) ---- 处理遍历得到数组元素的函数的函数指针
    注意：要存入数组的元素的字节大小是不确定的，要使用sizeof(ptr[0])
    返回：无
**********************************************************************/
void traversal(void *ptr, size_t count, size_t size, void(*pf)(void *))
{
    int i = 0;

    for(i = 0; i < count; i++)
    {
        pf(ptr + i * size);//传入函数处理遍历得到的元素
    }
}
/**********************************************************************
    名称： void rand_int_array(void*ptr, size_t count, size_t size)
    功能：随机产生一个整数数组
    参数：
            void *ptr ---- 数组的首地址的指针
            size_t count ---- 数组的长度
            size_t size ---- 一个数组元素的大小
    注意：使用rand，srand函数产生数组，要取[a,b)之间的随机整数，使用
    (rand() % (b - a)) + a
    返回：无
**********************************************************************/
void rand_int_array(void*ptr, size_t count, size_t size)
{
    srand(time(NULL));// 置随机种子

    int i = 0;

    for(i = 0; i < count; i++)
    {
        *(int*)(ptr + i * size) = rand() % 100;//产生0-100之间的随机整数，包括0不包括100
    }

}
/**********************************************************************
    名称： void generic_insert_sort(void *ptr, size_t count, size_t size, int(*comp)(const void*,const void*))
    功能：泛型插入排序
    参数：
            void *ptr ---- 数组的首地址的指针
            size_t count ---- 数组的长度
            size_t size ---- 一个数组元素的大小
            int(*comp)(const void*,const void*) ---- 对于取到的元素进行比较的函数的函数指针
    注意: 数组的元素的字节大小是不确定的，要使用sizeof(ptr[0])
    返回：无
**********************************************************************/
void generic_insert_sort(void *ptr, size_t count, size_t size, int(*comp)(const void*,const void*))
{
    int i = 1, j = 0;

    void*pt = malloc(size);//申请size个字节的内存，未初始化

    for(i = 1; i < count ; i++)
    {
        j = i - 1;
        memcpy(pt,ptr + i * sizeof(size),size);//将要排序的元素复制到申请到的内存中
        while(j >= 0&&comp(pt, ptr + j * sizeof(size)) < 0)//比较
        {

            memcpy(ptr + (j + 1) * sizeof(size), ptr + j * sizeof(size), size);//将元素一个一个比较后后移一位

            j--;
        }
        memcpy(ptr + (j + 1) * size, pt, size);//将元素插入合适的空位中

    }
    free(pt);//释放内存
    pt = NULL;//防止指针悬空
}
/**********************************************************************
    名称： void generic_bubble_sort(void *ptr, size_t count, size_t size, int(*comp)(const void*,const void*))
    功能：泛型冒泡排序
    参数：
            void *ptr ---- 数组的首地址的指针
            size_t count ---- 数组的长度
            size_t size ---- 一个数组元素的大小
            int(*comp)(const void*,const void*) ---- 对于取到的元素进行比较的函数的函数指针
    注意: 数组的元素的字节大小是不确定的，要使用sizeof(ptr[0])
    返回：无
**********************************************************************/
void generic_bubble_sort(void *ptr, size_t count, size_t size, int(*comp)(const void*,const void*))
{
    int bound = count - 1, new_bound = 0, i = 0, j = 0;

    for(i = 0; i < count - 1; i++ )
    {
        for(j = 0; j < bound; j++)
        {
            if(comp(ptr + j * size, ptr + (j + 1) * size) > 0) // 比较，前一个数比后一个数大，返回正值
            {
                generic_swap(ptr + j * size, ptr + (j + 1) * size, size); // 交换
                new_bound = j; // 更新最后一次发生交换的位置
            }
        }
        bound = new_bound; // 更新内层循环上界
    }
}

/**********************************************************************
    名称： void generic_selection_sort(void *ptr, size_t count, size_t size, int(*comp)(const void*,const void*))
    功能：泛型选择排序
    参数：
            void *ptr ---- 数组的首地址的指针
            size_t count ---- 数组的长度
            size_t size ---- 一个数组元素的大小
            int(*comp)(const void*,const void*) ---- 对于取到的元素进行比较的函数的函数指针
    注意: 数组的元素的字节大小是不确定的，要使用sizeof(ptr[0])
    返回：无
**********************************************************************/
void generic_selection_sort(void *ptr, size_t count, size_t size, int(*comp)(const void*,const void*))
{

    int i, j;
    int pos = 0; // 选择的位置
    for(i = 0; i < count - 1; i++)
    {
        pos = i; // 每次将 pos 置为无序数组的起始位置
        for(j = i + 1; j < count; j++) // 遍历无序数组，找到位置
        {
            if(comp(ptr + pos * sizeof(size), ptr + j * sizeof(size))> 0)
            {
                pos = j; // 更新位置
            }
        }
// 如果不是无序数组的起始位置，则交换
        if(pos != i)
        {

            generic_swap(ptr + i * sizeof(size),ptr + pos * sizeof(size), size);
        }
    }

}
/**********************************************************************
    名称： void generic_quick_sort(void *ptr, size_t count, size_t size, int(*comp)(const void*,const void*))
    功能：泛型快速排序
    参数：
            void *ptr ---- 传入数组的起始地址的指针
            size_t count ---- 数组的长度
            size_t size ---- 一个数组元素的大小
            int(*comp)(const void*,const void*) ---- 对于取到的元素进行比较的函数的函数指针
    注意: 数组的元素的字节大小是不确定的，要使用sizeof(ptr[0])：
          函数由递归实现
          调用分割函数

    返回：无
**********************************************************************/
void generic_quick_sort(void *ptr, size_t count, size_t size, int(*comp)(const void*,const void*))
{
    int low = 0, high = count - 1, Split_pos;

    if(low >= high)//简单情况判断
    {
        return;
    }

    Split_pos = Split(ptr, low, high, comp);//调用分割函数将数组分割变短，变成更简单情况

    generic_quick_sort(ptr, low, Split_pos - 1, comp);// 对low 和splitpos - 1 之间的元素递归排序

    generic_quick_sort(ptr, Split_pos + 1, high, comp);// 对splitpos + 1 和high 之间的元素递归排序


}
/**********************************************************************
    名称： int Split(int*ptr, int low, int high, int (*comp)(const void*, const void*));
    功能：用于快排中分割数组
    参数：
            void *ptr ---- 传入数组的起始地址的指针
            low ---- 传入数组的第一个元素
            high ---- 传入数组的最后一个元素
            int(*comp)(const void*,const void*) ---- 对于取到的元素进行比较的函数的函数指针
    注意: 可将传入数组的元素的大小先复制给一个int型的变量

    返回：分割元素位置
**********************************************************************/
int Split(int *ptr, int low, int high, int(*comp)(const void*,const void*))
{


    void*pt = malloc(sizeof(*ptr));

    memcpy(pt,ptr,sizeof(*ptr));// 把第一个元素复制到分割元素，留出空位


    for (;;)// 无限循环(通过判断利用break 跳出)
    {
// 从high 到low，查找小于（大于）分割元素的元素
        while (low < high && comp(pt, ptr + high * sizeof(*ptr)))
        {
            high--;
        }

        if (low >= high)// 调整结束，退出循环
        {
            break;
        }
// 将小于（大于）分割元素的元素调整到low 位
// 然后将low + 1
        memcpy(ptr + low * sizeof(*ptr),ptr + high * sizeof(*ptr),sizeof(*ptr));
        low++;
// 从low 到high，查找大于（小于）分割元素的元素
        while (low < high && comp(ptr + low * sizeof(*ptr), pt))
        {
            low++;
        }

        if (low >= high)// 调整结束，退出循环
        {
            break;
        }
// 将大于（小于）分割元素的元素调整到high 位
// 然后将high - 1
        memcpy(ptr + high * sizeof(*ptr),ptr + low * sizeof(*ptr),sizeof(*ptr));
        high--;
    }
// 将分割元素置于找到的位置(空位)， 此时左边的所有元素小于(大于) 分割元素，右边的所有元素大于(小于) 分割元素
    memcpy(ptr + high * sizeof(*ptr),pt,sizeof(*ptr));
    high--;
//释放内存，同时防止指针悬挂
    free(pt);
    pt = NULL;
    return high;// 返回分割元素的位置
}
