// 动态创建字符串数组
char **CreateStringArray(int n)
{
    char strTemp[STR_LEN + 1];
    char **p;
    int i;

    /*分配n个sizeof(char *)字节的
    连续空间存储每个字符串的首地址*/
    p = (char **)malloc(n * sizeof(char *));
    if(NULL == p) // 内存申请失败的处理
    {
        printf("Not enough strpointer memory!\n");
        exit(1);
    }

    // 把输入重定向到文件"data.txt"
    freopen("data.txt", "r", stdin);

    /*再为每一行分配n个strlen(strTemp) + 1个字节
    的连续空间存储每一个字符串*/
    for (i = 0; i < n; i++)
    {        
        read_line(strTemp, STR_LEN); // 读入一个字符串到临时数组
        p[i] = (char *)malloc((STR_LEN + 1) * sizeof(char));
        if(NULL == p[i]) // 内存申请失败的处理
        {
            printf("Not enough str's memory!\n");
            exit(1);
        }
	memset(p[i], '\0', STR_LEN + 1);
        // 复制字符串
        strcpy(p[i], strTemp);
    }

    // 把输入重定向回键盘
    freopen("CON", "r", stdin);
    return p;
}

void DestroyString(char **p, int n)
{
    int i;
    /*释放每一行的空间*/
    for (i = 0; i < n; i++)
    {
        free(p[i]);
        p[i] = NULL; // 赋值为NULL，防止野指针
    }

    /*释放存储每一行首地址的内存空间*/
    free(p);
}
