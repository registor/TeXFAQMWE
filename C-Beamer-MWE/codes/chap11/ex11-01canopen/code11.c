#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// 函数原型
bool readable(const char *file);

int main(int argc, char *argv[])
{
    if (argc < 2) // 判断参数个数(程序名称也算1个参数)
    {
        printf("usage: %s  <filenames>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

     // 循环检测每个文件能否打开
    for (int i = 1; i < argc; i++)
    {
        if (readable(argv[i]))
        {
            printf("Y: %s\n", argv[i]);
        }
        else
        {
            printf("N: %s\n", argv[i]);
        }
    }

    return 0;
}
// 功能：测试文件能否打开
bool readable(const char *filename)
{
    FILE *fp; // 声明文件指针
    if ((fp = fopen(filename, "r")) == NULL)
    {
        return false; // 文件打开失败
    }

    fclose(fp); // 关闭文件
    return true;
}
