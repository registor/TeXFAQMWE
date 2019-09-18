// 功能：按字节复制文件(文本文件或二进制文件)
bool fcopy(const char *srcname, const char *desname)
{
    FILE *src_fp, *des_fp; // 文件指针
    int ch; // 注意必须是整型

    // 打开源文件(二进制读方式，r只能处理文本文件)
    if ((src_fp = fopen(srcname, "rb")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", srcname);
        return false; //打开文件失败
    }

    // 打开目标文件(二进制写方式，w只能处理文本文件)
    if ((des_fp = fopen(desname, "wb")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", desname);
        fclose(src_fp); // 关闭已打开的文件
        return false;  // 打开文件失败
    }

    // 按字节复制(读一个字节，写一个字节)
    while ((ch = getc(src_fp)) != EOF)
    {
        putc(ch, des_fp);
    }

    // 关闭文件
    fclose(src_fp);
    fclose(des_fp);

    return true;
}
