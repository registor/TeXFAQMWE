// 功能：从由文件指针指向的文件中解析一行CSV格式的字符串
char *FreadCSVLine(FILE *fp, int max_line_size, int *done, int *err)
{
    // 用静态量，表示再次进入该函数，这些量保持的是以前的值
    static FILE *bookmark;
    static char read_buf[READ_BLOCK_SIZE], *read_ptr, *read_end;
    static int fread_len, prev_max_line_size = -1;
    static char *buf;

    char *bptr, *limit;
    char ch;
    int flagQuote;

    /* 如果新指定的长度比以前大，重新分配内存，否则用以前分配的内存 */
    if(max_line_size > prev_max_line_size)
    {
        if(prev_max_line_size != -1) // buf内有内容，应该释放
        {
            free(buf);
        }
        buf = malloc(max_line_size + 1); // 加1以存储'\0'
        if(!buf)
        {
            *err = CSV_ERR_NO_MEMORY; // 内存不足
            prev_max_line_size = -1;
            return NULL;
        }
        prev_max_line_size = max_line_size; // 更新
    }

    bptr = buf; // 缓冲区起始位置
    limit = buf + max_line_size; // 缓冲区结束

    if(bookmark != fp) // 不是同一个文件
    {
        read_ptr = read_buf + READ_BLOCK_SIZE; // 指向read_buf结尾
        read_end = read_buf + READ_BLOCK_SIZE; // 指向read_buf结尾
        bookmark = fp; // 更新
    }
