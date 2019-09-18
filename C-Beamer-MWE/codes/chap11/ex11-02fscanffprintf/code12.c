//-----------------------------------------
// 名称：void Input(const char *filename)
// 功能：从文件中用fscanf读入数据
// 参数：
//           [const char *filename] --- 文件名
// 返回：[void]  --- 无
// 作者：耿楠
// 日期：2017年11月12日
//-----------------------------------------
void Input(const char *filename)
{
    char str[80];
    int iVal;
    FILE * fp ; /* 文件指针 */
    // 打开文件
    if ((fp = fopen(filename, "r")) == NULL)
    {
        puts("can't open file");
        exit(EXIT_FAILURE) ; // 退出程序
    }
    /* 从文件读入数据 */
    fscanf(fp, "%s%d", str, &iVal); 
    /* 输出到stdout */
    fprintf(stdout, "%s %d", str, iVal); 

    fclose(fp); /* 关闭文件 */
}
