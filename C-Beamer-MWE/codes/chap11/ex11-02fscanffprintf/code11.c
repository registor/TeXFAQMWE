//-----------------------------------------
// 名称：void Output(const char *filename)
// 功能：用fprintf将数据写入文件
// 参数：
//           [const char *filename] --- 文件名
// 返回：[void]  --- 无
// 作者：耿楠
// 日期：2017年11月12日
//-----------------------------------------
void Output(const char *filename)
{
    char str[80];
    int iVal;
    FILE * fp ; /* 文件指针 */
    // 打开文件
    if ((fp = fopen(filename, "w ")) == NULL)
    {
        puts("can't open file");
        exit(EXIT_FAILURE) ; // 退出程序
    }
    /* 从stdin读入数据 */
    fscanf(stdin, "%s%d", str, &iVal);
    /* 将数据写入文件 */
    fprintf(fp, "%s %d", str, iVal);

    fclose(fp); /* 关闭文件 */
}
