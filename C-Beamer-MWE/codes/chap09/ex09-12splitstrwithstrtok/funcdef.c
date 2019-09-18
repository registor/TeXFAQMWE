...
// 比较函数，根据两个字符串大小返回负、0、正数
int comp(const void *s1, const void *s2)
{
    // 需要先将void指针强制转换成char**指针，
    // 再取内容*(char**)s1指向字符串
    return (strcmp(*(char **)s1, *(char **)s2));
}
// 查找
char **Search(const char *key, char **s)
{
    const char **pkey;
    char **ptr;
    /* 让pkey指向key */
    pkey = &key;
    /* 在字符串查找 */
    ptr = bsearch(pkey, s, MAX, sizeof(s[0]), comp);

    return ptr;
}
...
