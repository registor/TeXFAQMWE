
// 交换两个数
void Swap(StuNodePt pa, StuNodePt pb)
{
    StuNode temp = {0}; // 主要为指针赋NULL
    CopyStu(&temp, pa); // 交换
    CopyStu(pa, pb);
    CopyStu(pb, &temp);
    DestroyNode(&temp); // 销毁指针对象
}
// 升序比较函数
int Greater(const void *pa, const void *pb)
{
    // 需要先转换为(StuNodePt)指针
    StuNodePt p1 = (StuNodePt)pa;
    StuNodePt p2 = (StuNodePt)pb;
    return p1->ID > p2->ID? 1 : 0;
}
// 降序比较函数
int Lesser(const void *pa, const void *pb)
{
    // 需要先转换为(StuNodePt)指针
    StuNodePt p1 = (StuNodePt)pa;
    StuNodePt p2 = (StuNodePt)pb;
    return p1->ID < p2->ID? 1 : 0;
}
// 采用冒泡排序对数组排序
int BubbleSort(StuNodePt pa, int n, int (*pf)(const void *, 
                                             const void *))
{
    int i = 0, j = 0; // 循环变量
    int counter = 0;  // 循环次数计数
    for(i = 0; i < n - 1; i++ ){
        // j<n-1确保数据不越界
        // -i为了减少循环次数
        for(j = 0; j < n - 1 - i; j++){
            if(pf(pa + j, pa + j + 1)){// 用传入的函数比较
                // 交换
                Swap(pa + j, pa + j + 1);
            }
            counter++; //循环计数
        }
    }
    return counter; // 返回循环次数
}
