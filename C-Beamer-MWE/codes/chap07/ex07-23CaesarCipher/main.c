/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：凯撒密码问题的演示代码。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2018年11月15日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 81

// 函数原型
char CaesarCipher(char, int, int); // 凯撒加密

int main()
{
    char msg[N]; // 字符数组

    int i, len, step, mode;

    fgets(msg, N, stdin); // 读入字符串(gets函数已废弃，应该用fgets代替)
    len = strlen(msg); // 字符串长度

    puts(msg); // 输出字符串

    step = 2; // 加密距离
    mode = 0; // 加解密方式0表示加密，1表示解密(需要有同样的距离)
    for(i = 0; i < len; i++)
    {
        msg[i] = CaesarCipher(msg[i], step, mode); // 加密
    }
    puts(msg); // 输出字符串

    mode = 1; // 解密
    for(i = 0; i < len; i++)
    {
        msg[i] = CaesarCipher(msg[i], step, mode); // 解密
    }
    puts(msg); // 输出字符串


    // 不保存输入的字符，输入一个，加密一个，但无法进行解密处理
//    do
//    {
//        ch = getchar();
//        ch = CaesarCipher(ch, 2, 0);
//        putchar(ch);
//    }
//    while(ch != '\n');

    return 0;
}

// 函数定义

//-----------------------------------------------------------------------------------------------
// 名称: char CaesarCipher(char ch, int n, int mode)
// 功能: 对一个字符按凯撒加解密算法进行加解密处理
// 算法: 如果字符是字母，则用字母表中固定距离之后的那个字母来代替。
//          如果越过了字母Z或z，则绕回到字母表的起始位置。例如：
//          如果设定距离为2，则A被替换为C，Y替换为A，Z替换为B。
// 参数:
//      [char ch] --- 被加解密的字符
//      [int n] --- 加解密距离
//      [int mode] --- 加解密模式，0表示加密，1表示解密(需要同样的距离)
// 返回: [char]  --- 返回加解密后的字符
// 作者: 耿楠
// 日期: 2018年11月15日
//-----------------------------------------------------------------------------------------------
char CaesarCipher(char ch, int n, int mode)
{
    switch(mode)
    {
    case 0:
        if (ch >= 'A' && ch <= 'Z')
        {
            ch = ((ch - 'A') + n) % 26 + 'A';
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            ch = ((ch - 'a') + n) % 26 + 'a';
        }
        else
        {
            ch = ch;
        }
        break;
    case 1:
        if (ch >= 'A' && ch <= 'Z')
        {
            ch = ((ch - 'A') + (26 - n)) % 26 + 'A';
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            ch = ((ch - 'a') + (26 - n)) % 26 + 'a';
        }
        else
        {
            ch = ch;
        }
        break;
    }

    return ch;
}
