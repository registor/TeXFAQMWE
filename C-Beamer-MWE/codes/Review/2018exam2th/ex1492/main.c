/*--------------------------------------------------------------------------------
* Copyright (c) 2019,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：删除子串的演示代码。
*
* 问题描述：在给定字符串中查找所有特定子串并删除，
*          如果没有找到相应子串，则不作任何操作。要求实现函数：
*          int delSubStr(char * src, char * sub,char * result);
* [形参说明]：
*           src：输入的被操作字符串(函数的“输入”)
*           sub：需要查找并删除的特定子字符串(函数的“输入”)
*           result：在src字符串中删除所有sub子字符串后的结果(函数的“输出”)
* [返回] :
*           删除的子字符串的个数
* 输入：无
* 输出：无
* 输入样例：无
* 输出样例：无
* 提示 :
*          注：I、子串匹配只考虑最左匹配情况，即只需要从左到右进行字串匹配的情况。
*                 比如：在字符串"abababab"中，采用最左匹配子串"aba",可以匹配2个"aba"字串。
*                 如果匹配出从左到右位置2开始的"aba"，则不是最左匹配，且只能匹配出1个"aba"字串。
*             II、不用考虑超长字符串的情况。
*                 示例 : 输入：src = "abcde123abcd123",sub = "123"  输出：result="abcdeabcd"
*                 返回：2
*
* 测试数据及对应输出结果见"data/"下的各个"*.in"文件及"*.out"
*
* 当前版本：1.0
* 作者：C语言课程组
* 完成日期：2019年1月16日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <ctype.h>

// 宏定义
#define BUFLEN 60

// 函数声明
// OJ系统设计的函数
int ReadLine(char *, int); // 读入不超过指定长度的一个字符串

// 题目要求，原型不可更改
int delSubStr(char * src, char * sub, char * result);

// 测试(OJ系统提供，无法更改)
int main()
{
    char s1[BUFLEN+1] = {0}, s2[BUFLEN+1] = {0}, res[BUFLEN+1] = {0};
    int r;

    // 测试时也可以使用gets等其它函数
    ReadLine(s1, BUFLEN);
    ReadLine(s2, BUFLEN);

    // 执行删除操作
    r = delSubStr(s1, s2, res);

    // 输出结果
    printf("%s\n%d\n", res, r);

    return 0;
}

// 函数定义
//------------------------------------------------------------------
// 名称: int ReadLine(char *str, int n)
// 功能: 读入指定长度的字符串
// 算法: 逐个读入字符，直到遇到回车符或EOF或是长度大于指定长度。
// 参数:
//       [char *str] --- 结果字符串
//       [int n] --- 允许读入的最大长度
// 返回: [int]  --- 返回读入字符的个数
// 作者: C语言课程组
// 日期: 2019年1月16日
//------------------------------------------------------------------
int ReadLine(char *str, int n)
{
    int ch, i = 0;

    // 跳过前导空格
    while(isspace(ch = getchar()))
    {
        ;
    }

    // 读入数据
    while(ch != '\n' && ch != EOF)
    {
        if(i < n)
        {
            str[i++] = ch;
        }
        ch = getchar(); // 读入下一个字符
    }

    str[i] = '\0'; // 字符串终止字符

    return i;
}

//------------------------------------------------------------------
// 名称: int delSubStr(char * src, char * sub, char * result)
// 功能: 统计一个字符在指定字符串中出现的次数
// 参数:
//       [char * src] --- 输入的被操作字符串
//       [char * sub] --- 需要查找并删除的特定子字符串
//       [char * result] --- 在src字符串中删除所有sub子字符串后的结果
// 返回: [int]  --- 删除的子字符串的个数
// 作者: C语言课程组
// 日期: 2019年1月16日
//------------------------------------------------------------------
int delSubStr(char * src, char * sub, char * result)
{
    // 变量声明
    char *src_p = src;
    char *sub_p = sub;
    char *res_p = result;

    int count = 0;
    int sub_len = strlen(sub); // 子串长度
    char *temp;

    // 申请临时内存空间
    temp = (char*)malloc((sub_len + 1) * sizeof(char));
    if(temp == NULL)
    {
        return 0;
    }
    // 初始化
    memset(temp, '\0', (sub_len + 1) * sizeof(char));

    // 用'\0'结束循环
    while (*src_p)
    {
        // 将原串的sub_len复制到临时串
        memcpy(temp, src_p, sub_len);

        // 比较
        if(strcmp(temp, sub_p) == 0)
        {
            count++; // 删除了1个子串
            src_p += sub_len; // 调整指针
        }
        else
        {
            // 原串复制到结果串
            *res_p++ = *src_p++;
        }
    }

    // 结果串终止字符
    *res_p = '\0';

    // 释放空间
    free(temp);

    // 返回子串个数
    return count;
}
