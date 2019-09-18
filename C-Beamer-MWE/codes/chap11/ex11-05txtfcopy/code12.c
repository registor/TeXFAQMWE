// 功能：按行复制文本文件
bool txtfcopy(const char *srcname, const char *desname)
{
    FILE *src_fp, *des_fp; // 文件指针
    char str[80]; //

    // 打开源文件(文本读方式)
    if ((src_fp = fopen(srcname, "r")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", srcname);
        return false; //打开文件失败
    }

    // 打开目标文件(文本写方式)
    if ((des_fp = fopen(desname, "w")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", desname);
        fclose(src_fp); // 关闭已打开的文件
        return false;  // 打开文件失败
    }

    // 按字节复制(读一行，写一行)
    while (fgets(str, 80, src_fp) != NULL)
    {
        fputs(str, des_fp);
    }

    // 关闭文件
    fclose(src_fp);
    fclose(des_fp);

    return true;
}
