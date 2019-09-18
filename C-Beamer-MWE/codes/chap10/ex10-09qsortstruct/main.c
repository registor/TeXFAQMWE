/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：利用qsort()函数及函数指针实现含有动态分配的成员变量的
*           动态结构体数组的排序操作。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月03日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月03日
------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define N 10

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
    char *name;            // 姓名
    char *gender;         // 性别
    Date birthday;  // 生日
} StuNode, *StuNodePt; // typedef重定义新名称

// 函数原型
// 数组遍历
void Traversal(StuNodePt *, int, void (*pf)(StuNodePt));
// 数组排序(对qsort函数的简单封装)
void QSortArray(StuNodePt *, int, int (*)(const void *, const void *));
// 功能函数
StuNodePt * CreateStructArray(int); // 动态创建数组
void Input(StuNodePt); // 输入一个元素的数据
void Output(StuNodePt); //  输出一个元素的数据
void DestroyNode(StuNodePt); // 销毁一个元素中的动态内存
// 初始化一个元素
bool InitNode(StuNodePt, int, const char *, const char *, int, int, int);
// 读入一行字符
int read_line(char*, int);
// 比较函数
int Greater(const void *, const void *);
int Lesser(const void *, const void *);

//-----------------------------------------------------------------------------------------------
// 名称：int main(void)
// 功能：主函数，程序入口
// 参数： 无
// 返回：int  --- 成功返回0，其它返回非0
// 作者：耿楠
// 日期：2017年11月03日
//-----------------------------------------------------------------------------------------------
int main(void)
{
    StuNodePt *pStu = NULL; // 防止野指针

    // 把输入重定向到文件"data.txt"
    freopen("data.txt", "r", stdin);
    // 动态创建数组
    pStu = CreateStructArray(N);
    // 把输入重定向回键盘
    freopen("CON", "r", stdin);
    // 遍历输出
    Traversal(pStu, N, Output);
    printf("\n");
    // 升序排序
    QSortArray(pStu, N, Greater);
    Traversal(pStu, N, Output);
    printf("\n");
    // 降序排序
    QSortArray(pStu, N, Lesser);
    Traversal(pStu, N, Output);
    printf("\n");
    // 遍历释放各个元素及其字符串内存
    Traversal(pStu, N, DestroyNode);
    // 释放指针数组
    free(pStu);
    pStu = NULL; // 防止野指针

    return 0;
}

