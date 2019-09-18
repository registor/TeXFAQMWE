    flagQuote = 0; // 前双引号标志置0
    for(; ;){
        QUICK_GETC(ch, fp); // 读入1个字符(宏实现，快)
        // 是空字符或不是双引号内的'\n'
        if(!ch || (ch == '\n' && !flagQuote)){
            break; // 结束循环
        }
        if(bptr >= limit) // 读入的数据超长
        {
            free(buf);
            *err = CSV_ERR_LONGLINE;
            return NULL;
        }
        *bptr++ = ch; // 读取一个字符到目标字符串
        if(flagQuote) // 有前双引号
        {
            if(ch == '\"') // 是一个双引号
            {
                QUICK_GETC(ch, fp); // 读取下一个字符
                if(ch != '\"') // 不是双引号
                {
                    // 是空字符或不是双引号内的'\n'，行结束
                    if(!ch || ch == '\n'){
                        break; // 结束
                    }
                    flagQuote = 0; // 处理完后双引号
                }
                *bptr++ = ch; // 读取该字符到目标字符串
            }
        }
        else if(ch == '\"') // 前双引号
        {
            flagQuote = 1;
        }
    }
    *done = !ch; // 处理结束
    *bptr = '\0';
    return buf;
}
