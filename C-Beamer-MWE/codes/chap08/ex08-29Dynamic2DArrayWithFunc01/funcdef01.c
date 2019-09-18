

// 为二维数组开辟空间
int ** AllocArray(int m, int n)
{
    int i;//循环变量
    int **p = NULL;

    /*先分配m个sizeof(int *)字节的
    连续空间存储每行的首地址*/
    p = (int **)malloc(m * sizeof(int *));
    if(NULL == p) // 内存申请失败的处理
    {
        printf("Not enough row's memory!\n");
        exit(1);
    }

    /*再为每一行分配n个sizeof(int)字节
    的连续空间存储每一行的整型数*/
    for (i = 0; i < m; i++)
    {
        p[i] = (int *)malloc(n * sizeof(int));
        if(NULL == p[i]) // 内存申请失败的处理
        {
            printf("Not enough col's memory!\n");
            exit(1);
        }
    }

    // 返回分配的地址
    return p;
}
