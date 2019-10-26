/*--------------------------------------------------------------------------------
* Copyright (c) 2019,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：BMP图像转ASCII码的演示代码。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2019年XX月XX日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "bmp.h"
#include "run.h"
#include "callbacks.h"

// 函数声明
void help();

// 测试
int main(int argc, char *argv[])
{
    // 区块处理函数指针数组
    GETBLOCKFOO pFoo[] =
    {
        GetAverage, // 对区块数据求平均值
        GetMedian, // 取区块数据的中值
        GetLoG// 对区块数据用LOG算子进行处理
    };

    // 命令行参数不符合要求
    if(argc < 4 || argc > 6)
    {
        help();
        return 0;
    }

    // 读取区块大小参数
    int w = 1, h = 1;
    sscanf(argv[2], "%d", &w);
    sscanf(argv[3], "%d", &h);

    // 函数指针数组索引
    int idx = 0;

    // 启动转换操作
    if(argc == 6)
    {
        sscanf(argv[4], "%d", &idx);
        run(argv[1], w, h, pFoo[idx], argv[5]); // 指定了转换函数和字符查找表文件
    }
    else if(argc == 5)
    {
        if(sscanf(argv[4], "%d", &idx) == 1)
        {
            run(argv[1], w, h, pFoo[idx], NULL); // 指定了转换函数，但未指定了字符查找表文件
        }
        else
        {
            run(argv[1], w, h, pFoo[idx], argv[4]); // 指定了转换字符查找表文件
        }
    }
    else
    {
        run(argv[1], w, h, pFoo[idx], NULL); // 未指定转换函数和字符查找表文件
    }

    // 不使用命令行参数的测试代码
//    run("imgs/bq02.bmp", 2, 4, GetAverage, NULL);
//    run("imgs/bq02.bmp", 2, 4, GetMedian, NULL);
//    run("imgs/bq02.bmp", 2, 4, GetLoG, NULL);

//    // 将内置转换字符查找表输出到文件()
//    FILE *fp = fopen("asclut1", "w");
//    size_t len = sizeof(ascii_char_table1);
//    for(int i = 0; i < len; i++)
//    {
//        putc(ascii_char_table1[i], fp);
//    }
//    putc('\n', fp);
//    fclose(fp);
//
//    fp = fopen("asclut2", "w");
//    len = sizeof(ascii_char_table2);
//    for(int i = 0; i < len; i++)
//    {
//        putc(ascii_char_table2[i], fp);
//    }
//    putc('\n', fp);
//    fclose(fp);

    return 0;
}

//--------------------------------------------------------------
// 名称：void help()
// 功能：显示程序的使用帮助
// 参数：
//          无
// 返回：无
// 作者：耿楠
// 日期：2013年12月13日
// 备注：这是一个辅助函数，仅在main.c中可见
//--------------------------------------------------------------
void help()
{
    printf(
        "这是一个简单的图像转ASCII码处理程序\n"
        "它读入一个图像文件并根据指定的转换为1个ASCII字符的图像区块大小进行转换\n"
        "若未指定图像文件名称和要处理的区块宽度，则终止程序。\n"
        "另外，也可以指定一个转换字符查找表文件，以自定义转换字符。\n"
        "同时，还可以指定区块像素处理函数编号(从0开始计数)。\n"
        "使用方式:\n"
        "\tImage2AsciiArt <imgfilename> <w> <h> [FooNum] [LUTfilename]\n\n"
        "参数说明:\n"
        "\t<imgfilename>\t图像文件名称\n"
        "\t<w>\t\t区块宽度\n"
        "\t<h>\t\t区块调试\n"
        "\t[FooNum]\t区块像素处理函数编号(可选参数，默认为0)\n"
        "\t\t\t0\t平均值法\n"
        "\t\t\t1\t中值法\n"
        "\t\t\t2\tLoG法\n"
        "\t[LUTfilename]\t转换字符查找表文件名称(可选参数)\n"
    );
}

