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
* 完成日期：2017年11月12日
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
bool CreateDataFileByItem(const char*); // 按单个元素的方式创建数据文件
bool CreateDataFileByOnce(const char*); // 按整个数组的方式创建数据文件
// 从数据文件中1次性读入数据到数组中
bool LoadByOnce(StuNode *, int, const char*);
// 从数据文件中1次读入一个元素数据到数组的一个元素中
bool LoadByItem(StuNode *, int, const char*);

// 数组遍历，注意函数指针的使用
void Traversal(StuNode *, int, void (*)(StuNode *));
// 功能函数
void Input(StuNode *); // 录入一个元素的数据
void Output(StuNode *); //  输出一个元素的数据

//-----------------------------------------------------------------------------------------------
// 名称：int main(int argc, char *argv[])
// 功能：主函数，程序入口
// 参数：
//           [int argc] --- 命令行参数个数
//           [char *argv[]] --- 命令行参数指针数组
// 返回：[int]  --- 成功返回0，其它返回非0
// 作者：耿楠
// 日期：2017年11月12日
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

    // 按单个元素的方式创建数据文件
    if(!CreateDataFileByItem(argv[1]))
    {
        fprintf(stderr, "somthing wrong!\n");
        exit(EXIT_FAILURE);
    }

    // 按整个数组的方式创建数据文件
    if(!CreateDataFileByOnce(argv[1]))
    {
        fprintf(stderr, "somthing wrong!\n");
        exit(EXIT_FAILURE);
    }

    // 按整个数组的方式读入数据到数组
    if(!LoadByOnce(stu, N, argv[1]))
    {
        fprintf(stderr, "somthing wrong!\n");
        exit(EXIT_FAILURE);
    }

    // 按单个元素的方式读入数据到数组
//    if(!LoadByItem(stu, N, argv[1]))
//    {
//        fprintf(stderr, "somthing wrong!\n");
//        exit(EXIT_FAILURE);
//    }

    Traversal(stu, N, Output);

    return 0;
}

