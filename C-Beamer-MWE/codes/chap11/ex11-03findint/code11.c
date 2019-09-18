// 功能：搜索文件中以整数开始的行
int FindInt(const char *filename)
{
    FILE *fp = fopen(filename, "r"); // 声明文件指针
    int n;
    if (fp == NULL){
        return -1; // 无法打开文件
    }
    while(fscanf(fp, "%d", &n) != 1)
    {
        if(ferror(fp)){
            fclose(fp);
            return -2; // 发生读错误
        }
        if(feof(fp)){
            fclose(fp); // 未发现整数开始的行
            return -3;
        }
        fscanf(fp, "%*[^\n]"); // 跳过这一行剩余的除'\n'的内容
    }
    fclose(fp);
    return n;
}
