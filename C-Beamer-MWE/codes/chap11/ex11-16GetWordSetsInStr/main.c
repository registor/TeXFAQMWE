/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：将字符串分解为单词集合的演示代码。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2018年12月19日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 16

// 函数原型
char **GetWordSetsWithstrtok(char *, const char*); // 使用strtok函数分割字符串
char **GetWordSetsWithLoop(char *, const char*); // 使用循环分割字符串
char **GetWordSetsWithScansets(char *, const char*); // 使用%[]扫描集合分割字符串
void run(void); // 测试函数

// 函数类型重定义
typedef char **(*FooType)(char *, const char*);

// 函数描述结构体
typedef struct
{
    char *msg; //
    FooType pfoo;
} msgFooType;

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
// 日期: 2018年12月19日
//-----------------------------------------------------------------------------------------------
void run(void)
{
    // 用于测试的结构体数组
    msgFooType msgfoo[] =
    {
        {"With strtok", GetWordSetsWithstrtok},
        {"With loop", GetWordSetsWithLoop},
        {"With scansets", GetWordSetsWithScansets}
    };

    int i = 0, j = 0, k = 0;
    char **p = NULL;

    // 测试字符串
    // 注意后续操作中需要改写要被操作的字符串
    // 所以需要使用二维数组，不能用指针数组
    char s[][20] = {"To C, or not to C",
                    "To,C,or.not,to.C",
                    "To@C, or not.to@C",
                   };
    char str[][20] = {"To C, or not to C",
                      "To,C,or.not,to.C",
                      "To@C, or not.to@C",
                     };
    char *delim = ", .@"; // 分割符字符串

    for(i = 0; i < sizeof(msgfoo) / sizeof(msgfoo[0]); i++)
    {
        memcpy(str, s, sizeof(str));
        printf("%02d. %s: \n", i + 1, msgfoo[i].msg);

        for(j = 0; j < sizeof(str) / sizeof(str[0]); j++)
        {
            printf("origin: %s\n", str[j]);
            p = msgfoo[i].pfoo(str[j], delim);

            printf("words: ");
            k = 0;
            while(p[k] != NULL)
            {
                printf("%s ", p[k]);
                k++;
            }
            if(p != NULL)
            {
                free(p);
                p = NULL;
            }
            printf("\n");
        }
        printf("\n");
    }
}

//-----------------------------------------------------------------------------------------------
// 名称: char **GetWordSetsWithstrtok(char *str, const char* delim)
// 功能: 使用strtok函数分割字符串
// 算法: 使用strtok函数实现，将分割结果各个字符串的首地址
//          存放在一个动态创建的char类型的指针数组中。
// 参数:
//       [char *str] --- 要切分的字符串
//       [const char* delim] --- 由分割字符构成的字符串
// 返回: [char **]  --- 返回字符指针数组的地址，出错返回NULL
// 作者: 耿楠
// 日期: 2018年12月19日
// 注意: 该函数内部会创建动态字符指针数组，返回的是首地址，使用后需free进行释放。
//-----------------------------------------------------------------------------------------------
char **GetWordSetsWithstrtok(char *str, const char* delim)
{
    size_t len = 0; // 指针数组长度计数
    size_t size = BUFSIZE; // 数组容量

    char **p = NULL;
    char *ptok = NULL;

    // 申请初始空间
    p = (char **)malloc(size * sizeof(char *));
    if(p == NULL)
    {
        return NULL;
    }

    // 分割，第1次分割用str做实参
    ptok = strtok(str, delim);
    p[len++] = ptok; // 记录提取的字符串首地址

    while (ptok != NULL)
    {
        // 以后的分割用NULL做实参
        ptok = strtok(NULL, delim);
        p[len++] = ptok; // 记录提取的字符串首地址

        // 数组扩容
        if(len == size)
        {
            // 容量加倍
            size += BUFSIZE;
            p = (char **)realloc(p, size * sizeof(char *));
        }
    }

    // 数组结束标志
    p[len++] = NULL;
    // 调整数组容量
    p = (char **)realloc(p, len * sizeof(char *));

    return p;
}

