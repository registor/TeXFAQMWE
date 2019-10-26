/*--------------------------------------------------------------------------------
* Copyright (c) 2019,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：读取汉字点阵字库的演示代码。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2019年01月13日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// 宏定义
#define ASCROW 16
#define ASCCOL 8

#define HZROW 16
#define HZCOL 16

// 英文字符数据结构
typedef struct
{
    unsigned char ch;                                                               // 英文字符
    unsigned char rawdata[ASCROW * ASCCOL / 8]; // 字模数据
    char dispchar[ASCROW][ASCCOL + 1];               // 显示字符字符串数组
} ASCIICHAR;

// 中文字符数据结构
typedef struct
{
    unsigned char ch[3];                                        // 英文字符
    unsigned char rawdata[HZROW * HZCOL / 8]; // 字模数据
    char dispchar[HZROW][HZCOL + 1];               // 显示字符字符串数组
} HZCHAR;

// 函数原型
// 读取字模
int GetASCIICode(ASCIICHAR *, const char *, const char *); // 从ASC16英文字模库中读取一个英文字符的数据
int GetHZKCode(HZCHAR *, const char *, const char *); // 从HZK16汉字字模库中读取一个汉字字符的数据

// 字符串处理
int ASCProc(ASCIICHAR *, const char *, const char *, const char *); // 处理英文字符串
int HZProc(HZCHAR *, const char *, const char *, const char *); // 处理中文字符串

// 结果输出
void PrintASCII(const ASCIICHAR *, int); // 显示英文字符结果
void PrintHZK(const HZCHAR *, int); // 显示中文字符结果

// 辅助函数
int ReadLine(char *, int); // 读入不超过指定长度的一个字符串

// 函数原型
void run(void); // 测试函数

// 测试
int main()
{
    run(); // 启动各项功能

    return 0;
}

// 函数定义

//-----------------------------------------------------------------------------------------------
// 名称: void run(void)
// 功能: 函数功能测试函数
// 算法: 可以利用带有NULL的函数指针数组和数组名称指针数组通过循环测试每个函数。
//         若有新函数，将相应名称加入数组即可。
// 参数:
//         [void] --- 无
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月13日
//-----------------------------------------------------------------------------------------------
void run(void)
{
    // 测试英文字符
    char str[10] = "AbC!";
    int len = strlen(str);

    ASCIICHAR *pch1 = malloc(len * sizeof(ASCIICHAR)); // 申请空间
    ASCProc(pch1, str, "ASC16", " #"); // 读取并处理字模数据
    PrintASCII(pch1, len); // 输出
    free(pch1); // 释放内存

    // 测试中文字符
    char zh[10] = "耿楠学";
    len = strlen(zh);
    HZCHAR *pch2 = malloc(len * sizeof(HZCHAR)); // 申请空间
    HZProc(pch2, zh, "HZK16", " *"); // 读取并处理字模数据
    PrintHZK(pch2, len / 2); // 输出，注意汉字长度要除2
    free(pch2); // 释放内存
}

//-----------------------------------------------------------------------------------------------
// 名称: int ReadLine(char *str, int n)
// 功能: 读入指定长度的字符串
// 算法: 逐个读入字符，直到遇到回车符或EOF或是长度大于指定长度。
// 参数:
//         [char *str] --- 结果字符串
//         [int n] --- 允许读入的最大长度
// 返回: [int]  --- 返回读入字符的个数
// 作者: 耿楠
// 日期: 2019年01月13日
//-----------------------------------------------------------------------------------------------
int ReadLine(char *str, int n)
{
    int ch, i = 0;

    // 跳过前导空格
    while(isspace(ch = getchar()))
    {
        ;
    }

    // 读入数据
    while(ch != '\n' && ch != EOF)
    {
        if(i < n)
        {
            str[i++] = ch;
        }
        ch = getchar(); // 读入下一个字符
    }

    str[i] = '\0'; // 字符串终止字符

    return i;
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetASCIICode(ASCIICHAR *pch, const char *filename, const char *otab)
// 功能: 从字模文件中读入1个英文字符的字模数据
// 算法: 从指定文件中读取字模结构体字符成员的字模数据，并对读入的数据分析后，
//         按字模显示字符查找表填充字模结构体中的可显示字符二维数组。
//         该算法采用"位与"和"移位"操作实现。
// 参数:
//         [ASCIICHAR *pch] --- 字符数据结构体指针
//         [const char *filename] --- 字模文件名称字符串
//         [const char *otab] --- 字模显示字符查找表
// 返回: [int]  --- 成功返回1，否则返回0
// 作者: 耿楠
// 日期: 2019年01月13日
//-----------------------------------------------------------------------------------------------
int GetASCIICode(ASCIICHAR *pch, const char *filename, const char *otab)
{
    // 参数有效性检验
    if(pch == NULL || filename == NULL || otab == NULL)
    {
        return 0; // 参数有效性检验
    }

    FILE *fp;

    // 打开字模文件
    fp = fopen(filename, "rb");
    if(fp == NULL)
    {
        printf("Can't open data file!");
        return 0;
    }

    // 计算需要读取字符的字模数据偏移地址
    unsigned long pos = 0L;
    pos = (long)(pch->ch * (ASCROW * ASCCOL / 8) + 1);
    // 文件定位
    fseek(fp, pos, SEEK_SET);
    // 读入数据(ASCROW * ASCCOL / 8 个字节)
    fread(pch->rawdata, ASCROW * ASCCOL / 8, 1, fp);

    // 将字模数据转换为显示字符
    int i, j, k;
    for(i = 0; i < ASCROW; i++)
    {
        for(j = 0; j < ASCCOL / 8; j++)
        {
            unsigned char curr; // 当前状态
            unsigned char mask = 0x80; // 掩码(1000 0000)
            for(k = 0; k < 8; k++)
            {
                // 注意j + i * (ASCCOL / 8)
                curr = pch->rawdata[j + i * (ASCCOL / 8)] & mask; // 指定位保持原状，其它位置0
                if(curr) // 该位不为0
                {
                    pch->dispchar[i][k + 8 * j] = otab[1]; // 显示字符赋值(前景字符)
                }
                else
                {
                    pch->dispchar[i][k + 8 * j] = otab[0]; // 显示字符赋值(背景字符)
                }
                mask = mask >> 1; // 掩码右移1位
            }
        }
        pch->dispchar[i][k + 8 * (j - 1)] = '\0'; // 字符串终止字符(注意j-1)
    }

    // 关闭字模文件
    fclose(fp);

    return 1;
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetHZCode(HZCHAR *pch, const char *filename, const char *otab)
// 功能: 从字模文件中读入1个中文字符的字模数据
// 算法: 从指定文件中读取字模结构体字符成员的字模数据，并对读入的数据分析后，
//         按字模显示字符查找表填充字模结构体中的可显示字符二维数组。
//         该算法采用"位与"和"移位"操作实现。
// 参数:
//         [HZCHAR *pch] --- 字符数据结构体指针
//         [const char *filename] --- 字模文件名称字符串
//         [const char *otab] --- 字模显示字符查找表
// 返回: [int]  --- 成功返回1，否则返回0
// 作者: 耿楠
// 日期: 2019年01月13日
//-----------------------------------------------------------------------------------------------
int GetHZCode(HZCHAR *pch, const char *filename, const char *otab)
{
    // 参数有效性检验
    if(pch == NULL || filename == NULL || otab == NULL)
    {
        return 0; // 参数有效性检验
    }

    FILE *fp;

    // 打开字模文件
    fp = fopen(filename, "rb");
    if(fp == NULL)
    {
        printf("Can't open data file!");
        return 0;
    }

    // 计算需要读取字符的字模数据偏移地址
    unsigned long pos = 0L;

    // 计算汉字字模数据偏移地址
    /*区码=内码(高字节)-0xA0  位码=内码(低字节)-0xA0*/
    unsigned int rownum = pch->ch[0] - 0xA0;
    unsigned int colnum = pch->ch[1] - 0xA0;
    pos = (94 * (rownum - 1) + (colnum - 1)) * 32L; /*计算该汉字在字库中偏移量*/
    // 文件定位
    fseek(fp, pos, SEEK_SET);
    // 读入数据(ASCROW * ASCCOL / 8 个字节)
    fread(pch->rawdata, HZROW * HZCOL / 8, 1, fp); //

    // 将字模数据转换为显示字符
    int i, j, k;
    for(i = 0; i < HZROW; i++)
    {
        for(j = 0; j < HZCOL / 8; j++)
        {
            unsigned char curr; // 当前状态
            unsigned char mask = 0x80; // 掩码(1000 0000)
            for(k = 0; k < 8; k++)
            {
                // 注意j + i * (HZCOL / 8)
                curr = pch->rawdata[j + i * (HZCOL / 8)] & mask; // 指定位保持原状，其它位置0
                if(curr) // 该位不为0
                {
                    pch->dispchar[i][k + 8 * j] = otab[1]; // 显示字符赋值(前景字符)
                }
                else
                {
                    pch->dispchar[i][k + 8 * j] = otab[0]; // 显示字符赋值(背景字符)
                }
                mask = mask >> 1; // 掩码右移1位
            }
        }
        pch->dispchar[i][k + 8 * (j - 1)] = '\0'; // 字符串终止字符(注意j-1)
    }

    // 关闭字模文件
    fclose(fp);

    return 1;
}

