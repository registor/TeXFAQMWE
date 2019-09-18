/*--------------------------------------------------------------------------------
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
------------------------------------------------------------------------------------*/
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

    SplitOnWords(str, str + strlen(str), pdeli, HandleWord);

    return 0;
}

//-----------------------------------------------------------------------------------------------
// 名称：const char* Find(const char* s, const char* e, const char *pdeli, int (*pred)(char))
// 功能：在字符串的指定位置范围内查找是否存在指定的字符
// 参数：
//       [const char* s] --- 起始位置指针
//       [const char* e] --- 结束位置指针
//       [const char *pdeli] --- 指向分割字符构成的字符串的指针
//       [int (*pred)(char)] --- 判断函数指针(返回0不是，返回非0是)
// 返回：const char*  --- 返回找到字符的位置指针
// 作者：耿楠
// 日期：2017年10月29日
//-----------------------------------------------------------------------------------------------
const char* Find(const char* s, const char* e, const char *pdeli, int (*pred)(char, const char *))
{
    // 在指定范围内找是不是有指定的字符
    while( s != e && !pred(*s, pdeli) )
    {
        ++s;
    }
    // 返回位置指针
    return s;
}

//-----------------------------------------------------------------------------------------------
// 名称：void SplitOnWords(const char* s, const char* e, const char *pdeli, void (*pf)(const char*, const char*))
// 功能：在字符串的指定位置范围内按指定的字符分割字符串
// 参数：
//       [const char* s] --- 起始位置指针
//       [const char* e] --- 结束位置指针
//       [const char *pdeli] --- 指向分割字符构成的字符串的指针
//       [void (*pf)(const char*, const char*)] --- 分割到的字符串处理函数指针
// 返回：void  --- 无
// 作者：耿楠
// 日期：2017年10月29日
//-----------------------------------------------------------------------------------------------
void SplitOnWords(const char* s, const char* e, const char *pdeli, void (*pf)(const char*, const char*))
{
    const char* p = s;

    while( s != e )
    {
        s = Find(s, e, pdeli, IsNotDelimiter);//不可以想当然认为第1个字符不是分割符
        p = s;
        s = Find(s, e, pdeli, IsDelimiter);
        pf(p, s);
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void HandleWord(const char* s, const char* e)
// 功能：对字符串中指定位置范围内的字符的处理函数
// 参数：
//       [const char* s] --- 起始位置指针
//       [const char* e] --- 结束位置指针
// 返回：void  --- 无
// 作者：耿楠
// 日期：2017年10月29日
//-----------------------------------------------------------------------------------------------
void HandleWord(const char* s, const char* e)
{
    int len = e - s; //字符串长度
    // 分配内存
    char *pstr = (char*)malloc(sizeof(char) * (len + 1));

    memcpy(pstr, s, len); // 复制字符串
    pstr[len] = '\0'; // 添加空字符

    puts(pstr); // 输出字符串

    free(pstr); // 释放空间
    pstr = NULL;
}

//-----------------------------------------------------------------------------------------------
// 名称：int IsDelimiter(char ch, char * deli)
// 功能：判断一个字符是否为分割字符
// 参数：
//       [char ch] --- 需要判断的字符
//       [char * deli] --- 分割字符构成的字符串
// 返回：int  --- 是返回1，否返回0
// 作者：耿楠
// 日期：2017年10月29日
//-----------------------------------------------------------------------------------------------
int IsDelimiter(char ch, const char * deli)
{
    int result = 0;

    while(*deli)
    {
        if(ch == *deli)
        {
            result = 1;
            break;
        }
        deli++;
    }

    return result;
}

//-----------------------------------------------------------------------------------------------
// 名称：int IsNotDelimiter(char ch, char * deli)
// 功能：判断一个字符是否为分割字符
// 参数：
//       [char ch] --- 需要判断的字符
//       [char * deli] --- 分割字符构成的字符串
// 返回：int  --- 是返回0，否返回1
// 作者：耿楠
// 日期：2017年10月29日
//-----------------------------------------------------------------------------------------------
int IsNotDelimiter(char ch, const char * deli)
{
    return (!IsDelimiter(ch, deli));
}
