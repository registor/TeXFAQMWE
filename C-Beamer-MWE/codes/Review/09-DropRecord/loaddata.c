#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "loaddata.h"

// 删除字符串起始与结尾空白(只在本文件中使用，用static限定)
static void trimWhitespace(char * s)
{
    char * p = s;
    int l = strlen(p); // 字符串长度

    while(isspace(p[l - 1])) // 是空白字符
    {
        p[--l] = 0; // 赋为'\0'，长度减1
    }

    while(* p && isspace(* p)) // 是空白字符
    {
        ++p; // 调整指针
        --l; // 长度减1
    }

    memmove(s, p, l + 1); // 复制到起始地址
}

// 利用scanf的扫描字符集读入带有空白的字符串(只在本文件中使用，用static限定)
// 详情参见：K.N. King 著, 吕秀锋 黄倩译. C语言程序设计:现代方法(第2版), 北京:人民邮电出版社, 2013, PP: 400-401.
static void scanDataWithSet(const char *strin, unsigned int *pID, char *name, double *pgrade)
{
    int offset = 0;

    // %[^0-9]用于读到发现数字为止
    // %n用于统计到目前为止读入的字符数量
    sscanf(strin, "%d %[^0-9]%n", pID, name, &offset);

    strin += offset;
    for(int i = 0; i < NGRADE; i++)
    {
        // sscanf返回值用于检测是否正常读入了1个数。
        if(sscanf(strin, " %lf%n", pgrade + i, &offset) != 1)
        {
            break;
        }
        strin += offset; // 调整字符串指针
    }

    // 清除开始和结束空白符
    trimWhitespace(name);
}

// 找到需要读取的字符串的起始和结束地址，然后读入(只在本文件中使用，用static限定)
// 注意：本函数只能读入前导和后继为数字的1个字符串
static void scanDataWithStr(char *strin, unsigned int *pID, char *name, double *pgrade)
{
    char *pstart = NULL, *pend = NULL; // 字符串起始结束指针

    char *p = strin;

    while(*p != '\0') // 扫描字符串
    {
        if(*(p + 2) != '\0')
        {
            if(isdigit(*p) && isspace(*(p + 1))) // 前导是数字，当前是空白
            {
                pstart = p + 2; // 字符串起始地址
                p++;
                continue;
            }
        }

        if(*(p + 1) != '\0')
        {
            if(isspace(*p) && isdigit(*(p + 1))) // 当前是空白， 后继是数字
            {
                pend = p; // 字符串结束地址
                break; // 只处理一个字符串
            }
        }
        p++;
    }

    if(pstart != NULL && pend != NULL) // 找到字符串
    {
        *(pstart - 1) = '\0'; // 置'\0'，目的是分割为3节字符串
        *pend = '\0';
    }

    sscanf(strin, "%d", pID); // 读入学号
    strcpy(name, pstart); // 读入字符串(只处理1个字符串)
    trimWhitespace(name); // 清除开始和结束空白符

    int offset = 0;
    pend++;

    for(int i = 0; i < NGRADE; i++)
    {
        // %n用于统计到目前为止读入的字符数量
        // sscanf返回值用于检测是否正常读入了1个数。
        if(sscanf(pend, " %lf%n", pgrade + i, &offset) != 1)
        {
            break;
        }
        pend += offset; // 调整字符串指针
    }

//    int idx = 0; //
//    while(sscanf(pend, " %lf%n", pgrade + idx, &offset) == 1)
//    {
//        idx++;
//        pend += offset;
//    }
    //sscanf(pend + 1, "%lf %lf %lf", &pgrade[0], &pgrade[1], &pgrade[2]); // 读入其它数据（只能读3个数，应该用宏）
}

// 按扫描字符集方式读入数据
Student ** loadDataWithScanSet(const char *fname1, const char *fname2)
{
    FILE *fp1, *fp2; // 文件指针

    Student **pst, **p;

    char buffer[1024]; // 字符串缓冲区

    fp1 = fopen(fname1, "r"); // 打开文件(注意没有处理错误！)
    fp2 = fopen(fname2, "r");

    int l1;
    int l2;
    int length;

    fscanf(fp1, "%d", &l1); // 记录个数
    fgets(buffer, sizeof(buffer), fp1); // 跳过'\n'

    fscanf(fp2, "%d", &l2);
    fgets(buffer, sizeof(buffer), fp2);

    length = l1 + l2;

    pst = malloc((length + 1) * sizeof(Student*)); // 指针数组(多申请1个，为了用NULL结束循环)
    memset(pst, 0, (length + 1) * sizeof(Student*)); // 清0

    p = pst;
    for(int i = 0; i < l1; i++)
    {
        fgets(buffer, sizeof(buffer), fp1); // 读入一行字符串
        p[i] = malloc(sizeof(Student)); // 申请1个结构体空间
        memset(p[i], 0, sizeof(Student)); // 清0

        scanDataWithSet(buffer, &p[i]->ID, p[i]->name, p[i]->grade); // 读入数据
    }

    p = pst + l1; // 另一级数据
    for(int i = 0; i < l2; i++)
    {
        fgets(buffer, sizeof(buffer), fp2);
        p[i] = malloc(sizeof(Student));
        memset(p[i], 0, sizeof(Student));

        scanDataWithSet(buffer, &p[i]->ID, p[i]->name, p[i]->grade);
    }

    // 关闭文件
    fclose(fp1);
    fclose(fp2);

    return pst; // 返回指针
}

// 按字符串方式读入数据
Student ** loadDataWithGets(const char *fname1, const char *fname2)
{
    FILE *fp1, *fp2; // 文件指针

    Student **pst, **p;

    char buffer[1024]; // 字符串缓冲区

    fp1 = fopen(fname1, "r"); // 打开文件(注意没有处理错误！)
    fp2 = fopen(fname2, "r");

    int l1;
    int l2;
    int length;

    fscanf(fp1, "%d", &l1); // 记录个数
    fgets(buffer, sizeof(buffer), fp1); // 跳过'\n'
    fscanf(fp2, "%d", &l2);
    fgets(buffer, sizeof(buffer), fp2);

    length = l1 + l2;

    pst = malloc((length + 1) * sizeof(Student*)); // 指针数组(多申请1个，为了用NULL结束循环)
    memset(pst, 0, (length + 1) * sizeof(Student*)); // 清0

    p = pst;
    for(int i = 0; i < l1; i++)
    {
        fgets(buffer, sizeof(buffer), fp1); // 读入一行字符串
        p[i] = malloc(sizeof(Student)); // 申请1个结构体空间
        memset(p[i], 0, sizeof(Student)); // 清0

        scanDataWithStr(buffer, &p[i]->ID, p[i]->name, p[i]->grade); // 读入数据
    }

    p = pst + l1; // 另一级数据
    for(int i = 0; i < l2; i++)
    {
        fgets(buffer, sizeof(buffer), fp2);
        p[i] = malloc(sizeof(Student));
        memset(p[i], 0, sizeof(Student));

        scanDataWithStr(buffer, &p[i]->ID, p[i]->name, p[i]->grade);
    }

    //  关闭文件
    fclose(fp1);
    fclose(fp2);

    return pst; // 返回指针
}
