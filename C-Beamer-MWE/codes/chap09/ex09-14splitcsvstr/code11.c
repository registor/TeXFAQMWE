// 功能：计算一行待解析字符串的字段数目
static int CountFields(const char *line)
{
    const char *ptr;
    int cnt, flagQuote;

    cnt = 1; // 字段计数器置1
    flagQuote = 0;  // 前双引号标志0
    for(ptr = line; *ptr; ptr++)
    {
        if(flagQuote) // 已有前双引号
        {
            if (*ptr == '\"') // 当前字符是双引号
            {
                if (ptr[1] == '\"') // 紧邻下一个字符也是双引号
                {
                    ptr++;
                    continue; // 是双引号转义，跳过后处理下一个字符
                }
                flagQuote = 0; // 找到配对后双引号
            }
            continue; // 处理下一个字符
        }

        switch(*ptr)
        {
        case '\"':
            flagQuote = 1; // 是前双引号
            continue; // 处理下一个字符
        case ',': // 在查找后双引号的过程中，会跳过双引号内的','号，因此不会出现误判。
            cnt++; // 字段数加1
            continue; // 处理下一个字符
        default:
            continue; // 其它字符，跳过，处理下一个字符
        }
    }

    // 前后引号不匹配，返回-1
    if (flagQuote)
    {
        return -1;
    }

    return cnt; // 返回字段数
}
