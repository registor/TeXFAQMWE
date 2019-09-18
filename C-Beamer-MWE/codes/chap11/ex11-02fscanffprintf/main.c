/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示fscanf和fprintf函数的使用。
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
void Output(const char *);
void Input(const char *);

//-----------------------------------------------------------------------------------------------
// 名称：int main(void)
// 功能：主函数，程序入口
// 参数：
//           [void] --- 无
// 返回：[int]  --- 成功返回0，其它返回非0
// 作者：耿楠
// 日期：2017年11月12日
//-----------------------------------------------------------------------------------------------
int main(void)
{
    char filename[] = "test.dat";

    Output(filename);
    Input(filename);

    return 0;
}

//-----------------------------------------------------------------------------------------------
// 名称：void Output(const char *filename)
// 功能：用fprintf将数据写入文件
// 参数：
//           [const char *filename] --- 文件名
// 返回：[void]  --- 无
// 作者：耿楠
// 日期：2017年11月12日
//-----------------------------------------------------------------------------------------------
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

    fscanf(stdin, "%s%d", str, &iVal ) ;  /* 从stdin读入数据 */
    fprintf(fp, "%s %d", str, iVal) ; /* 将数据写入文件 */

    fclose(fp ); /* 关闭文件 */
}

//-----------------------------------------------------------------------------------------------
// 名称：void Input(const char *filename)
// 功能：从文件中用fscanf读入数据
// 参数：
//           [const char *filename] --- 文件名
// 返回：[void]  --- 无
// 作者：耿楠
// 日期：2017年11月12日
//-----------------------------------------------------------------------------------------------
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

    fscanf(fp, "%s%d", str, &iVal ); /* 从文件读入数据 */
    fprintf(stdout, "%s %d", str, iVal); /* 输出到stdout */

    fclose(fp ); /* 关闭文件 */
}
