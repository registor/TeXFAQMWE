...
// 函数原型
bool fcopy(const char *, const char *);

//----------------------------------------------
// 名称：int main(int argc, char *argv[])
// 功能：主函数，程序入口
// 参数：
//           [int argc] --- 命令行参数个数
//           [char *argv[]] --- 命令行参数指针数组
// 返回：[int]  --- 成功返回0，其它返回非0
// 作者：耿楠
// 日期：2017年11月12日
//----------------------------------------------
int main(int argc, char *argv[])
{
    // 判断命令行参数是否正确
    if (argc != 3)
    {
        fprintf(stderr, "usage:" 
            "fcopy <source-file>  <dest-file>\n");
        exit(EXIT_FAILURE);
    }

    // 调用复制函数，复制文件
    if(!fcopy(argv[1], argv[2]))
    {
        fprintf(stderr, "somthing wrong!\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
