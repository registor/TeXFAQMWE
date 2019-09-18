...
int main(void)
{
    int **p = NULL; // 整型指针，初始化为NULL
    int m = 3, n = 4; //数组大小
    AllocArray(&p, m, n); // 分配空间
    ...
}
void AllocArray(int ***p, int m, int n)
{
    int i;//循环变量
    (*p) = (int **)malloc(m * sizeof(int *));
    if(NULL == (*p)) // 内存申请失败的处理
    {
        printf("Not enough row's memory!\n");
        exit(1);
    }
    for (i = 0; i < m; i++)
    {
        (*p)[i] = (int *)malloc(n * sizeof(int));
        if(NULL == (*p)[i]) // 内存申请失败的处理
        {
            printf("Not enough col's memory!\n");
            exit(1);
        }
    }
}
