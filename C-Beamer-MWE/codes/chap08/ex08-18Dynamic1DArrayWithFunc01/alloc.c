...
int main()
{
    int *p = NULL;
    int n = 0;
    ...    
    p = AllocArray(n);    
    ....
}
// 为数组开辟空间
int * AllocArray(int n)
{
    int *p = NULL;

    /*分配n个sizeof(int)字节的
    连续存储空间*/
    p = (int *)malloc(n * sizeof(int));
    if(NULL == p) // 内存申请失败的处理
    {
        printf("Not enough memory!\n");
        exit(1);
    }

    // 返回分配的地址
    return p;
}
