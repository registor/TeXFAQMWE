/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示csv数据文件的相关操作。
* CSV文件的基本规则：
*        1、开头是不留空，以行为单位。
*        2、可含或不含列名，含列名则居文件第一行。
*        3、一行数据不跨行，无空行。
*        4、以半角逗号(即,）作分隔符，列为空也要表达其存在。
*        5、列内容如存在半角引号(即"），替换成半角双引号(""）转义，并用半角引号(即""）将该字段值包含起来。
*        6、内码格式不限，可为 ASCII、Unicode 或者其他。
*        7、不支持特殊字符
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
#define READ_BLOCK_SIZE 65536

// 读取一个字符的宏
#define QUICK_GETC(ch, fp)\
do\
{\
    if(read_ptr == read_end)\
    {\
        fread_len = fread(read_buf, sizeof(char), READ_BLOCK_SIZE, fp);\
        if(fread_len < READ_BLOCK_SIZE)\
            read_buf[fread_len] = '\0';\
        read_ptr = read_buf;\
    }\
    ch = *read_ptr++;\
}\
while(0)

// 函数原型
// 功能函数
char **ParseCSV(const char *);
void FreeCSVLine(char **);
char **SplitOnUnescapedNewlines(const char *);
char *FreadCSVLine(FILE *, int, int *, int *);

// 测试函数
int test_FreadCSVLine(void);
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
    run_test("test_FreadCSVLine", test_FreadCSVLine);
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

// 测试从CSV文件中按行读取数据，并对读入的数据进行解析
int test_FreadCSVLine(void)
{
    int err, done = 0;
    FILE *fp = fopen("test.csv", "r");
    int cnt = 1;

    // 测试用字符串(应该读出的CSV字符串)
    char *ptest[] = {"foo,bar,baz",
                     "foo,\"bar\",baz",
                     "foo,\"b\"\"ar\",baz",
                     "foo,\"b\na\nr\",baz",
                     "foo,\"\n\nb\n\n\"\"a\"\"\n\nr\n\n\",baz",
                     "foo,bar,\"baz\"",
                     "foo,bar,\"\"baz\"\"",
                     "foo,bar,\"\"\"baz\"\"\"",
                     "foo,bar,baz",
                     "" // 在文件没有结束时，读到空行，表示错误
                    };

    char *ptr;

    // 读取成功，并且不是文件尾
    while((ptr = FreadCSVLine(fp, 1024, &done, &err)) && !done)
    {
        if(strcmp(ptr, ptest[cnt - 1]))
        {
            free(ptr); // 未能正确读取一行CSV字符串
            return 0;
        }
        printf("The Line %d was parsing...\n", cnt);
        char **parsed = ParseCSV(ptr); // 解析该行字符串
        char **pstr = parsed;

        for(; *pstr; pstr++) // 通过判断最后一个指针是否为NULL结束循环
        {
            puts(*pstr); // 输出解析出的每个字段
        }

        FreeCSVLine(parsed); // 释放解析结果占有的内存空间
        cnt++;
    }

    if(ptr != NULL)
    {
        free(ptr); // 释放存放从文件中读取的CSV字符串的内存空间
    }

    fclose(fp);
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

//-----------------------------------------------------------------------------------------------
// 名称：char *FreadCSVLine(FILE *fp, int max_line_size, int *done, int *err)
// 功能：从由文件指针指向的文件中解析一行CSV格式的字符串，
//           可以在一对双引号中包含'\n'转义字符。
//           注意：这个函数可以多次调用，直到文件结束，为此进行了优化。
//           另外，该函数会不定期地调整文件指针(类似fseek/ftell)，
//           所以，不能在两次调用该函数之间更改文件指针。
// 参数：
//           [FILE *fp] --- 文件指针
//           [int max_line_size] --- 最大行长度(以字节为单位)
//           [int *done] --- 存储处理结束标志变量的指针
//           [int *err] ---  存储处理错误标志变量的指针
// 返回：[char *]  --- 读取的字符串
// 注意：对一个处理结束的文件调用该函数会引发未定义行为
// 作者：耿楠
// 日期：2017年11月14日
//-----------------------------------------------------------------------------------------------
char *FreadCSVLine(FILE *fp, int max_line_size, int *done, int *err)
{
    // 用静态量，表示再次进入该函数，这些量保持的是以前的值
    static FILE *bookmark;
    static char read_buf[READ_BLOCK_SIZE], *read_ptr, *read_end;
    static int fread_len, prev_max_line_size = -1;
    static char *buf;

    char *bptr, *limit;
    char ch;
    int flagQuote;

    /* 如果新指定的长度比以前大，重新分配内存，否则用以前分配的内存 */
    if(max_line_size > prev_max_line_size)
    {
        if(prev_max_line_size != -1) // buf内有内容，应该释放
        {
            free(buf);
        }

        buf = malloc(max_line_size + 1); // 加1以存储'\0'

        if(!buf)
        {
            *err = CSV_ERR_NO_MEMORY; // 内存不足
            prev_max_line_size = -1;
            return NULL;
        }

        prev_max_line_size = max_line_size; // 更新
    }

    bptr = buf; // 缓冲区起始位置
    limit = buf + max_line_size; // 缓冲区结束

    if(bookmark != fp) // 不是同一个文件
    {
        read_ptr = read_buf + READ_BLOCK_SIZE; // 指向read_buf结尾
        read_end = read_buf + READ_BLOCK_SIZE; // 指向read_buf结尾
        bookmark = fp; // 更新
    }

    flagQuote = 0; // 前双引号标志置0

    for(; ;)
    {
        QUICK_GETC(ch, fp); // 读入1个字符(宏实现，快)

        if(!ch || (ch == '\n' && !flagQuote)) // 是空字符或不是双引号内的'\n'
        {
            break; // 结束循环
        }

        if(bptr >= limit) // 读入的数据超长
        {
            free(buf);
            *err = CSV_ERR_LONGLINE;
            return NULL;
        }

        *bptr++ = ch; // 读取一个字符到目标字符串

        if(flagQuote) // 有前双引号
        {
            if(ch == '\"') // 是一个双引号
            {
                QUICK_GETC(ch, fp); // 读取下一个字符

                if(ch != '\"') // 不是双引号
                {
                    if(!ch || ch == '\n') // 是空字符或'\n'，不是双引号内的'\n'，表示该行结束
                    {
                        break; // 结束
                    }

                    flagQuote = 0; // 处理完后双引号
                }

                *bptr++ = ch; // 读取该字符到目标字符串
            }
        }
        else if(ch == '\"') // 前双引号
        {
            flagQuote = 1;
        }
    }

    *done = !ch; // 处理结束
    *bptr = '\0';
    return buf;
}
