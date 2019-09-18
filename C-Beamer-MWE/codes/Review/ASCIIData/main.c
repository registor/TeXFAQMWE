/*--------------------------------------------------------------------------------
* Copyright (c) 2018,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：ASCII字模文件处理的示例代码。
*
*           请编程从字模文件ASC12x8.DAT中读取指定字符串中ASCII字符的点阵字模
*           并用“#”显示在屏幕上。
*
*           字模文件中存放了0x20到0x7E共95个ASCII字符的点阵字模数据，
*           每个ASCII字符对应10个字节，例如，A的字模数据为：
*           0x00,0x00,0x20,0x20,0x30,0x50,0x50,0x78,0x48,0xCC
*           ........  //0x00
*           ........  //0x00
*           ..#.....  //0x20
*           ..#.....  //0x20
*           ..##....  //0x30
*           .#.#....  //0x50
*           .#.#....  //0x50
*           .####...  //0x78
*           .#..#...  //0x48
*           #.#.#.#.  0xCC
*           字模文件为二进制文件。
* 输入
*           待输出字符串，仅包含英文ASCII字符，长度不超过20个字符。
* 输出
*           字符串对应的字模点阵信息
* 样例输入
*           ABC
* 样例输出
*              #       ####     ####
*              #        #  #     #     #
*             ##       #  #     #
*            # #       ###     #
*            # #       #  #     #
*            ####    #  #     #
*            #  #      #  #     #     #
*          ##  ##  ####     ###
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2019年01月11日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h> // isspace等函数

// 宏定义
#define BYTENUM 10
#define MAXNUM 20

// 8位位段读取一个字节的数据，并得到每一个位的信息
// 注意使用unsigned char，以确保只占1个字节(确保读入的字节数正确)
typedef struct
{
    unsigned char a0: 1;
    unsigned char a1: 1;
    unsigned char a2: 1;
    unsigned char a3: 1;
    unsigned char a4: 1;
    unsigned char a5: 1;
    unsigned char a6: 1;
    unsigned char a7: 1;
} BYTETYPE;

// 1个字符的数据结构(使用位段)
typedef struct
{
    char ch;                       // 字符
    BYTETYPE bitdata[BYTENUM]; // 字模数据
    char ascdata[BYTENUM][9];     // 10x8的字符显示字符字符串
} ASCIITYPE;

// 1个字符的数据结构(使用字符数组)
typedef struct
{
    char ch;                       // 字符
    unsigned char rawdata[BYTENUM]; // 字模数据
    char ascdata[BYTENUM][9];     // 10x8的字符显示字符字符串
} ASCIICHAR;

// 函数原型
// 位段算法实现
int GetBitFieldData(const char *, ASCIITYPE *, const char *); // 从指定的文件中读取一个字符的字符数据(按位段处理)
int GetDataBitField(ASCIITYPE *, const char *, const char *, const char *); // 处理数据
void PrintASCIIBitField(const ASCIITYPE *, int); // 显示结果

// 位与和移位算法实现
int GetRawData(const char *, ASCIICHAR *, const char *); // 从指定的文件中读取一个字符的字符数据(按字符数组处理)
int GetDataRaw(ASCIICHAR *, const char *, const char *, const char *); // 处理数据
void PrintASCIIRaw(const ASCIICHAR *, int); // 显示结果

// 辅助函数
int ReadLine(char *, int); // 读入不超过指定长度的一个字符串

void run(void); // 测试函数

// 测试
int main()
{
    run(); // 启动各项功能

    return 1;
}

// 函数定义

//-----------------------------------------------------------------------------------------------
// 名称: void run(void)
// 功能: 函数功能测试函数
// 算法: 可以利用带有NULL的函数指针数组和数组名称指针数组通过循环测试每个函数。
//       若有新函数，将相应名称加入数组即可。
// 参数:
//       [void] --- 无
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月13日
//-----------------------------------------------------------------------------------------------
void run(void)
{

    // 输入数据不超过MAXNUM个ACSII字符
    char str[MAXNUM + 1] = {0};

    int len = ReadLine(str, MAXNUM); // 读入1行字符串

    // 测试位段方法
    ASCIITYPE *pasc1 = malloc(len * sizeof(ASCIITYPE)); // 申请空间
    GetDataBitField(pasc1, str, "ASC10x8.DAT", " #"); // 读取并处理字模数据
    PrintASCIIBitField(pasc1, len); // 输出
    free(pasc1); // 释放内存

    // 测试位与、移位方法
    ASCIICHAR *pasc2 = malloc(len * sizeof(ASCIICHAR)); // 申请空间
    GetDataRaw(pasc2, str, "ASC10x8.DAT", " #"); // 读取并处理字模数据
    PrintASCIIRaw(pasc2, len); // 输出
    free(pasc2); // 释放内存
}

//-----------------------------------------------------------------------------------------------
// 名称: int read_line(char *str, int n)
// 功能: 读入指定长度的字符串
// 算法: 逐个读入字符，直到遇到回车符或EOF或是长度大于指定长度。
// 参数:
//       [char *str] --- 结果字符串
//       [int n] --- 允许读入的最大长度
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
// 名称: int GetBitFieldData(const char *filename, ASCIITYPE *pasc, const char *otab)
// 功能: 从文件中读入1个字符的字模数据
// 算法: 从指定文件中读取字模结构体字符成员的字模数据，并对读入的数据分析后，
//         按字模显示字符查找表填充字模结构体中的可显示字符二维数组。
//         该算法采用"位段"操作实现。
// 参数:
//       [const char *filename] --- 字模文件名称字符串
//       [ASCIITYPE *pasc] --- 字符数据结构体指针
//       [const char *otab] --- 字模显示字符查找表
// 返回: [int]  --- 成功返回1，否则返回0
// 作者: 耿楠
// 日期: 2019年01月11日
//-----------------------------------------------------------------------------------------------
int GetBitFieldData(const char *filename, ASCIITYPE *pasc, const char *otab)
{
    // 参数有效性检验
    if(filename == NULL || pasc == NULL || otab == NULL)
    {
        return 0; // 参数有效性检验
    }

    FILE *fp;

    // 打开字模文件
    fp = fopen(filename, "rb");
    if(fp == NULL)
    {
        printf("Can't open ASC10x8.DAT file!");
        return 0;
    }

    // 计算需要读取字符的字模数据偏移地址
    long pos = 0L;
    pos = (long)((pasc->ch - 32) * BYTENUM);
    // 文件定位
    fseek(fp, pos, SEEK_SET);

    // 读入数据(10个字节)
    fread(pasc->bitdata, 1, BYTENUM, fp);

    // 将字模数据转换为显示字符(查找表实现)
    for(int i = 0; i < BYTENUM; i++)
    {
        // 注意高低位顺序
        pasc->ascdata[i][0] = otab[pasc->bitdata[i].a7];
        pasc->ascdata[i][1] = otab[pasc->bitdata[i].a6];
        pasc->ascdata[i][2] = otab[pasc->bitdata[i].a5];
        pasc->ascdata[i][3] = otab[pasc->bitdata[i].a4];
        pasc->ascdata[i][4] = otab[pasc->bitdata[i].a3];
        pasc->ascdata[i][5] = otab[pasc->bitdata[i].a2];
        pasc->ascdata[i][6] = otab[pasc->bitdata[i].a1];
        pasc->ascdata[i][7] = otab[pasc->bitdata[i].a0];
        pasc->ascdata[i][8] = '\0'; // 字符串终止字符
    }

    // 关闭字模文件
    fclose(fp);

    return 1;
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetRawData(const char *filename, ASCIICHAR *pasc, const char *otab)
// 功能: 从文件中读入1个字符的字模数据
// 算法: 从指定文件中读取字模结构体字符成员的字模数据，并对读入的数据分析后，
//         按字模显示字符查找表填充字模结构体中的可显示字符二维数组。
//         该算法采用"位与"和"移位"操作实现。
// 参数:
//       [const char *filename] --- 字模文件名称字符串
//       [ASCIICHAR *pasc] --- 字符数据结构体指针
//       [const char *otab] --- 字模显示字符查找表
// 返回: [int]  --- 成功返回1，否则返回0
// 作者: 耿楠
// 日期: 2019年01月13日
//-----------------------------------------------------------------------------------------------
int GetRawData(const char *filename, ASCIICHAR *pasc, const char *otab)
{
    // 参数有效性检验
    if(filename == NULL || pasc == NULL || otab == NULL)
    {
        return 0; // 参数有效性检验
    }

    FILE *fp;

    // 打开字模文件
    fp = fopen(filename, "rb");
    if(fp == NULL)
    {
        printf("Can't open ASC10x8.DAT file!");
        return 0;
    }

    // 计算需要读取字符的字模数据偏移地址
    long pos = 0L;
    pos = (long)((pasc->ch - 32) * BYTENUM);
    // 文件定位
    fseek(fp, pos, SEEK_SET);
    // 读入数据(10个字节)
    fread(pasc->rawdata, 1, BYTENUM, fp);

    // 将字模数据转换为显示字符
    int i, j;
    for(i = 0; i < BYTENUM; i++)
    {
        unsigned char curr; // 当前状态
        unsigned char mask = 0x80; // 掩码(1000 0000)
        for(j = 0; j < 8; j++)
        {
            curr = pasc->rawdata[i] & mask; // 指定位保持原状，其它位置0
            if(curr) // 该位不为0
            {
                pasc->ascdata[i][j] = otab[1]; // 显示字符赋值(前景字符)
            }
            else
            {
                pasc->ascdata[i][j] = otab[0]; // 显示字符赋值(背景字符)
            }
            mask = mask >> 1; // 掩码右移1位
        }
        pasc->ascdata[i][j] = '\0'; // 字符串终止字符
    }

    // 关闭字模文件
    fclose(fp);

    return 1;
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetDataBitField(ASCIITYPE *pasc, const char *str, const char *filename, const char *otab)
// 功能: 处理录入的字字符串
// 算法: 对字符串按逐个字符进行提取后，再调用读取字模数据函数。
//          该算法采用"位段"操作实现
// 参数:
//       [ASCIITYPE *pasc] --- 字符数据结构体指针
//       [char *str] --- 要处理的字符串
//       [const char *filename] --- 字模文件文件名称
//       [const char *otab] --- 字模显示查找表
// 返回: [int]  --- 成功返回1，否则返回0
// 作者: 耿楠
// 日期: 2019年01月13日
//-----------------------------------------------------------------------------------------------
int GetDataBitField(ASCIITYPE *pasc, const char *str,  const char *filename, const char *otab)
{
    // 参数有效性检验
    if(str == NULL || pasc == NULL || filename == NULL)
    {
        return 0;
    }

    // 处理每一个字符
    while(*str != '\0')
    {
        pasc->ch = *str;
        GetBitFieldData(filename, pasc, otab);
        pasc++;
        str++;
    }

    return 1;
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetDataRaw(ASCIICHAR *pasc, const char *str, const char *filename, const char *otab)
// 功能: 处理录入的字字符串
// 算法: 对字符串按逐个字符进行提取后，再调用读取字模数据函数。
//          该算法采用"位与"和"移位"操作实现
// 参数:
//       [ASCIICHAR *pasc] --- 字符数据结构体指针
//       [onst char *str] --- 要处理的字符串
//       [const char *filename] --- 字模文件文件名称
//       [const char *otab] --- 字模显示查找表
// 返回: [int]  --- 成功返回1，否则返回0
// 作者: 耿楠
// 日期: 2019年01月13日
//-----------------------------------------------------------------------------------------------
int GetDataRaw(ASCIICHAR *pasc, const char *str,  const char *filename, const char *otab)
{
    // 参数有效性检验
    if(str == NULL || pasc == NULL || filename == NULL)
    {
        return 0;
    }

    // 处理每一个字符
    while(*str != '\0')
    {
        pasc->ch = *str;
        GetRawData(filename, pasc, otab);
        pasc++;
        str++;
    }

    return 1;
}

//-----------------------------------------------------------------------------------------------
// 名称: void PrintASCIIBitField(const ASCIITYPE *pasc, int n)
// 功能: 用可显示字符显示字模结构体数组中的字符
// 算法: 将字模结构体数组中的所有字符的每行可显示字符串拼装成一个完整字符串后输出。
// 参数:
//       [const ASCIITYPE *pasc] --- 字符数据结构体数组指针
//       [int n] --- 字符个数
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月13日
//-----------------------------------------------------------------------------------------------
void PrintASCIIBitField(const ASCIITYPE *pasc, int n)
{
    // 参数有效性检验
    if(pasc == NULL)
    {
        return;
    }

    char **pstr = NULL;

    // 分析字符串指针数组
    pstr = malloc(BYTENUM * sizeof(char *));
    if(pstr == NULL)
    {
        printf("Not enough memory!");
        return;
    }
    // 分配每行字条串数组
    for(int i = 0; i < BYTENUM; i++)
    {
        pstr[i] = malloc((n * 8 + 1) * sizeof(char));
        if(pstr[i] == NULL)
        {
            printf("Not enough memory!");
            return;
        }
        memset(pstr[i], 0, (n * 8 + 1) * sizeof(char)); // 初始化
    }

    // 将每个字符的显示字符串拼成一个字符串
    for(int i = 0; i < BYTENUM; i++)
    {
        for(int j = 0; j < n; j++)
        {
            strcat(pstr[i], pasc[j].ascdata[i]); // 拼装
        }
    }

    // 输出拼成的字符串
    for(int i = 0; i < BYTENUM; i++)
    {
        puts(pstr[i]);
    }

    // 释放内存
    for(int i = 0; i < BYTENUM; i++)
    {
        free(pstr[i]);
    }

    free(pstr);
}

//-----------------------------------------------------------------------------------------------
// 名称: void PrintASCIIRaw(const ASCIICHAR *pasc, int n)
// 功能: 用可显示字符显示字模结构体数组中的字符
// 算法: 将字模结构体数组中的所有字符的每行可显示字符串拼装成一个完整字符串后输出。
// 参数:
//       [const ASCIICHAR *pasc] --- 字符数据结构体数组指针
//       [int n] --- 字符个数
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月13日
//-----------------------------------------------------------------------------------------------
void PrintASCIIRaw(const ASCIICHAR *pasc, int n)
{
    // 参数有效性检验
    if(pasc == NULL)
    {
        return;
    }

    char **pstr = NULL;

    // 分析字符串指针数组
    pstr = malloc(BYTENUM * sizeof(char *));
    if(pstr == NULL)
    {
        printf("Not enough memory!");
        return;
    }
    // 分配每行字条串数组
    for(int i = 0; i < BYTENUM; i++)
    {
        pstr[i] = malloc((n * 8 + 1) * sizeof(char));
        if(pstr[i] == NULL)
        {
            printf("Not enough memory!");
            return;
        }
        memset(pstr[i], 0, (n * 8 + 1) * sizeof(char)); // 初始化
    }

    // 将每个字符的显示字符串拼成一个字符串
    for(int i = 0; i < BYTENUM; i++)
    {
        for(int j = 0; j < n; j++)
        {
            strcat(pstr[i], pasc[j].ascdata[i]); // 拼装
        }
    }

    // 输出拼成的字符串
    for(int i = 0; i < BYTENUM; i++)
    {
        puts(pstr[i]);
    }

    // 释放内存
    for(int i = 0; i < BYTENUM; i++)
    {
        free(pstr[i]);
    }

    free(pstr);
}
