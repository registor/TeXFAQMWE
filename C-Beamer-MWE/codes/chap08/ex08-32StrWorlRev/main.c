/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：颠倒句子中单词顺序的演示代码。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2018年11月16日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VALUE 100 // 最大字符长度

// 函数原型
void StrRev(char *, int, int); // 字符串中指定区域反转
void StrWordRev(char *, int); // 颠倒字符串中单词的顺序
int ReadSentence(char *, int, char *); // 读入字符串
void OutSentence(char *, int, char); // 输出字符串


int main()
{
    int len;
    char terminating_char;
    char words[MAX_VALUE] = {0};

    printf("Enter a sentence: ");
    len = ReadSentence(words, MAX_VALUE, &terminating_char);

    // 整句翻转
    StrRev(words, 0, len - 1); // 减去最后的标点符号
    printf("Reversal of whole sentence: \n");
    OutSentence(words, len, terminating_char);

    // 各个单词翻转
    StrWordRev(words, len);
    printf("Reversal of each word in sentence: \n");
    OutSentence(words, len, terminating_char);

    return 0;
}

// 读入字符串
//-----------------------------------------------------------------------------------------------
// 名称: int ReadSentence(char *s, int maxlen, char *pch)
// 功能: 读入1个句子，遇到句号、问号或感叹号终止(称为“终止字符”)。
// 参数:
//       [char *s] --- 保存读入字符的字符型数组的指针
//       [int maxlen] --- 能够读入的最大字符数
//       [char *pch] --- 用于保存终止字符的变量指针
// 返回: [int]  --- 读入的字符个数
// 作者: 耿楠
// 日期: 2018年11月16日
//-----------------------------------------------------------------------------------------------
int ReadSentence(char *s, int maxlen, char *pch)
{
    int i = 0, ch = 0;
    memset(s, 0, maxlen); // 内存清零
    *pch = '\0'; // 句末终止字符先置为空字符

    for (i = 0; (ch = getchar()) != '\n' && i < maxlen; i++)
    {
        if (ch == '.' || ch == '!' || ch == '?')
        {
            *pch = ch;
            break;
        }
        s[i] = ch;
    }

    // 没有输入句末终止字符，置为'.'
    if(*pch == '\0')
    {
        *pch = '.';
    }

    return i + 1;
}

//-----------------------------------------------------------------------------------------------
// 名称: void StrRev(char *s, int from, int to)
// 功能: 对一个字符串中指定区域的字符进行前后位置反转
// 参数:
//       [char *s] --- 字符型数组的指针
//       [int from] --- 反转的起始位置
//       [char *pch] --- 反转的结束位置
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年11月16日
//-----------------------------------------------------------------------------------------------
void StrRev(char *s, int from, int to)
{
    // 利用异或操作实现交换
    while(from < to)
    {
        s[from] ^= s[to];
        s[to] ^= s[from];
        s[from++] ^= s[to--]; // 交换的同时调整from和to的位置
        //from++;
        //to--;
    }
}

//-----------------------------------------------------------------------------------------------
// 名称: void StrWordRev(char *s, int len)
// 功能: 颠倒字符串中单词的顺序
// 参数:
//       [char *s] --- 字符型数组的指针
//       [int len] --- 字符串长度
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年11月16日
//-----------------------------------------------------------------------------------------------
void StrWordRev(char *s, int len)
{
    int i = 0, j = 0;

    while(i < len)
    {
        j = i; // 单词起始位置

        // 查找单词终止位置(以空格分割单词)
        while(j < len)
        {
            if(s[j] == ' ')
            {
                break;
            }
            j++;
        }
        StrRev(s, i, j - 1); // 翻转该单词字符顺序
        i = j + 1; // 跳过空格，处理下一个单词
    }
}

//-----------------------------------------------------------------------------------------------
// 名称: void OutSentence(char *s, int len, char ch)
// 功能: 输出字符串
// 参数:
//       [char *s] --- 字符型数组的指针
//       [int len] --- 字符串长度
//       [char ch] --- 终止字符
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年11月16日
//-----------------------------------------------------------------------------------------------
void OutSentence(char *s, int len, char ch)
{
    int i;
    for(i = 0; i < len; i++)
    {
        putchar(s[i]); // 输出每个字符
    }

    printf("%c\n", ch); // 添加句末终止字符
}

/*
void revertWord(char *p, char *p1)
{
    char c;
    for (; p < p1; p++, p1--) {
        c = *p;
        *p = *p1;
        *p1 = c;
    }
}

void revert(char *p) 
{
    char *p1;
    while (*p && *p == ' ')
        p++;
    if (!*p)
        return;
    p1 = p;
    while (*p && *p != ' ')
        p++;
    revertWord(p1, p - 1);
    revert(p);
}

int main() 
{
    char line[] = "hello world.";
    revert(line);
    printf("%s\n", line);
    return 0;
}

*/
