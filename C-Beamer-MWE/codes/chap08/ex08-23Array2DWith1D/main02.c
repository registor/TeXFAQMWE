    // 按一维方式操作二维数组(注意偏移量的计算)
    for(i = 0; i < M; i++)
    {
        for(j = 0; j < N; j++)
        {
            // 得到第i行，第j列的偏移
            sum1 += *(p + i * N + j);
        }
    }

    // 按一维方式操作二维数组(注意偏移量的计算)
    for(i = 0; i < M; i++)
    {
        pTemp = p + i * N; // 指向第i行的首地址
        for(j = 0; j < N; j++)
        {
            sum2 += *(pTemp + j); // 第j列的偏移
        }
    }

    printf("%d\n", sum1);
    printf("%d\n", sum2);

    return 0;
}
