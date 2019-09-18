/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示fseek、rewind函数的使用。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月13日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月13日
--------------------------------------------------------------------------------*/
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
// 从数据文件读入数据到数组
bool LoadFromDataFile(StuNode *, int, const char*);
// 修改数据
bool ModifyDataFile(const char*);
// 数组遍历，注意函数指针的使用
void Traversal(StuNode *, int, FILE *, bool (*)(StuNode *, FILE *));
// 功能函数
bool Input(StuNode *, FILE *); // 录入一个元素的数据
bool Output(StuNode *, FILE *); //  输出一个元素的数据

bool SaveItem(StuNode *, FILE *); // 录入一个元素的数据
bool LoadItem(StuNode *, FILE *); //  输出一个元素的数据

bool fcopy(const char *, const char *); // 复制文件

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
    StuNode stu[N];

    fcopy("databak.dat", "data.dat");

    LoadFromDataFile(stu, N, "data.dat");
    Traversal(stu, N, stdout, Output);
    printf("\n");

    ModifyDataFile("data.dat");

    LoadFromDataFile(stu, N, "data.dat");
    Traversal(stu, N, stdout, Output);

    return 0;
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
// 名称：bool ModifyDataFile(const char *filename)
// 功能：修改数据文件中的数据
// 参数：
//           [const char *filename] --- 数据文件文件名
// 返回：[bool]  --- 成功返回true，失败返回false
// 作者：耿楠
// 日期：2017年11月13日
//-----------------------------------------------------------------------------------------------
bool ModifyDataFile(const char *filename)
{
    FILE *fp;
    fpos_t pos;
    StuNode stu = {0};

    // 打开文件，二进制文件读/写模式
    if((fp = fopen(filename, "rb+")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", filename);
        return false; //打开文件失败
    }

    fseek(fp, 2L * sizeof(stu), SEEK_SET); // 向前偏移2个元素
    fread(&stu, sizeof(stu), 1, fp);
    fgetpos(fp, &pos); // 记录当前位置

    strcpy(stu.name, "ModifyName");
    fseek(fp, -1L * sizeof(stu), SEEK_CUR); // 向后偏移1个元素
    fwrite(&stu, sizeof(stu), 1, fp);

    rewind(fp); // 回退到文件开始位置
    fread(&stu, sizeof(stu), 1, fp);
    strcpy(stu.name, "First");
    fseek(fp, -1L * sizeof(stu), SEEK_CUR); // 向后偏移1个元素
    fwrite(&stu, sizeof(stu), 1, fp);

    fsetpos(fp, &pos); // 设置前面记录的位置
    fread(&stu, sizeof(stu), 1, fp);
    strcpy(stu.name, "SetPos");
    fseek(fp, -1L * sizeof(stu), SEEK_CUR); // 向后偏移1个元素
    fwrite(&stu, sizeof(stu), 1, fp);

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

//-----------------------------------------------------------------------------------------------
// 名称：bool fcopy(const char *srcname, const char *desname)
// 功能：搜索文件中以整数开始的行
// 参数：
//           [const char *srcname] --- 源文件名
//           [const char *desname] --- 目标文件名
// 返回：[bool]  --- 成功返回true, 失败返回false
// 作者：耿楠
// 日期：2017年11月12日
//-----------------------------------------------------------------------------------------------
bool fcopy(const char *srcname, const char *desname)
{
    FILE *src_fp, *des_fp; // 文件指针
    int ch; // 注意必须是整型

    // 打开源文件(二进制读方式)
    if ((src_fp = fopen(srcname, "rb")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", srcname);
        return false; //打开文件失败
    }

    // 打开目标文件(二进制写方式)
    if ((des_fp = fopen(desname, "wb")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", desname);
        fclose(src_fp); // 关闭已打开的文件
        return false;  // 打开文件失败
    }

    // 按字节复制(读一个字节，写一个字节)
    while ((ch = getc(src_fp)) != EOF)
    {
        putc(ch, des_fp);
    }

    // 关闭文件
    fclose(src_fp);
    fclose(des_fp);

    return true;
}
