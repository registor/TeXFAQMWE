/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示csv格式的分割操作。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月14日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月14日
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 宏定义
#define CSV_ERR_LONGLINE 0
#define CSV_ERR_NO_MEMORY 1


// 函数原型
char **ParseCSV(const char *);
void FreeCSVLine(char **);

int test_ParseCSV(void);
void run_test(const char *, int (*)(void));

//-----------------------------------------------------------------------------------------------
// 名称：int main(void)
// 功能：主函数，程序入口
// 参数：
//           [void] --- 无
// 返回：[int]  --- 成功返回0，其它返回非0
// 作者：耿楠
// 日期：2017年11月13日
//-----------------------------------------------------------------------------------------------
int main(void)
{
    run_test("test_ParseCSV", test_ParseCSV);
}

void run_test(const char *name, int (*pf)(void))
{
    int result;
    printf("Running %s...\n", name);
    result = pf();
    if (result)
    {
        printf("Success.\n");
    }
    else
    {
        printf("Failure!\n");
    }
}

int test_ParseCSV(void)
{
    /*
     * 测试字符串来自: https://en.wikipedia.org/wiki/Comma-separated_values
     */
    const char *test =
        "1996,Jeep,\"Venture \"\"Extended Edition\"\"\",\"MUST SELL!\nair, moon roof, loaded\",4799.00";

    char **parsed = ParseCSV(test);

    char **ptr;

    puts("CSV string is...");
    puts(test);
    puts("");

    for(ptr = parsed; *ptr; ptr++) // 通过判断最后一个指针是否为NULL结束循环
    {
        puts(*ptr); // 释放每个指针指向的字符串
    }

    if(!parsed[0] || !parsed[1] || !parsed[2] || !parsed[3] || !parsed[4])
    {
        return 0;
    }

    if(parsed[5])
    {
        return 0;
    }

    if(strcmp(parsed[0], "1996")
            ||   strcmp(parsed[1], "Jeep")
            ||   strcmp(parsed[2], "Venture \"Extended Edition\"")
            ||   strcmp(parsed[3], "MUST SELL!\nair, moon roof, loaded")
            ||   strcmp(parsed[4], "4799.00"))
    {
        return 0;
    }

    FreeCSVLine(parsed);

    return 1;
}

//-----------------------------------------------------------------------------------------------
// 名称：void FreeCSVLine(char **parsed)
// 功能：释放一行CSV数据解析结果字符串数组占有的内存
// 参数：
//           [char **parsed] --- 解析出的字符串的指针数组的指针
// 返回：[void]  --- 无
// 作者：耿楠
// 日期：2017年11月14日
//-----------------------------------------------------------------------------------------------
void FreeCSVLine(char **parsed)
{
    char **ptr = NULL; // 防止野指针

    for(ptr = parsed; *ptr; ptr++) // 通过判断最后一个指针是否为NULL结束循环
    {
        free(*ptr); // 释放每个指针指向的字符串
    }

    free(parsed); // 释放指针数组
}

//-----------------------------------------------------------------------------------------------
// 名称：static int CountFields(const char *line)
// 功能：计算一行待解析字符串的字段数目
// 参数：
//           [const char *line] --- 需要解析的字符串的指针
// 返回：[static int]  --- 成功返回字段数，错误返回-1(用static限定只在本文件中使用该函数)
// 作者：耿楠
// 日期：2017年11月14日
//-----------------------------------------------------------------------------------------------
static int CountFields(const char *line)
{
    const char *ptr;
    int cnt, flagQuote;

    cnt = 1; // 字段计数器置1
    flagQuote = 0;  // 前双引号标志0
    for(ptr = line; *ptr; ptr++)
    {
        if(flagQuote) // 已有前双引号
        {
            if (*ptr == '\"') // 当前字符是双引号
            {
                if (ptr[1] == '\"') // 紧邻下一个字符也是双引号
                {
                    ptr++;
                    continue; // 是双引号转义，跳过后处理下一个字符
                }
                flagQuote = 0; // 找到配对后双引号
            }
            continue; // 处理下一个字符
        }

        switch(*ptr)
        {
        case '\"':
            flagQuote = 1; // 是前双引号
            continue; // 处理下一个字符
        case ',': // 在查找后双引号的过程中，会跳过双引号内的','号，因此不会出现误判。
            cnt++; // 字段数加1
            continue; // 处理下一个字符
        default:
            continue; // 其它字符，跳过，处理下一个字符
        }
    }

    // 前后引号不匹配，返回-1
    if (flagQuote)
    {
        return -1;
    }

    return cnt; // 返回字段数
}

