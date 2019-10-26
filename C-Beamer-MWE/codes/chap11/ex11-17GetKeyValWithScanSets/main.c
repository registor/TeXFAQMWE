/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：利用%[]扫描集合读取"key=value"的演示代码。
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
#include <ctype.h>

#define BUFSIZE 16

// 函数原型
int GetKeyValWithScansets(char *, char *, const char*); // 使用%[]扫描集合实现
int GetKeyValWithstrtok(char *, char *, const char*); // 使用strtok函数实现
void run(void); // 测试函数

// 函数类型重定义
typedef int(*FooType)(char *, char *, const char*);

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
        {"With scansets", GetKeyValWithScansets},
        {"With strtok", GetKeyValWithstrtok}
    };

    int i = 0, j = 0;

    char key[81] = {'\0'};
    char val[81] = {'\0'};

    // 测试字符串
    char *str[] =  {"name=Foo Bar", // 常规字符串
                    "12name=Foo Bar",    // 前导错误字符串
                    "name = Foo Bar\n",  // 带有空白的字符串
                    NULL
                   };

    for(i = 0; i < sizeof(msgfoo) / sizeof(msgfoo[0]); i++)
    {
        printf("%02d. %s: \n", i + 1, msgfoo[i].msg);
        j = 0;
        while(str[j] != NULL)
        {
            printf("origin: %s\n", str[j]);
            msgfoo[i].pfoo(key, val, str[j]);
            printf("Key: [%s], Val: [%s]\n", key, val);
            j++;
        }
        printf("\n");
    }
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetKeyValWithScansets(char *key, char *val, const char* str)
// 功能: 获取键=值对中的键和值
// 算法: 使用%[]扫描集合结合sscanf函数实现。
//          键需要以字母开始，跳过前面非字母字符
//          "%*[^a-zA-Z]"读到是'a-z'或'A-Z'中的一个字母时为止，结果丢弃
//          "%[^ =\n]"读到是' '或'='或'\n'时为止，结果赋给key
//          "%*[ =]"读入不是' '或'='时为止，结果丢弃
//          "%[^\n]"读到是'\n'时为止，结果赋给val
//          "%n"处理过的字符总数，结果赋给off，不影响sscanf的返回值
// 参数:
//       [char *key] --- 提取的键字符串
//       [char *val] --- 提取的值字符串
//       [const char* str] --- 待分析的字符串
// 返回: [int]  --- 成功返回1, 否则返回EOF
// 作者: 耿楠
// 日期: 2018年12月19日
//-----------------------------------------------------------------------------------------------
int GetKeyValWithScansets(char *key, char *val, const char* str)
{
    // 参数有效性检验
    if(key == NULL || val == NULL || str == NULL)
    {
        return EOF; // 返回出错信息
    }

    int off = 0; // 偏移量

    // 跳过非字母
    sscanf(str, "%*[^a-zA-Z]%n", &off);
    // 读入key和val
    sscanf(str + off, "%[^ =\n]%*[ =]%[^\n]", key, val);

    return 1; // 返回正确信息
}

//-----------------------------------------------------------------------------------------------
// 名称: char *LeftTrim(char *s)
// 功能: 删除字符串左侧空白
// 算法: isspace函数判断是不是空白字符，然后移动指针实现。
// 参数:
//       [char * s] --- 待处理的字符串
// 返回: [char *]  --- 成功处理后的字符串首地址
// 作者: 耿楠
// 日期: 2018年12月19日
// 备注: 这是一个被GetKeyValWithstrtok调用的辅助函数，可以不出现在函数声明列表中。
//-----------------------------------------------------------------------------------------------
char* LeftTrim(char* s)
{
    while(!isalpha(*s) || isspace(*s))
    {
        s++;
    }
    return s;
}

//-----------------------------------------------------------------------------------------------
// 名称: char *RightTrim(char *s)
// 功能: 删除字符串右侧空白
// 算法: isspace函数判断是不是空白字符，然后通过赋值为'\0'实现。
// 参数:
//       [char * s] --- 待处理的字符串
// 返回: [char *]  --- 成功处理后的字符串首地址
// 作者: 耿楠
// 日期: 2018年12月19日
// 备注: 这是一个被GetKeyValWithstrtok调用的辅助函数，可以不出现在函数声明列表中。
//-----------------------------------------------------------------------------------------------
char *RightTrim(char *s)
{
    // 避免处理字符串
    int len = strlen(s);
    if(len == 0)
    {
        return s;
    }

    // 处理
    // 指向终止字符前一个字符
    char* pos = s + len - 1;

    // 从右向左处理
    while(pos >= s && isspace(*pos))
    {
        *pos = '\0'; // 赋值为空字符
        pos--;
    }
    return s;
}

//-----------------------------------------------------------------------------------------------
// 名称: char *Trim(char *s)
// 功能: 删除字符串右侧空白
// 算法: 先执行左侧清除，再执行右侧清除。
// 参数:
//       [char * s] --- 待处理的字符串
// 返回: [char *]  --- 成功处理后的字符串首地址
// 作者: 耿楠
// 日期: 2018年12月19日
// 备注: 这是一个被GetKeyValWithstrtok调用的辅助函数，可以不出现在函数声明列表中。
//-----------------------------------------------------------------------------------------------
char *Trim(char *s)
{
    return RightTrim(LeftTrim(s));
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetKeyValWithstrtok(char *key, char *val, const char* str)
// 功能: 获取键=值对中的键和值
// 算法: 通过strtok函数分割实现，对分割后的字符串的前后空白单独进行删除。
// 参数:
//       [char *key] --- 提取的键字符串
//       [char *val] --- 提取的值字符串
//       [const char* str] --- 待分析的字符串
// 返回: [int]  --- 成功返回1, 否则返回EOF
// 作者: 耿楠
// 日期: 2018年12月19日
//-----------------------------------------------------------------------------------------------
int GetKeyValWithstrtok(char *key, char *val, const char* str)
{
    // 参数有效性检验
    if(key == NULL || val == NULL || str == NULL)
    {
        return EOF; // 返回出错信息
    }

    // 复制字符串(确保不更改原串)
    // 1. 确保原串不被更改
    // 2. strtok()函数会更改被处理的字符串
    char *s = (char *)malloc((strlen(str) + 1) * sizeof(char));
    if(s == NULL)
    {
        return EOF; // 返回出错信息
    }
    strcpy(s, str);

    // 提取key
    char *k = strtok(s, "=");
    if(k != NULL)
    {
        k = Trim(k); // 清理前后空白
        strcpy(key, k); // 复制字符串
    }
    else
    {
        free(s);
        return EOF; // 返回出错信息
    }
    // 提取val(注意，第2次调用strtok实参为NULL)
    char *v = strtok(NULL, "=");
    if(v != NULL)
    {
        v = Trim(v); // 清理前后空白
        strcpy(val, v); // 复制字符串
    }
    else
    {
        free(s);
        return EOF; // 返回出错信息
    }

    free(s);

    return 1; // 返回正确信息
}
