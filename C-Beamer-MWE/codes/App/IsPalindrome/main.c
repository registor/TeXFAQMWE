/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示采用递归判断一个字符串是不是回文。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月20日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月20日
------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 全局变量
bool IsPalindrome(char *, int); // 判断一个字符串是不是回文

int main()
{

    char *p = "level";

    if(IsPalindrome(p, strlen(p)))
    {
        printf("%s is Palindrome.\n", p);
    }
    else
    {
        printf("%s is not Palindrome.\n", p);
    }

    return 0;
}

//-----------------------------------------------------------------------------------------------
// 名称：bool IsPalindrome(char *str, int len);
// 功能：用递归实现探测一个字符串是否是回文
// 参数：
//       [char *str] --- 需要探测的字符串的指针
//       [int len] --- 字符串长度
// 返回：[bool] --- 是返回true，否返回false
// 作者：耿楠
// 日期：2017年11月20日
//-----------------------------------------------------------------------------------------------
bool IsPalindrome(char *str, int len)
{
    if(len <= 1)
    {
        return true; // 一个字符，是回文
    }
    else
    {
        // 判断首尾字符与递归的结果求与运算，然后返回
        return (str[0] == str[len - 1] && IsPalindrome(str + 1, len - 2));
    }

    return true;
}
