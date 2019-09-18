// 字符串遍历
void Traversal(char*s,void (*pf)(char*))
{
    // 以空字符'\0'为结束条件
    while(*s != '\0')
    {
        pf(s);
        s++;
    }
}
// 大写字母变小写
void lower(char *pch)
{
    if((*pch >= 'A' && *pch <= 'Z'))
    {
        *pch = *pch + ('a' - 'A');
    }
}
// 小写字母变大写
void upper(char *pch)
{
    if((*pch >= 'a' && *pch <= 'z'))
    {
        *pch = *pch - ('a' - 'A');
    }
}