//-----------------------------------------------------------------------------------------------
// 名称: int ASCProc(ASCIICHAR *pch, const char *str, const char *filename, const char *otab)
// 功能: 处理录入的字字符串
// 算法: 对字符串按逐个字符进行提取后，再调用读取字模数据函数。
//          该算法采用"位段"操作实现
// 参数:
//       [ASCIICHAR *pch] --- 字符数据结构体指针
//       [char *str] --- 要处理的字符串
//       [const char *filename] --- 字模文件文件名称
//       [const char *otab] --- 字模显示查找表
// 返回: [int]  --- 成功返回1，否则返回0
// 作者: 耿楠
// 日期: 2019年01月13日
//-----------------------------------------------------------------------------------------------
int ASCProc(ASCIICHAR *pch, const char *str,  const char *filename, const char *otab)
{
    // 参数有效性检验
    if(str == NULL || pch == NULL || filename == NULL)
    {
        return 0;
    }

    // 处理每一个字符
    while(*str != '\0')
    {
        pch->ch = *str;
        GetASCIICode(pch, filename, otab);
        pch++;
        str++;
    }

    return 1;
}

//-----------------------------------------------------------------------------------------------
// 名称: int HZProc(HZCHAR *pch, const char *str, const char *filename, const char *otab)
// 功能: 处理录入的字字符串
// 算法: 对字符串按逐个字符进行提取后，再调用读取字模数据函数。
//          该算法采用"位段"操作实现
// 参数:
//       [HZCHAR *pch] --- 字符数据结构体指针
//       [char *str] --- 要处理的字符串
//       [const char *filename] --- 字模文件文件名称
//       [const char *otab] --- 字模显示查找表
// 返回: [int]  --- 成功返回1，否则返回0
// 作者: 耿楠
// 日期: 2019年01月13日
//-----------------------------------------------------------------------------------------------
int HZProc(HZCHAR *pch, const char *str,  const char *filename, const char *otab)
{
    // 参数有效性检验
    if(str == NULL || pch == NULL || filename == NULL)
    {
        return 0;
    }

    // 处理每一个字符
    while(*str != '\0')
    {
        pch->ch[0] = str[0];
        pch->ch[1] = str[1];
        pch->ch[2] = '\0';
        GetHZCode(pch, filename, otab);
        pch++;
        str += 2;
    }

    return 1;
}