//-----------------------------------------------------------------------------------------------
// 名称：bool CreateDataFileByItem(const char *filename)
// 功能：创建数据文件
// 参数：
//           [const char *filename] --- 数据文件文件名
// 返回：[bool]  --- 成功返回true，失败返回false
// 作者：耿楠
// 日期：2017年11月12日
//-----------------------------------------------------------------------------------------------
bool CreateDataFileByItem(const char *filename)
{
    int i;
    StuNode stu;
    FILE *fp;

    // 打开文件，二进制文件的追加模式
    if((fp = fopen(filename, "wb")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", filename);
        return false; //打开文件失败
    }

    for(i = 0; i < N; i++)
    {
        Input(&stu); // 读入一个学生的数据
        fwrite(&stu, sizeof(stu), 1, fp);
    }

    fclose(fp); // 关闭文件
    return true;
}

//-----------------------------------------------------------------------------------------------
// 名称：bool CreateDataFileByOnce(const char *filename)
// 功能：创建数据文件
// 参数：
//           [const char *filename] --- 数据文件文件名
// 返回：[bool]  --- 成功返回true，失败返回false
// 作者：耿楠
// 日期：2017年11月12日
//-----------------------------------------------------------------------------------------------
bool CreateDataFileByOnce(const char *filename)
{
    StuNode stu[N];
    FILE *fp;

    // 打开文件，二进制文件的追加模式
    if((fp = fopen(filename, "wb")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", filename);
        return false; //打开文件失败
    }

    Traversal(stu, N, Input);

    fwrite(stu, sizeof(stu[0]), N, fp);

    fclose(fp); // 关闭文件
    return true;
}

//-----------------------------------------------------------------------------------------------
// 名称：bool LoadByOnce(StuNode *pstu, int n, const char *filename)
// 功能：从数据文件读入数据到数组中
// 参数：
//           [StuNode *pstu] --- 数组指针
//           [int n] --- 数组长度
//           [const char *filename] --- 数据文件文件名
// 返回：[bool]  --- 成功返回true，失败返回false
// 作者：耿楠
// 日期：2017年11月12日
//-----------------------------------------------------------------------------------------------
bool LoadByOnce(StuNode *pstu, int n, const char *filename)
{
    int count;
    FILE *fp;

    // 打开文件，二进制文件的追加模式
    if((fp = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", filename);
        return false; //打开文件失败
    }

    // 一次读入所有数据
    count = fread(pstu, sizeof(pstu[0]), n, fp);

    if(count != n)
    {
        fclose(fp);
        return false;
    }

    fclose(fp); // 关闭文件
    return true;
}

//-----------------------------------------------------------------------------------------------
// 名称：bool LoadByItem(StuNode *pstu, int n, const char *filename)
// 功能：从数据文件读入数据到数组中
// 参数：
//           [StuNode *pstu] --- 数组指针
//           [int n] --- 数组长度
//           [const char *filename] --- 数据文件文件名
// 返回：[bool]  --- 成功返回true，失败返回false
// 作者：耿楠
// 日期：2017年11月12日
//-----------------------------------------------------------------------------------------------
bool LoadByItem(StuNode *pstu, int n, const char *filename)
{
    int count, i;
    FILE *fp;
    StuNode *p;

    // 打开文件，二进制文件的追加模式
    if((fp = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", filename);
        return false; //打开文件失败
    }

    p = pstu;
    for(i = 0; i < n; i++)
    {
        count = fread(p, sizeof(pstu[0]), 1, fp);
        if(count != 1)
        {
            fclose(fp);
            return false;
        }
        p++;
    }

    fclose(fp); // 关闭文件
    return true;
}

//-----------------------------------------------------------------------------------------------
// 名称：void Traversal(StuNode *pa, int n, void (*pf)(StuNode *))
// 功能：遍历结构体数组
// 参数：
//           [StuNode *pa] --- 结构体数组指针
//           [int n] --- 数组长度
//           [void (*pf)(StuNode *] --- 处理每个单元的函数指针
// 返回：[void]  --- 无
// 作者：耿楠
// 日期：2017年11月12日
//-----------------------------------------------------------------------------------------------
void Traversal(StuNode *pa, int n, void (*pf)(StuNode *))
{
    StuNode *p;

    // 遍历数组，使用指针进行操作
    for(p = pa; p < pa + n; p++)
    {
        pf(p); // 调用传入的函数处理每个元素
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void Output(StuNode *pa)
// 功能：在stdout流上输出一个结构体变量的数据
// 参数：
//           [StuNode *pa] --- 结构体变量的指针
// 返回：[void]  --- 无
// 作者：耿楠
// 日期：2017年11月12日
//-----------------------------------------------------------------------------------------------
void Output(StuNode * pData)
{
    // 输出一个结构体变量的数据
    printf("%d\t%s\t%s\t%d/%d/%d\n", pData->ID, pData->name,
           pData->gender, pData->birthday.year,
           pData->birthday.month, pData->birthday.day);
}

//-----------------------------------------------------------------------------------------------
// 名称：void Input(StuNode *pa)
// 功能：从stdin流中读入数据到结构体变量
// 参数：
//           [StuNode *pa] --- 结构体变量的指针
// 返回：[void]  --- 无
// 作者：耿楠
// 日期：2017年11月12日
//-----------------------------------------------------------------------------------------------
void Input(StuNode *pData)
{
    memset(pData, 0, sizeof(*pData));  // 数据清0

    scanf("%d", &pData->ID);
    scanf("%*[^\n]"); // 清空前一次scanf留下的内容，不处理'\n'
    scanf("%*c"); // 清空前一次scanf留下的'\n'
    scanf("%[^\n]\n", pData->name); // 读入字符串(可读入除\n外的字符)
    scanf("%[^\n]\n", pData->gender); // 读入字符串(可读入除\n外的字符)
    scanf("%d", &pData->birthday.year);
    scanf("%d", &pData->birthday.month);
    scanf("%d", &pData->birthday.day);
}
