/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：使用扫描集合提取字符串整数数字的演示代码。
*
*           在scanf、fscanf、sscanf中可以使用%[ ]扫描集合进行匹配，如:
*           %[0-9]表示只读入'0'到'9'之间的字符
*           %[a-zA-Z]表示只读入字母
*           %[^a-z]就表示读入小写字母之外的字符。
*           "%n[^=]" 读入"="号前的至多n 个字符
*           '-'是范围连接符，当然也可以直接列出需要读入的字符。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2018年12月18日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 10

// 函数原型
int SkipNonDigit(const char *); // 跳过非数字字符
int ReadIntInStr(int *, int, const char *); // 从字符串中读入整数
void run(void); // 测试函数

// 测试
int main()
{
    run();

    return 0;
}

// 函数定义

//-----------------------------------------------------------------------------------------------
// 名称: void run(void)
// 功能: 函数功能测试函数
// 算法: 利用带有NULL的函数指针数组和数组名称指针数组通过循环测试每个函数。
//          若有新函数，将相应名称加入数组即可。
// 参数:
//       [void] --- 无
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年12月18日
//-----------------------------------------------------------------------------------------------
void run(void)
{
    // 测试字符串
    char *str[] = {"1235ab86",
                   "abc1235ab86d78ffff39",
                   "hjk-1235ab86-efdsaf87",
                   NULL
                  };
    int cnt = 0;
    int d[MAXLEN] = {0};

    int i = 0;
    while(str[i] != NULL)
    {
        cnt = ReadIntInStr(d, MAXLEN, str[i]);
        printf("There are %d ints in %s: \n", cnt, str[i]);
        for(int j = 0; j < cnt; j++)
        {
            printf("%d ", d[j]);
        }
        printf("\n");
        i++;
    }
}

//-----------------------------------------------------------------------------------------------
// 名称: int SkipNonDigit(const char *str)
// 功能: 跳过非0-9 的字符
// 算法: 利用"%*[^0-9]"格式串跳过非0-9 的字符，
//         利用"%n"获得跳过的字符数
// 参数:
//       [const char *str] --- 字符串指针
// 返回: [int]  --- 字符串中第1个数字字符的位置
// 作者: 耿楠
// 日期: 2018年12月19日
//-----------------------------------------------------------------------------------------------
int SkipNonDigit(const char *str)
{
    int pos = 0;

    //跳过读入非0-9的字符，并将跳过的字符数记入n
    sscanf(str, "%*[^0-9]%n", &pos);

    if(str[pos - 1] == '-')
    {
        return pos - 1; // 前一个字符是'-'号
    }
    else
    {
        return pos;
    }
}

//-----------------------------------------------------------------------------------------------
// 名称: int ReadIntInStr(int *buf, int n, const char *str)
// 功能: 提取字符串中整数数字
// 参数:
//       [int *buf] --- 记录读入数据的数组指针
//       [int n] --- 整数数组容量(最多提取的整数个数)
//       [const char *str] --- 字符串指针
// 返回: [int]  --- 读入的整数个数
// 作者: 耿楠
// 日期: 2018年12月18日
//-----------------------------------------------------------------------------------------------
int ReadIntInStr(int *buf, int n, const char *str)
{
    int i = 0;
    int pos = 0;
    int len = 0;

    const char *p = str;

    // 跳过读入非0-9的字符
    pos = SkipNonDigit(p);
    // 数字位置
    p += pos;

    // 用"%n"获得读取的字符数量
    // "%n"不影响sscanf的返回值
    while(i < n && sscanf(p, "%d%n", &buf[i], &len) == 1)
    {
        p += len; // 跳过已读取的数字
        // 跳过读入非0-9的字符
        pos = SkipNonDigit(p);
        // 数字位置
        p += pos;
        i++;
    }

    return i; // 返回读入的整数个数
}