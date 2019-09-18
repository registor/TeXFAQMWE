/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示结构体数组块读写操作。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月12日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月13日
--------------------------------------------------------------------------------*/
/** 测试数据
101
zhang san
male
1999
12
1
102
wang wu
female
1998
7
12
103
li si
male
2000
12
13
104
zhao liu
male
2000
4
27
105
lei qi
female
1999
1
24

**/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define N 5

// 日期结构体类型
typedef struct
{
    int year;    // 年
    int month;  // 月
    int day;     // 日
} Date;

// 学生结构体类型
typedef struct
{
    int ID;                       // 学号
    char name[20];            // 姓名
    char gender[13];         // 性别
    Date birthday;  // 生日
} StuNode;


// 函数原型

// 创建数据文件
bool CreateDataFile(StuNode *, int, const char*);
// 从数据文件读入数据到数组
bool LoadFromDataFile(StuNode *, int, const char*);

// 数组遍历，注意函数指针的使用
void Traversal(StuNode *, int, FILE *, bool (*)(StuNode *, FILE *));
// 功能函数
bool Input(StuNode *, FILE *); // 录入一个元素的数据
bool Output(StuNode *, FILE *); //  输出一个元素的数据

bool SaveItem(StuNode *, FILE *); // 录入一个元素的数据
bool LoadItem(StuNode *, FILE *); //  输出一个元素的数据

//-----------------------------------------------------------------------------------------------
// 名称：int main(int argc, char *argv[])
// 功能：主函数，程序入口
// 参数：
//           [int argc] --- 命令行参数个数
//           [char *argv[]] --- 命令行参数指针数组
// 返回：[int]  --- 成功返回0，其它返回非0
// 作者：耿楠
// 日期：2017年11月13日
//-----------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    StuNode stu[N];

    // 判断命令行参数是否正确
    if (argc != 2)
    {
        fprintf(stderr, "usage: students <datafilename>\n");
        exit(EXIT_FAILURE);
    }

    // 为数组读入数据
    Traversal(stu, N, stdin, Input);

    // 按单个元素的方式读入数据到数组
    if(!CreateDataFile(stu, N, argv[1]))
    {
        fprintf(stderr, "somthing wrong!\n");
        exit(EXIT_FAILURE);
    }

    // 按单个元素的方式读入数据到数组
    if(!LoadFromDataFile(stu, N, argv[1]))
    {
        fprintf(stderr, "somthing wrong!\n");
        exit(EXIT_FAILURE);
    }

    Traversal(stu, N, stdout, Output);

    return 0;
}

