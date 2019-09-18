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
    /* 以二级指针作为函数实参调用函数 */
    SetItem(p, m, n);
    Display(p, m, n);

    /*释放每一行的空间*/
    for (i = 0; i < m; i++)
    {
        free(p[i]);
        p[i] = NULL; // 赋值为NULL，防止野指针
    }

    /*释放存储每一行首地址的内存空间*/
    free(p);
    p = NULL; // 赋值为NULL，防止野指针

    return 0;
}
