/*--------------------------------------------------------------------------------
* Copyright (c) 2019,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：读取点阵字库的演示代码。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2019年01月14日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

// 宏定义
#define HZROW 16
#define HZCOL 16

// 点阵字符数据结构
typedef struct
{
    unsigned char ch[3];              // 字符字符串(按中文3个字节统一表示)
    unsigned short row;               // 点阵行数
    unsigned short col;                // 点阵列数
    unsigned short bytes;            // 每行占有的字节数
    unsigned int tranflag;            // 字模是否需要转置
    unsigned long offset;             // 字库文件地址偏移量
    char filename[20];                   // 字库文件名称
    unsigned char *rawdata;         // 字模数据
    unsigned char fgch;                // 前景可显示字符
    unsigned char bgch;               // 背景可显示字符
    unsigned char *disdata;          // 显示字符字符串数组
} CHARTYPE;

// 函数原型
int GetMatCode(CHARTYPE *); // 从字模库文件中读取并生成一个字符数据
int SetCharInfo(CHARTYPE *, const unsigned char *, unsigned short, unsigned short,
                const char *, unsigned char, unsigned char); // 设置字符数据
int ProcString(CHARTYPE **, const unsigned char *, const char *, const char *,
               unsigned char, unsigned char); // 处理字符串
void PrintChars(const CHARTYPE *, int); // 显示结果

// 辅助函数
int ReadLine(char *, int); // 读入不超过指定长度的一个字符串

// 函数原型
void run(void); // 测试函数

// 测试
int main()
{
    // 置随机种子
    srand((unsigned)time( NULL ));
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
// 日期: 2019年01月14日
//-----------------------------------------------------------------------------------------------
void run(void)
{
    // 测试英文字符
    unsigned char str[80] = "小息Love C/C++！";
    int cnts = 0;

    CHARTYPE *ps;

    cnts = ProcString(&ps, str, "fonts/ASC12", "fonts/HZK16", '*', ' '); // 处理字符串
    PrintChars(ps, cnts); // 显示结果

    for(int i = 0; i < cnts; i++)
    {
        free(ps[i].rawdata);
        free(ps[i].disdata);
    }

    free(ps);
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
// 日期: 2019年01月14日
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
// 名称: int Transpose(unsigned char *pmat, unsigned short n)
// 功能: 二维数组的转置
// 参数:
//         [unsigned char *pmat] --- 数组指针
//         [unsigned short n] --- 数组宽度
// 返回: [int]  --- 成功返回1，否则返回0
// 作者: 耿楠
// 日期: 2019年01月14日
// 备注: 这是一个辅助函数
//-----------------------------------------------------------------------------------------------
int Transpose(unsigned char *pmat, unsigned short n)
{
    // 参数有效性检验
    if(pmat == NULL)
    {
        return 0;
    }
    unsigned char ch;
    int i = 0, j = 0;

    for(i = 0; i < n; i++)
    {
        for (j = i; j < n; j++)
        {
            ch = pmat[j + i * n];
            pmat[j + i * n] = pmat[i + j * n];
            pmat[i + j * n] = ch;
        }
    }

    return 1;
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetMatCode(CHARTYPE *pch)
// 功能: 从字模文件中读入1个字符的字模数据
// 算法: 从指定文件中读取字模结构体字符成员的字模数据，并对读入的数据分析后，
//         按字模显示字符查找表填充字模结构体中的可显示字符二维数组。
//         该算法采用"位与"和"移位"操作实现。
// 参数:
//         [ASCIICHAR *pch] --- 1个字符数据结构体指针
// 返回: [int]  --- 成功返回1，否则返回0
// 作者: 耿楠
// 日期: 2019年01月14日
//-----------------------------------------------------------------------------------------------
int GetMatCode(CHARTYPE *pch)
{
    // 参数有效性检验
    if(pch == NULL)
    {
        return 0;
    }

    FILE *fp;

    // 打开字模文件
    fp = fopen(pch->filename, "rb");
    if(fp == NULL)
    {
        printf("Can't open mat data file!\n");
        return 0;
    }

    // 为字模数据区申请内存
    size_t rawsize = pch->row * pch->bytes;
    size_t dissize = pch->row * pch->col;

    pch->rawdata = malloc(rawsize * sizeof(char));
    if(pch->rawdata == NULL)
    {
        printf("Not enough memory!\n");
        return 0;
    }
    pch->disdata = malloc(dissize * sizeof(char));
    if(pch->disdata == NULL)
    {
        printf("Not enough memory!\n");
        return 0;
    }

    // 文件定位
    fseek(fp, pch->offset, SEEK_SET);
    // 读入1个字符的字模数据
    fread(pch->rawdata, rawsize, 1, fp);

    // 将字模数据转换为可显示字符
    int i, j, k;
    for(i = 0; i < pch->row; i++)
    {
        for(j = 0; j < pch->bytes; j++)
        {
            unsigned char flag; // 判断结果
            unsigned char mask = 0x80; // 掩码(1000 0000)
            unsigned short cnt = 8; // 位数

            // 最后一个字节需要处理的位数
            if(((j + 1) * 8) > pch->col)
            {
                cnt = pch->col % 8;
            }

            // 将字模转换为可显示字符
            for(k = 0; k < cnt; k++)
            {
                // 注意j + i * (ASCCOL / 8)
                flag = pch->rawdata[j + i * pch->bytes] & mask; // 指定位保持原状，其它位置0
                if(flag) // 该位不为0
                {
                    pch->disdata[k + 8 * j + i * pch->col] = pch->fgch; // 前景字符
                }
                else
                {
                    pch->disdata[k + 8 * j + i * pch->col] = pch->bgch; // 背景字符
                }
                mask = mask >> 1; // 掩码右移1位
            }
        }
    }

    // 打印机点阵字体需要进行转置操作
    if(pch->tranflag)
    {
        Transpose(pch->disdata, pch->row);
    }

    // 关闭字模文件
    fclose(fp);

    return 1; // 正常，返回1
}

//-----------------------------------------------------------------------------------------------
// 名称: int SetCharInfo(CHARTYPE *pch, const unsigned char *str,
//                            unsigned short row, unsigned short col,
//                            const char *filename,
//                            unsigned char fg, unsigned char bg)
// 功能: 设置一个字符的基本信息
// 参数:
//         [CHARTYPE *pch] --- 1个字符数据结构体指针
//         [unsigned char *str] --- 字符，按中文2个字节的字符串统一处理
//         [unsigned short row] --- 字模行数
//         [unsigned short col] --- 字模列数
//         [const char *filename] --- 字模文件文件名称
//         [unsigned char fg] --- 字模可显示前景字符
//         [unsigned char bg] --- 字模可显示背景字符
// 返回: [int]  --- 成功返回1，否则返回0
// 作者: 耿楠
// 日期: 2019年01月14日
//-----------------------------------------------------------------------------------------------
int SetCharInfo(CHARTYPE *pch, const unsigned char *str,
                unsigned short row, unsigned short col,
                const char *filename,
                unsigned char fg, unsigned char bg)
{
    // 参数有效性检验
    if(pch == NULL || str == NULL || filename == NULL)
    {
        return 0;
    }

    memset(pch->ch, 0, 3);

    memcpy(pch->ch, str, 3);
    pch->row = row;
    pch->col = col;

    // 每行字节数
    if(pch->col % 8 == 0)
    {
        pch->bytes = pch->col / 8;
    }
    else
    {
        pch->bytes = pch->col / 8 + 1;
    }

    // 计算字模数据偏移地址
    if(pch->ch[1] == 0 && pch->ch[2] == 0)
    {
        // 提取出主文件名
        char *pstr = malloc((strlen(filename) + 1) * sizeof(char));
        if(pstr == NULL)
        {
            printf("Not enoght memory!\n");
            return 0;
        }
        strcpy(pstr, filename);

        char *ptok = strtok(pstr, "/");
        char *qtok = NULL;
        qtok = ptok;
        while(ptok != NULL)
        {
            qtok = ptok;
            ptok = strtok(NULL, "/");
        }

        // 英文字模文件
        if(strcmp(qtok, "ASC16") == 0)
        {
            // UCDOS字模文件
            pch->offset = (unsigned long)(pch->ch[0] * (pch->row * pch->bytes) + 1);
        }
        else
        {
            // 自制字模文件
            pch->offset = (unsigned long)((pch->ch[0] - 0x20) * (pch->row * pch->bytes));
        }

        free(pstr);
    }
    else
    {
        // 中文字模文件

        // 提取出主文件名
        char *pstr = malloc((strlen(filename) + 1) * sizeof(char));
        if(pstr == NULL)
        {
            printf("Not enoght memory!\n");
            return 0;
        }
        strcpy(pstr, filename);

        char *ptok = strtok(pstr, "/");
        char *qtok = NULL;
        qtok = ptok;
        while(ptok != NULL)
        {
            qtok = ptok;
            ptok = strtok(NULL, "/");
        }

        char *p[] = {"HZK24F", "HZK24H", "HZK24K", "HZK24S", "HZK40S", "HZK48S"};
        int flag = 0;
        for(int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
        {
            if(strcmp(qtok, p[i]) == 0)
            {
                flag = 1;
                break;
            }
        }

        /*区码=内码(高字节)-0xA0  位码=内码(低字节)-0xA0*/
        unsigned int rown = pch->ch[0] - 0xA0;
        unsigned int coln = pch->ch[1] - 0xA0;

        /*计算该汉字在字库中偏移量*/
        if(flag)
        {
            pch->offset = (unsigned long)((94 * (rown - 16) + (coln - 1)) * pch->row * pch->bytes);
            pch->tranflag = 1; // 需要转置
        }
        else
        {
            pch->offset = (unsigned long)((94 * (rown - 1) + (coln - 1)) * pch->row * pch->bytes);
            pch->tranflag = 0; // 无需转置
        }
        free(pstr);
    }

    strcpy(pch->filename, filename);
    pch->fgch = fg;
    pch->bgch = bg;

    return 1; // 成功返回1
}


