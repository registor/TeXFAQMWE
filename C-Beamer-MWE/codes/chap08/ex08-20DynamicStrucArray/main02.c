    /*使用内存*/
    for(i = 0; i < n; i++)
    {
        scanf("%d", &pstd->id);
        scanf(" "); /* 清理输入缓冲区 */
        gets(pstd->name);
        scanf(" ");
        gets(pstd->gender);
        scanf(" ");
        scanf("%d", &pstd->age);
    }

    printf("\nEntered details are:\n");
    for(i = 0; i < n; i++)
    {
        printf("%d, %s, %s, %d\n",
        pstd->id, pstd->name, pstd->gender, pstd->age);
    }

    // 释放内存
    free(pstd);

    return 0;
}