//-----------------------------------------------------------------------------------------------
// 名称：bool CreateDataFile(StuNode *pa, int n, const char *filename)
// 功能：创建数据文件
// 参数：
//           [StuNode *pa] --- 结构体数组指针
//           [int n] --- 数组长度
//           [const char *filename] --- 数据文件文件名
// 返回：[bool]  --- 成功返回true，失败返回false
// 作者：耿楠
// 日期：2017年11月13日
//-----------------------------------------------------------------------------------------------
bool CreateDataFile(StuNode *pa, int n, const char *filename)
{
    FILE *fp; // 声明文件指针

    // 打开文件，二进制文件模式
    if((fp = fopen(filename, "wb")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", filename);
        return false; //打开文件失败
    }

    Traversal(pa, n, fp, SaveItem);

    fclose(fp); // 关闭文件
    return true;
}

//-----------------------------------------------------------------------------------------------
// 名称：bool LoadFromDataFile(StuNode *pa, int n, const char *filename)
// 功能：创建数据文件
// 参数：
//           [StuNode *pa] --- 结构体数组指针
//           [int n] --- 数组长度
//           [const char *filename] --- 数据文件文件名
// 返回：[bool]  --- 成功返回true，失败返回false
// 作者：耿楠
// 日期：2017年11月13日
//-----------------------------------------------------------------------------------------------
bool LoadFromDataFile(StuNode *pa, int n, const char *filename)
{
    FILE *fp;

    // 打开文件，二进制文件模式
    if((fp = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", filename);
        return false; //打开文件失败
    }

    Traversal(pa, n, fp, LoadItem);

    fclose(fp); // 关闭文件
    return true;
}

//-----------------------------------------------------------------------------------------------
// 名称：void Traversal(StuNode *pa, int n, FILE *stream, bool (*pf)(StuNode *))
// 功能：遍历结构体数组
// 参数：
//           [StuNode *pa] --- 结构体数组指针
//           [int n] --- 数组长度
//           [FILE *stream] --- 文件流指针
//           [bool (*pf)(StuNode *] --- 处理每个单元的函数指针
// 返回：[void]  --- 无
// 作者：耿楠
// 日期：2017年11月13日
//-----------------------------------------------------------------------------------------------
void Traversal(StuNode *pa, int n, FILE *stream, bool (*pf)(StuNode *, FILE *))
{
    StuNode *p;

    // 遍历数组，使用指针进行操作
    for(p = pa; p < pa + n; p++)
    {
        pf(p, stream); // 调用传入的函数处理每个元素
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：bool Output(StuNode *pa, FILE *stream)
// 功能：在流上输出一个结构体变量的数据
// 参数：
//           [StuNode *pa] --- 结构体变量的指针
//           [FILE *stream] --- 文件流指针
// 返回：[bool]  --- 成功返回true, 失败返回false
// 作者：耿楠
// 日期：2017年11月13日
//-----------------------------------------------------------------------------------------------
bool Output(StuNode * pData, FILE *stream)
{
    // 输出一个结构体变量的数据
    fprintf(stream, "%d\t%s\t%s\t%d/%d/%d\n", pData->ID, pData->name,
            pData->gender, pData->birthday.year,
            pData->birthday.month, pData->birthday.day);

    return true;
}

//-----------------------------------------------------------------------------------------------
// 名称：bool Input(StuNode *pa, FILE *stream)
// 功能：从流中读入数据到结构体变量
// 参数：
//           [StuNode *pa] --- 结构体变量的指针
//           [FILE *stream] --- 文件流指针
// 返回：[bool]  --- 成功返回true, 失败返回false
// 作者：耿楠
// 日期：2017年11月13日
//-----------------------------------------------------------------------------------------------
bool Input(StuNode *pData, FILE *stream)
{
    memset(pData, 0, sizeof(*pData));  // 数据清0

    fscanf(stream, "%d", &pData->ID);
    fscanf(stream, "%*[^\n]"); // 清空前一次scanf留下的内容，不处理'\n'
    fscanf(stream, "%*c"); // 清空前一次scanf留下的'\n'
    fscanf(stream, "%[^\n]\n", pData->name); // 读入字符串(可读入除\n外的字符)
    fscanf(stream, "%[^\n]\n", pData->gender); // 读入字符串(可读入除\n外的字符)
    fscanf(stream, "%d", &pData->birthday.year);
    fscanf(stream, "%d", &pData->birthday.month);
    fscanf(stream, "%d", &pData->birthday.day);

    return true;
}

//-----------------------------------------------------------------------------------------------
// 名称：bool SaveItem(StuNode *pa, FILE *stream)
// 功能：从流中读入数据到结构体变量
// 参数：
//           [StuNode *pa] --- 结构体变量的指针
//           [FILE *stream] --- 文件流指针
// 返回：[bool]  --- 成功返回true, 失败返回false
// 作者：耿楠
// 日期：2017年11月13日
//-----------------------------------------------------------------------------------------------
bool SaveItem(StuNode *pa, FILE *stream)
{
    int count;
    count = fwrite(pa, sizeof(*pa), 1, stream);

    if(count != 1)
    {
        return false;
    }

    return true;
}
//-----------------------------------------------------------------------------------------------
// 名称：bool LoadItem(StuNode *pa, FILE *stream)
// 功能：从流中读入数据到结构体变量
// 参数：
//           [StuNode *pa] --- 结构体变量的指针
//           [FILE *stream] --- 文件流指针
// 返回：[bool]  --- 成功返回true, 失败返回false
// 作者：耿楠
// 日期：2017年11月13日
//-----------------------------------------------------------------------------------------------
bool LoadItem(StuNode *pa, FILE *stream)
{
    int count;
    count = fread(pa, sizeof(*pa), 1, stream);

    if(count != 1)
    {
        return false;
    }

    return true;
}
