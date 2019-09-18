/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示fseek、ftell函数的使用。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月12日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月13日
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
// 函数原型
long GetFileSize(FILE *stream);

//-----------------------------------------------------------------------------------------------
// 名称：int main(void)
// 功能：主函数，程序入口
// 参数：
//            无
// 返回：[int]  --- 成功返回0，其它返回非0
// 作者：耿楠
// 日期：2017年11月13日
//-----------------------------------------------------------------------------------------------
int main(void)
{
    FILE *stream;

    stream = fopen("test.txt", "w+");

    fprintf(stream, "This is a test"); // 输出数据

    printf("Filesize of test.txt is %ld bytes\n",
                                        GetFileSize(stream));

    fclose(stream);

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------------------------
// 名称：long GetFileSize(FILE *stream)
// 功能：获得文件的大小(以字节为单位)
// 参数：
//           [FILE *stream] --- 文件指针
// 返回：[long]  --- 文件的大小(字节单位)
// 作者：耿楠
// 日期：2017年11月13日
//-----------------------------------------------------------------------------------------------
long GetFileSize(FILE *stream)
{
    long curpos, length; // long int类型

    curpos = ftell(stream); // 获取文件当前位置

    fseek(stream, 0L, SEEK_END); // 移动到文件尾

    length = ftell(stream); // 获取当前位置(长度)

    fseek(stream, curpos, SEEK_SET); // 恢复文件位置

    return length;
}