//-----------------------------------------------------------------------------------------------
// 名称: int SkipNonDigit(const char *str)
// 功能: 跳过非0-9 的字符
// 算法: 利用"%*[^0-9]"格式串跳过非0-9 的字符，
//         利用"%n"获得跳过的字符数
// 参数:
//       [const char *str] --- 字符串指针
// 返回: [int]  --- 字符串中第1个数字字符的位置
// 作者: 耿楠
// 日期: 2018年12月19日
// 备注: 这是一个辅助函数用于读取字模文件名中的整数
//-----------------------------------------------------------------------------------------------
int SkipNonDigit(const char *str)
{
    int pos = 0;

    //跳过读入非0-9的字符，并将跳过的字符数记入n
    sscanf(str, "%*[^0-9]%n", &pos);

    if(str[pos - 1] == '-')
    {
        return pos - 1; // 前一个字符是'-'号
    }
    else
    {
        return pos;
    }
}

//-----------------------------------------------------------------------------------------------
//int ProcString(CHARTYPE **pc, const unsigned char *str,
//               const char *enname, const char *zhname,
//               unsigned char fgc, unsigned char bgc)
// 功能: 分析字符串，并创建字模结构体动态数组
// 参数:
//         [CHARTYPE **pc]  --- 字符结构指针的指针
//         [const char *str] --- 字符串指针
//         [const char *enname] --- 英文字模文件名指针
//         [const char *zhname] --- 英文字模文件名指针
//         [unsigned char fgc] --- 前景可显示字符
//         [unsigned char bgc] --- 背景可显示字符
// 返回: [int]  --- 字符总数
// 作者: 耿楠
// 日期: 2019年01月14日
//-----------------------------------------------------------------------------------------------
int ProcString(CHARTYPE **pc, const unsigned char *str,
               const char *enname, const char *zhname,
               unsigned char fgc, unsigned char bgc)
{
    // 参数有效性检验
    if(str == NULL || enname == NULL || zhname == NULL)
    {
        return 0;
    }

    int cnt = 0;

    const unsigned char *ptemp  = str;

    // 统计字符个数(包含中英文字符)
    while(*ptemp != '\0')
    {
        cnt++;
        if((*ptemp) < 128)
        {
            ptemp++;
        }
        else
        {
            ptemp += 2;
        }
    }

    // 申请空间
    CHARTYPE *pch = (CHARTYPE *)malloc(cnt * sizeof(CHARTYPE));
    if(pch == NULL)
    {
        printf("Not enough memory!\n");
        return 0;
    }

    // 初始化，主要是使各个指针为NULL
    memset(pch, 0, cnt * sizeof(CHARTYPE));

    unsigned char ch[3] = {0};
    int pos = 0;
    const char *p;
    int rows = 0;

    // 前景字符表
    char fgch[] = "@#*oO.$?0\xF9";
    int fglen = strlen(fgch);

    cnt = 0;
    // 逐个处理字符(包含中英文字符)
    while(*str != '\0')
    {
        // 前景字符(随机产生)
        int idx = rand() % fglen; // x=rand()%(Y-X+1)+X
        fgc = fgch[idx];
        if(*str < 128)
        {
            // 英文字符
            memset(ch, 0, 3);
            ch[0] = *str;

            // 提取字模文件名中的数字
            p = enname;
            // 跳过非0-9的字符
            pos = SkipNonDigit(p);
            // 数字起始位置
            p += pos;
            sscanf(p, "%d", &rows);
            if(rows == 10)
            {
                SetCharInfo(&pch[cnt], ch, 10, 8, enname, fgc, bgc);
            }
            else if(rows == 12)
            {
                SetCharInfo(&pch[cnt], ch, 12, 8, enname, fgc, bgc);
            }
            else if(rows == 16)
            {
                SetCharInfo(&pch[cnt], ch, 16, 8, enname, fgc, bgc);
            }
            else
            {
                SetCharInfo(&pch[cnt], ch, 48, 24, enname, fgc, bgc);
            }

            GetMatCode(&pch[cnt]);

            // 下一个字符
            str++;
        }
        else
        {
            // 中文字符
            memset(ch, 0, 3);
            ch[0] = *str;
            ch[1] = *(str + 1);

            // 提取字模文件名中的数字
            p = zhname;
            // 跳过非0-9的字符
            pos = SkipNonDigit(p);
            // 数字起始位置
            p += pos;
            sscanf(p, "%d", &rows);

            SetCharInfo(&pch[cnt], ch, rows, rows, zhname, fgc, bgc);

            GetMatCode(&pch[cnt]);

            // 下一个字符
            str += 2;
        }
        cnt++;
    }

    // 为形参赋值
    *pc = pch;

    // 返回字符总数
    return cnt;
}

