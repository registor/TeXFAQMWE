// 函数定义
// const常量，只读参数
int count_spaces(const char *s)
{
    int count = 0;

    // 以空字符'\0'为结束条件
    while(*s != '\0')
    {
        if(*s == ' ')
        {
            count++;
        }
        s++;
    }
    return count;
}
