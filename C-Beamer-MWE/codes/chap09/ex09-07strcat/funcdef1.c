char *strcat(char *s1, const char *s2)
{
    char *p = s1;

    while (*p != '\0') /* 确定s1末尾位置*/
        p++;

    while (*s2 != '\0')
    {
        *p = *s2; /* 逐字符复制 */
        p++;      /* 调整s1指针 */
        s2++;     /* 调整s2指针 */
    }
    *p = '\0';    /* 添加空字符 */

    return s1;    /* 返回s1首地址 */
}
