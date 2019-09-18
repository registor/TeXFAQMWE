    /* 字符串排序. */
    qsort(planets, MAX, sizeof(planets[0]), comp);
    Output(planets, MAX);
    return(0);
}
// 函数定义
// 输出字符数组
void Output(char (*str)[8], int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        puts(str[i]);
    }
}
// 比较函数，根据两个字符串大小返回负、0、正数
int comp(const void *s1, const void *s2)
{
    // 需要先将void指针强制转换成char*指针
    return strcmp((char*)s1, (char*)s2);
}
