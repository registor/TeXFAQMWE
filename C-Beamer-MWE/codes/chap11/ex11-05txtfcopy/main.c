/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示行读写函数的使用。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月12日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月12日
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 函数原型
bool txtfcopy(const char *, const char *);

//-----------------------------------------------------------------------------------------------
// 名称：int main(int argc, char *argv[])
// 功能：主函数，程序入口
// 参数：
//           [int argc] --- 命令行参数个数
//           [char *argv[]] --- 命令行参数指针数组
// 返回：[int]  --- 成功返回0，其它返回非0
// 作者：耿楠
// 日期：2017年11月12日
//-----------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    // 判断命令行参数是否正确
    if (argc != 3)
    {
        fprintf(stderr, "usage: fcopy <source-file> <dest-file>\n");
        exit(EXIT_FAILURE);
    }

    // 调用复制函数，复制文件
    if(!txtfcopy(argv[1], argv[2]))
    {
        fprintf(stderr, "somthing wrong!\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

//-----------------------------------------------------------------------------------------------
// 名称：bool txtfcopy(const char *srcname, const char *desname)
// 功能：按行复制文本文件
// 参数：
//           [const char *srcname] --- 源文件名
//           [const char *desname] --- 目标文件名
// 返回：[bool]  --- 成功返回true, 失败返回false
// 作者：耿楠
// 日期：2017年11月12日
//-----------------------------------------------------------------------------------------------
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
