        switch(*ptr) // 处理特殊字符
        {
        case '\"':
            flagQuote = 1; // 是前双引号
            continue;
        case '\0':
            flagEnd = 1; // 字符串结束
        case ',':
            *tptr = '\0'; // 当前字段结束，置'\0'
            *bptr = strdup(tmp); // 复制解析出的当前字段
            if(!*bptr) // 解析出错
            {
                // 释放已解析出字段占有的空间
                for(bptr--; bptr >= buf; bptr--)
                {
                    free(*bptr);
                }
                free(buf);
                free(tmp);
                return NULL; // 返回NULL
            }
            bptr++; // 处理下一个字段(指针数组偏移1)
            tptr = tmp; // 复位当前字段指针

            if(flagEnd) // 处理结束
            {
                break;
            }
            else
            {
                continue; // 处理下一个字符
            }

        default:
            *tptr++ = *ptr; // 其它字符，解析到当前字段
            continue;
        }

        if(flagEnd) // 处理结束
        {
            break;
        }
    }

    *bptr = NULL; // 给最后一个指针赋值为NULL，表示指针数组的结束
    free(tmp);
    return buf;
}