//-----------------------------------------------------------------------------------------------
// 名称: void PrintChars(const CHARTYPE *pch, int n)
// 功能: 用可显示字符显示字模结构体数组中的字符
// 算法: 将字模结构体数组中的所有字符的每行可显示字符串拼装成一个完整字符串后输出。
// 参数:
//         [const CHARTYPE *pch] --- 字符数据结构体数组指针
//         [int n] --- 字符个数
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月14日
//-----------------------------------------------------------------------------------------------
void PrintChars(const CHARTYPE *pch, int n)
{
    // 参数有效性检验
    if(pch == NULL)
    {
        return;
    }

    // 计算所有字符的总宽度
    size_t rowsize = 0;
    size_t rowmax = 0;
    for(int i = 0; i < n; i++)
    {
        if(pch[i].rawdata != NULL)
        {
            rowsize += pch[i].col;
            if(pch[i].row > rowmax)
            {
                rowmax = pch[i].row;
            }
        }
    }

    // 分配空间
    char **pstr = NULL;
    // 分析字符串指针数组
    pstr = malloc(rowmax * sizeof(char *));
    if(pstr == NULL)
    {
        printf("Not enough memory!\n");
        return;
    }
    memset(pstr, 0, rowmax * sizeof(char *)); // 初始化，主要是让指针为NULL
    // 分配每行的字符串数组
    for(int i = 0; i < rowmax; i++)
    {
        pstr[i] = malloc((rowsize + 1) * sizeof(char));
        if(pstr[i] == NULL)
        {
            printf("Not enough memory!\n");
            return;
        }
        memset(pstr[i], 0, (rowsize + 1) * sizeof(char)); // 初始化，主要目的是置'\0'终止字符
    }

    char *s;

    // 将每个字符的显示字符串拼成一个字符串
    for(int i = 0; i < rowmax; i++)
    {
        s = pstr[i];
        for(int j = 0; j < n; j++)
        {
            if(pch[j].rawdata != NULL)
            {
                if(i < (rowmax - pch[j].row))
                {
                    memset(s, pch[j].bgch, pch[j].col);
                    s += pch[j].col;
                }
                else
                {
                    unsigned int pos = (i - (rowmax - pch[j].row)) * pch[j].col;
                    memcpy(s, pch[j].disdata + pos, pch[j].col);
                    s += pch[j].col;
                }
            }
        }
    }

    // 输出拼成的字符串
    for(int i = 0; i < rowmax; i++)
    {
        puts(pstr[i]);
    }

    // 释放内存
    for(int i = 0; i < rowmax; i++)
    {
        free(pstr[i]);
    }
    free(pstr);
}
