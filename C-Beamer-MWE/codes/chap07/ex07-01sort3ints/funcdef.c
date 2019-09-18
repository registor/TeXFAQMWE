// 对3个整型数进行排序
void Sort(int *pa, int *pb, int *pc)
{
    // 交换a和b的值
    if(*pa < *pb){
        Swap(pa, pb);
    }
    // 交换a和c的值
    if(*pa < *pc){
        Swap(pa, pc);
    }
    // 交换b和c的值
    if(*pb < *pc){
        Swap(pb, pc);
    }
}
// 交换两个数
void Swap(int *pa, int *pb)
{
    int temp;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}
