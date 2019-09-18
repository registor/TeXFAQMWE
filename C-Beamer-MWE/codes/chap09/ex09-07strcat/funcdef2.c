char *strcat(char *s1, const char *s2)
{
    char *p = s1;

    while (*p) /* 确定s1末尾位置*/
        p++;

    // 逐字符复制，同时调整s1和s2的指针
    // 以赋值后的结果*p为循环条件
    // 赋值后结束，无需再添加空字符
    while (*p++ = *s2++)
        ;

    return s1;    /* 返回s1首地址 */
}