//-----------------------------------------------------------------------------------------------
// 名称: void PrintASCII(const ASCIICHAR *pch, int n)
// 功能: 用可显示字符显示字模结构体数组中的字符
// 算法: 将字模结构体数组中的所有字符的每行可显示字符串拼装成一个完整字符串后输出。
// 参数:
//         [const ASCIICHAR *pch] --- 字符数据结构体数组指针
//         [int n] --- 字符个数
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月13日
//-----------------------------------------------------------------------------------------------
void PrintASCII(const ASCIICHAR *pch, int n)
{
    // 参数有效性检验
    if(pch == NULL)
    {
        return;
    }

    char **pstr = NULL;

    // 分析字符串指针数组
    pstr = malloc(ASCROW * sizeof(char *));
    if(pstr == NULL)
    {
        printf("Not enough memory!");
        return;
    }
    // 分配每行字条串数组
    for(int i = 0; i < ASCROW; i++)
    {
        pstr[i] = malloc((n * ASCCOL + 1) * sizeof(char));
        if(pstr[i] == NULL)
        {
            printf("Not enough memory!");
            return;
        }
        memset(pstr[i], 0, (n * ASCCOL + 1) * sizeof(char)); // 初始化
    }

    // 将每个字符的显示字符串拼成一个字符串
    for(int i = 0; i < ASCROW; i++)
    {
        for(int j = 0; j < n; j++)
        {
            strcat(pstr[i], pch[j].dispchar[i]); // 拼装
        }
    }

    // 输出拼成的字符串
    for(int i = 0; i < ASCROW; i++)
    {
        puts(pstr[i]);
    }

    // 释放内存
    for(int i = 0; i < ASCROW; i++)
    {
        free(pstr[i]);
    }
    free(pstr);
}

//-----------------------------------------------------------------------------------------------
// 名称: void PrintHZK(const HZCHAR *pch, int n)
// 功能: 用可显示字符显示字模结构体数组中的字符
// 算法: 将字模结构体数组中的所有字符的每行可显示字符串拼装成一个完整字符串后输出。
// 参数:
//         [const HZCHAR *pch] --- 字符数据结构体数组指针
//         [int n] --- 字符个数
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月13日
//-----------------------------------------------------------------------------------------------
void PrintHZK(const HZCHAR *pch, int n)
{
    // 参数有效性检验
    if(pch == NULL)
    {
        return;
    }

    char **pstr = NULL;

    // 分析字符串指针数组
    pstr = malloc(HZROW * sizeof(char *));
    if(pstr == NULL)
    {
        printf("Not enough memory!");
        return;
    }
    // 分配每行字条串数组
    for(int i = 0; i < HZROW; i++)
    {
        pstr[i] = malloc((n * HZCOL + 1) * sizeof(char));
        if(pstr[i] == NULL)
        {
            printf("Not enough memory!");
            return;
        }
        memset(pstr[i], 0, (n * HZCOL + 1) * sizeof(char)); // 初始化
    }

    // 将每个字符的显示字符串拼成一个字符串
    for(int i = 0; i < HZROW; i++)
    {
        for(int j = 0; j < n; j++)
        {
            strcat(pstr[i], pch[j].dispchar[i]); // 拼装
        }
    }

    // 输出拼成的字符串
    for(int i = 0; i < HZROW; i++)
    {
        puts(pstr[i]);
    }

    // 释放内存
    for(int i = 0; i < HZROW; i++)
    {
        free(pstr[i]);
    }
    free(pstr);
}
