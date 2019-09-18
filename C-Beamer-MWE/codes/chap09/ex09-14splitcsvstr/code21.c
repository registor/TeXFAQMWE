// 功能：解析一行结尾不包含'\n'，但字段中可能包含'\n'的的字符串。
char **ParseCSV(const char *line)
{
    char **buf, **bptr, *tmp, *tptr;
    const char *ptr;
    int fieldcnt, flagQuote, flagEnd;
    // 统计字段数
    fieldcnt = CountFields(line);
    if (fieldcnt == -1){
        return NULL; // 没有字段，返回NULL
    }
    // 申请存放结果的指针数组，增加1个存储结束NULL指针
    buf = malloc(sizeof(char*) * (fieldcnt + 1));
    if (!buf){
        return NULL; //内存申请出错，返回NULL
    }
    // 申请临时空间存放需要解析的字符串，增加1，用于'\0'
    tmp = malloc(strlen(line) + 1);
    if(!tmp){
        free(buf);  // 申请失败释放前面申请的空间
        return NULL;
    }
    // 开始解析
    // 为各个量赋初值
    bptr = buf;
    flagQuote = 0; // 前双引号标志置0
    *tmp = '\0'; // 临时字符串第0个字符置'\0'，形成空串
    tptr = tmp;
    flagEnd = 0; //字符串结束标志置0
    // 循环扫描待解析的字符串
    for (ptr = line ; ; ptr++){
        if(flagQuote){ // 已有前双引号
            if(!*ptr){ // 是空字符'\0'，结束
                break;
            }
            if(*ptr == '\"'){ // 是双引号
                if(ptr[1] == '\"'){ // 连续两个引号，是双引号转义
                    *tptr++ = '\"'; // 解析出双引号到当前字段
                    ptr++;  // 跳过，处理下一个字符
                    continue;
                }
                flagQuote = 0; // 是后双引号
            }
            else{
                *tptr++ = *ptr; // 解析出该字符到当前字段
            }
            continue; // 是后双引号，不做解析，分析下一个字符
        }