//-----------------------------------------------------------------------------------------------
// 名称：char **ParseCSV(const char *line)
// 功能：解析一行结尾不包含'\n'，但在用双引号括起来的字段中可能包含'\n'的的字符串。
//           该函数返回一个以NULL指针结束的字符串数组的指针，
//           每个指针指向一行中解析出的字符串。
// 参数：
//           [const char *line] --- 需要解析的字符串的指针
// 返回：[char **]  --- 成功返回字段字符串指针数组的指针，错误返回NULL
// 作者：耿楠
// 日期：2017年11月14日
//-----------------------------------------------------------------------------------------------
char **ParseCSV(const char *line)
{
    char **buf, **bptr, *tmp, *tptr;
    const char *ptr;
    int fieldcnt, flagQuote, flagEnd;

    // 统计字段数
    fieldcnt = CountFields(line);

    if (fieldcnt == -1)
    {
        return NULL; // 没有字段，返回NULL
    }

    // 申请存放结果的指针数组，增加1个用于存储表示指针数组结束的NULL指针
    buf = malloc(sizeof(char*) * (fieldcnt + 1));
    if (!buf)
    {
        return NULL; //内存申请出错，返回NULL
    }

    // 申请临时空间存放需要解析的字符串，增加1，用于'\0'
    tmp = malloc(strlen(line) + 1);
    if(!tmp)
    {
        free(buf);  // 申请失败释放前面申请的空间
        return NULL;
    }

    // 开始解析
    // 为各个量赋初值
    bptr = buf;
    flagQuote = 0; // 前双引号标志置0
    *tmp = '\0'; // 临时字符串第0个字符置'\0'，形成空串
    tptr = tmp;
    flagEnd = 0; //字符串结束标志置0

    // 循环扫描待解析的字符串
    for (ptr = line ; ; ptr++)
    {
        if(flagQuote) // 已有前双引号
        {
            if(!*ptr) // 是空字符'\0'，结束
            {
                break;
            }

            if(*ptr == '\"') // 是双引号
            {
                if(ptr[1] == '\"') // 连续两个引号，是双引号转义
                {
                    *tptr++ = '\"'; // 解析出双引号到当前字段
                    ptr++;  // 跳过，处理下一个字符
                    continue;
                }
                flagQuote = 0; // 是后双引号
            }
            else
            {
                *tptr++ = *ptr; // 解析出该字符到当前字段
            }
            continue; // 是后双引号，不做解析，分析下一个字符
        }

        switch(*ptr) // 处理特殊字符
        {
        case '\"':
            flagQuote = 1; // 是前双引号
            continue;
        case '\0':
            flagEnd = 1; // 字符串结束
        case ',':
            *tptr = '\0'; // 当前字段结束，置'\0'
            *bptr = strdup(tmp); // 复制解析出的当前字段(strdup是GCC有的函数)
            if(!*bptr) // 解析出错
            {
                // 释放已解析出字段占有的空间
                for(bptr--; bptr >= buf; bptr--)
                {
                    free(*bptr);
                }
                free(buf);
                free(tmp);
                return NULL; // 返回NULL
            }

            bptr++; // 处理下一个字段(指针数组偏移1)
            tptr = tmp; // 复位当前字段指针

            if(flagEnd) // 处理结束
            {
                break;
            }
            else
            {
                continue; // 处理下一个字符
            }

        default:
            *tptr++ = *ptr; // 其它字符，解析到当前字段
            continue;
        }

        if(flagEnd) // 处理结束
        {
            break;
        }
    }

    *bptr = NULL; // 给最后一个指针赋值为NULL，表示指针数组的结束
    free(tmp);
    return buf;
}