//-----------------------------------------------------------------------------------------------
// 名称：void Traversal(StuNodePt *pa, int n, void (*pf)(StuNodePt))
// 功能：遍历数组，找到需要操作的数组元素
// 参数：
//       [StuNodePt *pa] --- 数组指针
//       [int n] --- 数组个数
//       [void (*pf)(StuNodePt)] --- 对元素执行操作的函数的函数指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月03日
//-----------------------------------------------------------------------------------------------
void Traversal(StuNodePt *pa, int n, void (*pf)(StuNodePt))
{
    StuNodePt *p;

    // 遍历数组，使用指针进行操作
    for(p = pa; p < pa + n; p++)
    {
        pf(*p); // 对遍历到的元素调用传入的函数进行操作
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void Input(StuNodePt pData)
// 功能：输入一个元素的数据
// 参数：
//       [StuNodePt pData] --- 当前元素的指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月03日
//-----------------------------------------------------------------------------------------------
void Input(StuNodePt pData)
{
    // 输入一个节点的数据
    int id;
    char name[81], gender[15];
    int year, month, day;

    // 读入学号
    scanf("%d", &id);

    // 跳过剩下的其它字符及'\n'
    while(getchar() != '\n')
        ;

    // 读入字符串
    read_line(name, 80);
    read_line(gender, 15);

    // 读入日期数据
    scanf("%d%d%d", &year, &month, &day);

    // 给一个节点各成员赋值(字符串需要动态分配)
    InitNode(pData, id, name, gender, year, month, day);
}

//-----------------------------------------------------------------------------------------------
// 名称：void Output(StuNodePt pData)
// 功能：输出一个元素的数据
// 参数：
//       [StuNodePt pData] --- 当前元素的指针是，返回非0是)
// 返回：无
// 作者：耿楠
// 日期：2017年11月03日
//-----------------------------------------------------------------------------------------------
void Output(StuNodePt pData)
{
    // 输出一个节点的数据
    printf("%d\t%s\t%s\t%d/%d/%d\n", pData->ID, pData->name, pData->gender,
           pData->birthday.year, pData->birthday.month, pData->birthday.day);
}

//-----------------------------------------------------------------------------------------------
// 名称：bool InitNode(StuNodePt pNode, int ID, const char *pname, const char *pgender, int year, int month, int day)
// 功能：创建一个元素，主要是涉及指针成员动态内存的创建
// 参数：
//       [StuNodePt pNode] --- 当前元素的指针
//       [int ID,] --- 学号
//       [const char *pname] --- 姓名(只读)
//       [const char *pgender] --- 性别(只读)
//       [int year] --- 年龄中的年
//       [int month] --- 年龄中的月
//       [int day] --- 年龄中的日
// 返回：bool  --- 成功返回真，失败返回假
// 作者：耿楠
// 日期：2017年11月03日
//-----------------------------------------------------------------------------------------------
bool InitNode(StuNodePt pNode, int ID, const char *pname, const char *pgender, int year, int month, int day)
{
    if(pNode == NULL || pname == NULL || pgender == NULL)
    {
        return false; // 空指针，无法后续操作，返回假值
    }

    // ID赋值
    pNode->ID = ID;

    // 为姓名和性别成员动态开避内存并赋值
    pNode->name = (char *)malloc((strlen(pname) + 1) * sizeof(char));
    pNode->gender = (char *)malloc((strlen(pgender) + 1) * sizeof(char));
    if(pNode->name == NULL || pNode->gender == NULL)
    {
        pNode->ID = -1;
        return false;  // 内存分配出错，返回假值
    }
    // 动态内存赋值
    strcpy(pNode->name, pname);
    strcpy(pNode->gender, pgender);

    // 其它成员赋值
    pNode->birthday.year = year;
    pNode->birthday.month = month;
    pNode->birthday.day = day;

    return true; // 一切正常，返回真值
}

//-----------------------------------------------------------------------------------------------
// 名称：StuNodePt * CreateStructArray(int n)
// 功能：创建动态数组
// 参数：
//       [int n] --- 动态数组的个数
// 返回：StuNodePt * --- 动态数组的起始地址，失败返回NULL
// 作者：耿楠
// 日期：2017年11月03日
//-----------------------------------------------------------------------------------------------
StuNodePt * CreateStructArray(int n)
{
    int i;
    StuNodePt *p;

    // 分配指针数组
    p = (StuNodePt *)malloc(n * sizeof(StuNodePt));
    if(p == NULL)
    {
        return NULL;  // 内存分配出错，返回NULL
    }

    // 分配结构体变量内存
    for(i = 0; i < n; i++)
    {
        p[i] = (StuNodePt)malloc(1 * sizeof(StuNode));
        if(p[i] == NULL)
        {
            return NULL;  // 内存分配出错，返回NULL
        }
        Input(p[i]); // 为一个变量读入数据
    }

    return p;
}

//-----------------------------------------------------------------------------------------------
// 名称：void DestroyNode(StuNodePt pNode)
// 功能：销毁当前元素中的动态数据及自身占用的内存
// 参数：
//       [StuNodePt pNode] --- 当前元素的指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月03日
//-----------------------------------------------------------------------------------------------
void DestroyNode(StuNodePt pNode)
{
    // 释放节点中动态分配的内存
    free(pNode->name);
    pNode->name = NULL; // 防止野指针
    free(pNode->gender);
    pNode->name = NULL; // 防止野指针

    // 释放自己
    free(pNode);
    pNode = NULL; // 防止野指针
}

//-----------------------------------------------------------------------------------------------
// 名称：int read_line(char *str, int n)
// 功能：通过键盘读入一行字符串(以'\n'结束，可以读入空白)
// 参数：
//       [char *str] --- 字符串缓冲区指针(存储读入字符的内存首地址)
//       [int n] --- 能够读入字符的个数
// 返回：int  --- 返回读入字符的个数
// 作者：耿楠
// 日期：2017年11月03日
//-----------------------------------------------------------------------------------------------
int read_line(char *str, int n)
{
    int ch, i = 0;

    // 读入字符，直到遇到换行符
    while ((ch = getchar()) != '\n')
    {
        if(i < n) /* 最大字符数 */
        {
            str[i++] = ch;
        }
    }
    str[i] = '\0'; /* 添加空字符'\0' */

    return i;    /* 返回读入的字符数 */
}

//-----------------------------------------------------------------------------------------------
// 名称：int Greater(const void *pa, const void *pb)
// 功能：qsort函数用到的升序比较函数
// 参数：
//       [const void *pa] --- 需要比较的元素1的指针
//       [const void *pb] --- 需要比较的元素2的指针
// 返回：int  --- 大于返回正值, 等于返回0, 小于返回负值
// 作者：耿楠
// 日期：2017年11月03日
//-----------------------------------------------------------------------------------------------
int Greater(const void *pa, const void *pb)
{
    // 需要先转换为(StuNodePt*)指针
    StuNodePt *p1 = (StuNodePt *)pa;
    StuNodePt *p2 = (StuNodePt *)pb;

    return ((*p1)->ID - (*p2)->ID); // 必须在(*p1)和(*p2)使用小括号，否则有优先级问题
}

//-----------------------------------------------------------------------------------------------
// 名称：int Greater(const void *pa, const void *pb)
// 功能：qsort函数用到的降序比较函数
// 参数：
//       [const void *pa] --- 需要比较的元素1的指针
//       [const void *pb] --- 需要比较的元素2的指针
// 返回：int  --- 大于返回正值, 等于返回0, 小于返回负值
// 作者：耿楠
// 日期：2017年11月03日
//-----------------------------------------------------------------------------------------------
int Lesser(const void *pa, const void *pb)
{
    // 需要先转换为(StuNodePt*)指针
    StuNodePt *p1 = (StuNodePt *)pa;
    StuNodePt *p2 = (StuNodePt *)pb;

    return ((*p2)->ID - (*p1)->ID); // 必须在(*p1)和(*p2)使用小括号，否则有优先级问题
}

//-----------------------------------------------------------------------------------------------
// 名称：void QSortArray(StuNodePt *pa, int n, int (*pf)(const void *, const void *))
// 功能：调用qsort函数的包装器函数
// 参数：
//       [StuNodePt *pa] --- 要排序的起始地址
//       [int n] --- 参与排序的个数
//       [int (*pf)(const void *, const void *)] --- 比较函数指针
//       [int (*pred)(char)] --- 判断函数指针(返回0不是，返回非0是)
// 返回：无
// 作者：耿楠
// 日期：2017年11月03日
//-----------------------------------------------------------------------------------------------
void QSortArray(StuNodePt *pa, int n, int (*pf)(const void *, const void *))
{
    qsort(pa, n, sizeof(pa[0]), pf); // 调用qsort函数排序
}
