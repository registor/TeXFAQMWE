/*--------------------------------------------------------------------------------
* Copyright (c) 2019,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：比压牌的演示代码。
*
* 问题描述：牌只有1到9，手里拿着已经排好序的牌a，对方出牌b，
*          用程序判断手中牌是否能够压过对方出牌。
*          规则：出牌牌型有5种
*               [1]一张 如4 则5...9可压过
*               [2]两张 如44 则55，66，77，...，99可压过
*               [3]三张 如444 规则如[2]
*               [4]四张 如4444 规则如[2]
*               [5]五张 牌型只有12345 23456 34567 45678 56789五个，后面的比前面的均大。
* 输入：
*          输入有多组数据。
*          每组输入两个字符串(字符串大小不超过100)a，b。
*          a字符串代表手中牌，b字符串代表出的牌。
* 输出：
*          压过输出YES 否则NO。
* 输入样例：
*          12233445566677
*          33
* 输出样例：
*          YES
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
#include <string.h>

// 函数原型(非强制要求，可以不写函数，但函数能简化程序设计)
void Fix(char *); // 修复由fgets读入的字符串中多出一个'\n'的问题
int Judge(char *, char *); // 牌型判断

// 测试
int main()
{
    char a[101];
    char b[101];
    int flag;

    while(fgets(b, 100, stdin) != NULL)
    {
        Fix(b);
        if (strlen(b) == 0)
        {
            break;
        } 
        if (fgets(a, 100, stdin) == NULL)
        {
            break;
        }

        Fix(a);

        flag = Judge(b, a);
        printf("%s\n", flag ? "YES" : "NO");
    }

    return 0;
}

// 函数定义
//-----------------------------------------
// 名称: void Fix(char *s)
// 功能: 删除fgets函数读入的'\n'，修复字符串
// 参数:
//       [char *s] --- 待修复的字符串
// 返回: [void]  --- 无
// 作者: C语言课程组
// 日期: 2019年1月16日
//-----------------------------------------
void Fix(char *s)
{
    // 用'\0'结束循环
    while(*s)
    {
        if (*s == '\n')
        {
            *s = '\0';  // 修复
            break;
        }
        s++;
    }
    return ;
}

//-----------------------------------------
// 名称: int Judge(char *str1, char *str2)
// 功能: 牌大小判断
// 参数:
//       [char *str1] --- 自己的牌
//       [char *str2] --- 对手的牌
// 返回: [int]  --- 无
// 作者: C语言课程组
// 日期: 2019年1月16日
//-----------------------------------------
int Judge(char *str1, char *str2)
{
    // 声明变量
    int i, lenstr1, lenstr2, flag = 0;
    int count[11];
    int key;

    // 参数有效性检查
    if(str1 == NULL || str2 == NULL)
    {
        return 0;
    }

    // 字符串长度
    lenstr1 = strlen(str1);
    lenstr2 = strlen(str2);

    // 长度不符合要求
    if(lenstr1 == 0 || lenstr2 == 0)
    {
        return 0;
    }

    // 初始化
    memset(count, 0, sizeof(count));

    // 遍历自己的牌(统计每个点数的张数)
    for(i = 0; i < lenstr1; i ++)
    {
        // str1[i] - '0'转换为下标索引(只有数字)
        count[str1[i] - '0'] ++;
    }

    // 检测对方的牌
    switch(lenstr2)
    {
    case 1: // 一张
    case 2: // 两张
    case 3: // 三张
    case 4: // 四张
        for(key = str2[0] - '0' + 1; key <= 9; key++) // 1-9循环
        {
            if(count[key] >= lenstr2) // 有比对方大的牌型
            {
                flag = 1;
                break;
            }
        }
        break;
    case 5: // 五张
        for(key = str2[0] - '0' + 1; key < 9; key++) // 1-9循环
        {
            if(count[key] > 0 && count[key + 1] > 0
                    && count[key + 2] > 0 && count[key + 3] > 0
                    && count[key + 4] > 0) // 有比对方大的牌型
            {
                flag = 1;
                break;
            }
        }
        break;
    default:
        flag = 0;
    }

    return flag;
}
