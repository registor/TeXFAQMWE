/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：输入任意长度字符串的演示代码。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2018年12月17日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 习惯于用2的整次幂，但为了调试方便，
// 测试时应该设置为2或3这样的小的数字
#define LEN 8

// 函数原型
int GetStrWithfgets(char **); // 使用fgets配合realloc函数实现任意长度字符串输入
int GetStrWithDofgets(char **); // 使用fgets配合realloc结合do...while实现任意长度字符串输入
int GetStrWithmalloc(char **); // 使用malloc函数实现任意长度字符串输入
int GetStrWithOnerealloc(char **); // 使用realloc单字符分配实现任意长度字符串输入
int GetStrWithrealloc(char **); // 使用realloc函数实现任意长度字符串输入
int GetStrWithFile(char **); // 使用文件的方式实现任意长度字符串输入
int GetStrWithtmpFile(char **); // 使用临时文件(内存文件)的方式实现任意长度字符串输入
void run(void); // 测试函数

// 函数类型重定义
typedef int(*GetStrFooType)(char **);

// 函数描述结构体
typedef struct
{
    char *msg; //
    GetStrFooType pfoo;
}msgFooType;


// 测试
int main()
{
    // 启动测试
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
// 日期: 2018年12月18日
//-----------------------------------------------------------------------------------------------
void run(void)
{

    // 用于测试的结构体数组
    msgFooType strfoo[] = {
        {"With fgets", GetStrWithfgets},
        {"With do...while fgets", GetStrWithDofgets},
        {"With malloc", GetStrWithmalloc},
        {"With realloc inc one char", GetStrWithOnerealloc},
        {"With realloc inc block", GetStrWithrealloc},
        {"With File", GetStrWithFile},
        {"With tmpFile", GetStrWithtmpFile},
    };

    int i = 0;
    int len = 0;
    char *p = NULL;

    for(i = 0; i < sizeof(strfoo) / sizeof(strfoo[0]); i++)
    {
        printf("%02d. %s: \n", i + 1, strfoo[i].msg);
        len = strfoo[i].pfoo(&p);
        printf("retlen = %d, strlen = %d\n", len, (int)strlen(p));
        puts(p);
        free(p);
        p = NULL;
    }
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetStrWithfgets(char **str)
// 功能: 输入任意长度字符串
// 算法: 利用realloc函数实现
//          通过fgets与calloc和realloc的配合实现。
//          无空间浪费。
// 参数:
//       [char **str] --- 字符串指针的地址
// 返回: [int]  --- 读入的字符长度，如果出错返回EOF
// 作者: 耿楠
// 日期: 2018年12月17日
// 注意: 需要删除fgets自动添加的'\n'
//-----------------------------------------------------------------------------------------------
int GetStrWithfgets(char **str)
{
    size_t bufsize = LEN, len = 0;
    char buf[LEN];

    // 申请内存
    char *p = (char *)calloc(1, 1);
    if(p == NULL)
    {
        *str  = p;
        return EOF;
    }

    while(fgets(buf, bufsize, stdin) != NULL)
    {
        len += strlen(buf); // 调整长度

        p = (char *)realloc(p, len); // 重新分配内存。
        if(p == NULL)
        {
            *str = p;
            return EOF;
        }

        strcat(p, buf); // 链接字符串

        // 自动添加了'\n'表示输入结束
        if(buf[strlen(buf) - 1] == '\n')
        {
            break;
        }
    }

    len = strlen(p);
    p[len - 1] = '\0'; // 字符串结束标志(删除fgets自动添加的'\n')

    *str = p; // 得到首地址

    return len - 1;
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetStrWithDofgets(char **str)
// 功能: 输入任意长度字符串
// 算法: 利用realloc函数实现
//          通过fgets与calloc和realloc的配合实现。
//          无空间浪费。
// 参数:
//       [char **str] --- 字符串指针的地址
// 返回: [int]  --- 读入的字符长度，如果出错返回EOF
// 作者: 耿楠
// 日期: 2018年12月17日
// 注意: 需要删除fgets自动添加的'\n'
//-----------------------------------------------------------------------------------------------
int GetStrWithDofgets(char **str)
{
    size_t blen = LEN; // 块长度
    char* p = NULL; // 字符串指针
    char buf[LEN];
    size_t plen = 0, tlen = 0;

    do
    {
        fgets(buf, blen, stdin); // 读入
        tlen = strlen(buf);
        plen += tlen;
        p = realloc(p, plen + 1); // 重新分配内存(按块增长)
        if(p == NULL)
        {
            *str = p;
            return EOF;
        }
        strcat(p, buf);
    }while (tlen == blen - 1 && buf[blen - 2] != '\n');


    plen = strlen(p); // 字符串长度
    p[plen - 1] = '\0'; // // 字符串结束标志(删除fgets自动添加的'\n')
    plen = strlen(p); // 字符串长度
    p = realloc(p, plen + 1);
    if(p == NULL)
    {
        *str = p;
        return EOF;
    }

    *str = p; // 得到首地址

    return plen; // 返回字符串长度
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetStrWithmalloc(char **str)
// 功能: 输入任意长度字符串
// 算法: 利用malloc函数实现
//          通过先申请1个字符的空间，然后不断为空间不断加1实现。
//          不存在空间浪费。
// 参数:
//       [char **str] --- 字符串指针的地址
// 返回: [int]  --- 读入的字符长度，如果出错返回EOF
// 作者: 耿楠
// 日期: 2018年12月17日
// 注意: 类似这样一个字节一个字节地申请内存释放内存，是很愚蠢的，不建议使用。
//-----------------------------------------------------------------------------------------------
int GetStrWithmalloc(char **str)
{
    int ch; // 接收的字符，注意需要用到int否则无法检测EOF
    int len = 1;

    char *p = (char *)malloc(len * sizeof(char)); // 申请一个字符的空间
    if(p == NULL)
    {
        *str = p;
        return EOF;
    }

    *p = '\0'; // 初始化

    // 处理第1个字符
    if((ch = getchar()) != EOF && ch != '\r'  && ch != '\n')
    {
        *p = ch;
        len++;
    }
    else
    {
        *str = p;
        return 0;
    }

    char *q = NULL;

    while((ch = getchar()) != EOF && ch != '\r'  && ch != '\n')
    {
        // 申请新的内存
        q = (char *)malloc(len * sizeof(char));
        if(q == NULL)
        {
            *str = p;
            return EOF;
        }
        // 将p里的内容复制到q中
        strcpy(q, p);
        // 将新录入的字符追加到q中
        q[len - 1] = ch;
        // 释放p指向的内存
        free(p);
        // 让p指向新的内存
        p = q;
        // 长度加1
        len++;
    }

    // 申请新的内存
    q = (char *)malloc(len * sizeof(char));
    if(p == NULL)
    {
        *str = p;
        return EOF;
    }

    // 将p里的内容复制到q中
    strcpy(q, p);
    // 添加终止字符
    q[len] = '\0';
    free(p);
    p = q;

    // 通过开参返回内存地址
    *str = p;

    // 返回长度
    return len - 1;
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetStrWithOnerealloc(char **str)
// 功能: 输入任意长度字符串
// 算法: 利用malloc和realloc函数实现
//          通过先申请1个字符的空间，然后不断为空间不断加1实现。
//          不存在空间浪费。
// 参数:
//       [char **str] --- 字符串指针的地址
// 返回: [int]  --- 读入的字符长度，如果出错返回EOF
// 作者: 耿楠
// 日期: 2018年12月17日
// 注意: 类似这样一个字节一个字节地申请内存释放内存，是很愚蠢的，不建议使用。
//-----------------------------------------------------------------------------------------------
int GetStrWithOnerealloc(char **str)
{
    int i;
    int ch; // 接收的字符，注意需要用到int否则无法检测EOF

    for(i = 0; 1; i++)
    {
        if(i != 0)
        {
            *str = (char *)realloc((*str), (i + 1) * sizeof(char)); // 重新分配空间(递增1个字节)
            if(*str == NULL)
            {
                return EOF;
            }
        }
        else
        {
            *str = (char *)malloc((i + 1) * sizeof(char)); // 分配新空间
            if(*str == NULL)
            {
                return EOF;
            }
        }

        ch = getchar(); // 读取字符
        (*str)[i] = ch; // 赋值

        if(ch == EOF || ch == '\r' || ch == '\n')
        {
            (*str)[i] = '\0'; // 终止字符
            break; // 跳出循环
        }
    }

    return i; // 返回长度
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetStrWithrealloc(char **str)
// 功能: 输入任意长度字符串
// 算法: 利用realloc函数实现
//          传入的指针已申请了LEN个空间空间，如果不够，则通过用realloc不断增加一个LEN实现。
//          无空间浪费。
// 参数:
//       [char *str] --- 字符串指针
// 返回: [int]  --- 读入的字符长度，如果出错返回EOF
// 作者: 耿楠
// 日期: 2018年12月17日
//-----------------------------------------------------------------------------------------------
int GetStrWithrealloc(char **str)
{
    int cnt = 0; // 计数器
    int ch; // 接收的字符，注意需要用到int否则无法检测EOF
    int len = LEN;

    char *p = (char *)calloc(len, sizeof(char)); // 分配内存时同时清0
    if(p == NULL)
    {
        *str = p;
        return EOF;
    }

    while((ch = getchar()) != EOF && ch != '\r'  && ch != '\n')
    {
        p[cnt++] = ch;
        if(cnt == len)
        {
            len += LEN;
            p = (char *)realloc(p, len); //不够，重新分配内存。
            if(p == NULL)
            {
                *str = p;
                return EOF;
            }
        }
    }

    p = (char *)realloc(p, cnt); //重新分配内存，避免内存浪费。
    p[cnt] = '\0'; // 字符串结束标志

    *str = p; // 得到首地址

    return cnt;
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetStrWithFile(char **str)
// 功能: 输入任意长度字符串
// 算法: 利用磁盘空间，打开一个缓存文件
//          先把输入的字符存到这个文件中，同时，得到了字符串的长度
//          接下来，向操作系统要这个长度的内存，然后从磁盘中读出这个文件到内存。
// 参数:
//       [char *str] --- 字符串指针
// 返回: [int]  --- 读入的字符长度，如果出错返回EOF
// 作者: 耿楠
// 日期: 2018年12月17日
//-----------------------------------------------------------------------------------------------
int GetStrWithFile(char **str)
{
    FILE *fp;
    int ch;
    size_t cnt = 0;
    char filename[] = "buf.dat"; // 文件名

    // 打开文件准备写(二进制写)
    if((fp = fopen(filename, "wb")) == NULL)
    {
        return EOF;
    }

    // 将读入的字符写入文件
    while((ch = getchar()) != '\n')
    {
        if(!ferror(fp))
        {
            fputc(ch, fp);
        }
        cnt++;
    }

    // 关闭文件
    fclose(fp);

    // 打开文件准备读(二进制读)
    if((fp = fopen(filename, "rb")) == NULL)
    {
        return EOF;
    }

    // 申请内存
    char *p = (char *)malloc((cnt) * sizeof(char));
    if(p == NULL)
    {
        *str = p;
        return EOF;
    }
    cnt = 0;
    while((ch = fgetc(fp)) != EOF)
    {
        p[cnt++] = ch;
    }

    p[cnt] = '\0'; // 终止字符

    // 关闭文件
    fclose(fp);

    (*str) = p;  // 得到首地址

    if(remove(filename) != 0)
    {
        return EOF;
    }

    return cnt;
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetStrWithtmpFile(char **str)
// 功能: 输入任意长度字符串
// 算法: 利用临时文件(内存文件)，打开一个缓存文件
//          先把输入的字符存到这个文件中，同时，得到了字符串的长度
//          接下来，向操作系统要这个长度的内存，然后从磁盘中读出这个文件到内存。
// 参数:
//       [char *str] --- 字符串指针
// 返回: [int]  --- 读入的字符长度，如果出错返回EOF
// 作者: 耿楠
// 日期: 2018年12月17日
//-----------------------------------------------------------------------------------------------
int GetStrWithtmpFile(char **str)
{
    FILE *fp;
    int ch;
    size_t cnt = 0;

    // 创建临时文件(内存文件, wb+读写模式)
    if((fp = tmpfile()) == NULL)
    {
        return EOF;
    }

    // 将读入的字符写入文件
    while((ch = getchar()) != '\n')
    {
        if(!ferror(fp))
        {
            fputc(ch, fp);
        }
        cnt++;
    }

    // 返回到文件头
    fseek(fp, 0, SEEK_SET);
    // 申请内存
    char *p = (char *)malloc((cnt) * sizeof(char));
    if(p == NULL)
    {
        *str = p;
        return EOF;
    }
    cnt = 0;
    while((ch = fgetc(fp)) != EOF)
    {
        p[cnt++] = ch;
    }

    p[cnt] = '\0'; // 终止字符

    // 关闭文件
    fclose(fp);

    (*str) = p;  // 得到首地址

    return cnt;
}



