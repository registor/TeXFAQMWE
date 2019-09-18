...
int main()
{
    int *p = NULL;
    int n = 0;
    ...
    AllocArray(&p, n);    
    ....
}

void AllocArray(int **p, int n)
{
    /*分配n个sizeof(int)字节的
    连续存储空间*/
    (*p) = (int *)malloc(n * sizeof(int));
    if(NULL == (*p)) // 内存申请失败的处理
    {
        printf("Not enough memory!\n");
        exit(1);
    }
}
