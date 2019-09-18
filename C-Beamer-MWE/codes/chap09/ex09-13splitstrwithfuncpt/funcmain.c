/*-------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：利用自定义函数及函数指针实现字符串的分割操作。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年10月29日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年10月29日
--------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 查找字串
const char* Find(const char*,  const char*, const char *,
                 int (*)(char, const char*));
// 分割为单词
void SplitOnWords(const char*, const char*, const char *,
                  void (*)(const char*, const char*));
// 处理分割的单词
void HandleWord(const char*, const char* );

// 判断是不是分割字符
int IsDelimiter(char, const char *);
int IsNotDelimiter(char, const char *);

int main(void)
{
    char str[] = "- This, a sample string.";
    char *pdeli = " ,.-";

    SplitOnWords(str, str + strlen(str), pdeli, 
                 HandleWord);

    return 0;
}