//-----------------------------------------------------------------------------------------------
// 名称: int IsDelimiter(char ch, const char* delim)
// 功能: 判断一个字符是不是分割符
// 参数:
//       [char ch] --- 需要判断的字符
//       [const char* delim] --- 由分割字符构成的字符串
// 返回: [int]  --- 是返回1, 否则返回0
// 作者: 耿楠
// 日期: 2017年10月29日
// 注意: 这是一个辅助函数，可以不出现在函数原型声明列表中。
//-----------------------------------------------------------------------------------------------
int IsDelimiter(char ch, const char* delim)
{
    // 以'\0'终止循环
    while(*delim)
    {
        if(ch == *delim)
        {
            return 1; // 是分割符，返回1
        }
        delim++;
    }
    return 0; // 返回0
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
// 注意: 这是一个辅助函数，可以不出现在函数原型声明列表中。
//-----------------------------------------------------------------------------------------------
int IsNotDelimiter(char ch, const char * deli)
{
    return (!IsDelimiter(ch, deli));
}

//-----------------------------------------------------------------------------------------------
// 名称：char* Find(char* s, char* e, const char *delim, int (*pf)(char))
// 功能：在字符串的指定位置范围内查找是否存在指定的字符
// 参数：
//       [char* s] --- 起始位置指针
//       [char* e] --- 结束位置指针
//       [const char *delim] --- 指向分割字符构成的字符串的指针
//       [int (*pf)(char)] --- 判断是否是分割符的函数指针(返回0不是，返回非0是)
// 返回：const char*  --- 返回找到字符的位置指针
// 作者：耿楠
// 日期：2017年10月29日
// 注意: 这是一个辅助函数，可以不出现在函数原型声明列表中。
//-----------------------------------------------------------------------------------------------
char* Find(char* s, char* e, const char *delim, int (*pf)(char, const char *))
{
    // 在指定范围内找是不是有指定的字符
    while( s != e && !pf(*s, delim) )
    {
        ++s;
    }
    // 返回位置指针
    return s;
}

//-----------------------------------------------------------------------------------------------
// 名称: char **GetWordSetsWithLoop(char *str, const char* delim)
// 功能: 使用使用循环自定义分割字符串
// 算法: 使用判断函数，找到非分割符后记录地址，找到分割符后将其置为'\0'。
//         将分割结果各个字符串的首地址，存放在一个动态创建的char类型的指针数组中。
// 参数:
//       [char *str] --- 要切分的字符串
//       [const char* delim] --- 由分割字符构成的字符串
// 返回: [char **]  --- 返回字符指针数组的地址，出错返回NULL
// 作者: 耿楠
// 日期: 2018年12月19日
// 注意: 该函数内部会创建动态字符指针数组，返回的是首地址，使用后需free进行释放。
//-----------------------------------------------------------------------------------------------
char **GetWordSetsWithLoop(char *str, const char* delim)
{
    size_t len = 0; // 指针数组长度计数
    size_t size = BUFSIZE; // 数组容量

    char **p = NULL;
    char *s = str, *e = str + strlen(str);

    // 申请初始空间
    p = (char **)malloc(size * sizeof(char *));
    if(p == NULL)
    {
        return NULL;
    }

    // 分割
    while (s <= e)
    {
        // 发现第1个非分割字符(不可以想当然认为第1个字符就不是分割符)
        s = Find(s, e, delim, IsNotDelimiter);
        // 记录提取的字符串首地址
        p[len++] = s;
        // 找到分割符位置
        s = Find(s, e, delim, IsDelimiter);
        // 将分割字符置为'\0'
        *s = '\0';
        s++; // 偏移

        // 数组扩容
        if(len == size)
        {
            // 容量加倍
            size += BUFSIZE;
            p = (char **)realloc(p, size * sizeof(char *));
        }
    }

    // 数组结束标志
    p[len++] = NULL;
    // 调整数组容量
    p = (char **)realloc(p, len * sizeof(char *));

    return p;
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetDelimiterPos(const char*str, const char* delim)
// 功能: 获取分割符位置
// 算法: 使用%[]、%n格式符结合sscanf函数实现
// 参数:
//       [const char* str] --- 被处理的字符串
//       [const char* delim] --- 由分割字符构成的字符串
// 返回: [int]  --- 是字符串str中第1次出现分割符的位置
// 作者: 耿楠
// 日期: 2018年12月19日
// 注意: 这是一个辅助函数，可以不出现在函数原型声明列表中。
//-----------------------------------------------------------------------------------------------
int GetDelimiterPos(const char*str, const char* delim)
{
    int pos = 0;

    // 格式串长度="%*[^" + strlen(delim) + ']' + "%n" + '\0'
    size_t size = 4 + strlen(delim) + 1 + 2 + 1;

    // 构造格式串，构造类似"%*[^, @.]%n"的格式串，用于sscanf
    char *p = (char *)malloc(size * sizeof(char));
    if(p == NULL)
    {
        return EOF;
    }
    strcpy(p, "%*[^");
    strcat(p, delim);
    strcat(p, "]");
    strcat(p, "%n");

    // 跳过指定的字符，记录跳过的字符个数
    sscanf(str, p, &pos);

    // 释放空间
    free(p);

    return pos; // 返回找到的位置
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetNonDelimiterPos(const char*str, const char* delim)
// 功能: 获取分割符位置
// 算法: 使用%[]、%n格式符结合sscanf函数实现
// 参数:
//       [const char* str] --- 被处理的字符串
//       [const char* delim] --- 由分割字符构成的字符串
// 返回: [int]  --- 是字符串str中第1次出现分割符的位置
// 作者: 耿楠
// 日期: 2018年12月19日
// 注意: 这是一个辅助函数，可以不出现在函数原型声明列表中。
//-----------------------------------------------------------------------------------------------
int GetNonDelimiterPos(const char*str, const char* delim)
{
    int pos = 0;

    // 格式串长度="%*[" + strlen(delim) + ']' + "%n" + '\0'
    size_t size = 3 + strlen(delim) + 1 + 2 + 1;

    // 构造格式串，构造类似"%*[, @.]%n"的格式串，用于sscanf
    char *p = (char *)malloc(size * sizeof(char));
    if(p == NULL)
    {
        return EOF;
    }
    strcpy(p, "%*[");
    strcat(p, delim);
    strcat(p, "]");
    strcat(p, "%n");

    // 跳过指定的字符，记录跳过的字符个数
    sscanf(str, p, &pos);

    // 释放空间
    free(p);

    return pos; // 返回找到的位置
}

//-----------------------------------------------------------------------------------------------
// 名称: char **GetWordSetsWithScansets(char *str, const char* delim)
// 功能: 使用%[]扫描集合分割字符串
// 算法: 找到非分割符后记录地址，找到分割符后将其置为'\0'。
//         将分割结果各个字符串的首地址，存放在一个动态创建的char类型的指针数组中。
// 参数:
//       [char *str] --- 要切分的字符串
//       [const char* delim] --- 由分割字符构成的字符串
// 返回: [char **]  --- 返回字符指针数组的地址，出错返回NULL
// 作者: 耿楠
// 日期: 2018年12月19日
// 注意: 该函数内部会创建动态字符指针数组，返回的是首地址，使用后需free进行释放。
//-----------------------------------------------------------------------------------------------
char **GetWordSetsWithScansets(char *str, const char* delim)
{
    size_t len = 0; // 指针数组长度计数
    size_t size = BUFSIZE; // 数组容量

    char **p = NULL;
    unsigned int s = 0, e = strlen(str);
    unsigned int off = 0;

    // 申请初始空间
    p = (char **)malloc(size * sizeof(char *));
    if(p == NULL)
    {
        return NULL;
    }

    // 分割
    while (s <= e)
    {
        // 发现第1个非分割字符(不可以想当然认为第1个字符就不是分割符)
        off = GetNonDelimiterPos(str + s, delim);
        s += off; // 偏移
        // 记录提取的字符串首地址
        p[len++] = str + s;
        // 找到分割符位置
        off = GetDelimiterPos(str + s, delim);
        s += off;  // 偏移
        // 将分割字符置为'\0'
        str[s] = '\0';
        s++;  // 偏移

        // 数组扩容
        if(len == size)
        {
            // 容量加倍
            size += BUFSIZE;
            p = (char **)realloc(p, size * sizeof(char *));
        }
    }

    // 数组结束标志
    p[len++] = NULL;
    // 调整数组容量
    p = (char **)realloc(p, len * sizeof(char *));

    return p;
}
