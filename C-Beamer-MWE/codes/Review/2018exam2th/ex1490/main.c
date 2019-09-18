/*--------------------------------------------------------------------------------
* Copyright (c) 2019,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：寻找亲近的同学问题的演示代码。
*
* 问题描述：小明喜欢把他的同学分类，每一类用一个大写英文字母标记。
*           他只乐意亲近一部分类型的同学。
*           请从小明的同学中挑出他愿意亲近的同学。
* 输入：
*           输入三行。第一行是一个正整数m，m是小明的学号。
*           第二行是由大写字母组成的字符串，其中的字符表示小明喜欢的类型。
*           第三行是由大写字母组成的字符串，其中的字符是小明同学（包含他自己）
*           的类型，按照学号有序。学号从1开始，没有间断和重复。
*           小明的同学最多不超过1000个。
* 输出：
*           按照从小到大的顺序依次输出小明喜欢的同学的学号。
*           每个学号之后有一个空格。如果没有找到小明喜欢的同学，
*           则输出"Lonely Xiao Ming"。
* 输入样例：
*           1
*           ABC
*           BPTYHJKAMNBPHC
* 输出样例：
*           8 11 14
*
* 测试数据及对应输出结果见"data/"下的各个"*.in"文件及"*.out"
*
* 当前版本：1.0
* 作者：C语言课程组
* 完成日期：2019年1月16日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 宏定义
#define MAXNUM 1000

// 函数声明
int FindClosest(int *, int, const char *, const char *); // 查找亲近同学
void Output(int *, int); // 输出结果

// 测试
int main()
{
    // 声明变量
    int mno;
    char like[27]; // 26个大写字符+'\0'
    char classmate[MAXNUM + 1];  // MAXNUM个同学+'\0'
    int sno[MAXNUM];

    // 读入数据
    scanf("%d", &mno);
    scanf("%s", like);
    scanf("%s", classmate);

    // 处理数据
    int n = FindClosest(sno, mno, like, classmate);

    // 输出结果
    Output(sno, n);

    return 0;
}

// 函数定义
//-----------------------------------------------------------------------------------
// 名称: int FindClosest(int *sno, int myno, const char *like, const char *classmate)
// 功能: 查找亲近同学
// 算法: 利用字符搜索函数实现
// 参数:
//       [int *sno] --- 记录结果的数组
//       [int myno] --- 自己的学号
//       [const char *like] --- 喜欢类型字符串
//       [const char *classmate] --- 同学类型字符串
// 返回: [int]  --- 找到亲近同学总数
// 作者: C语言课程组
// 日期: 2019年1月16日
//-----------------------------------------------------------------------------------
int FindClosest(int *sno, int myno, const char *like, const char *classmate)
{
    int n = 0;

    // 指向同学类型字符串的指针
    const char* iter = classmate;
    while(*iter != '\0')
    {
        // 与自己的学号相同，跳过
        if(iter - classmate + 1 == myno)
        {
            iter++;
            continue;
        }
        // 用strchr判断like中是否有*iter，以确定是否是亲近类别
        if(strchr(like, *iter))
        {
            // 学号由"iter - classmate + 1"确定
            sno[n] = iter - classmate + 1;
            n++;
        }
        // 处理下一个字符
        iter++;
    }

    return n; // 返回找到的亲近同学总数
}

//----------------------------------------
// 名称: void FindClosest(int *sno, int n)
// 功能: 输出结果
// 参数:
//       [int *sno] --- 记录结果的数组
//       [int n] --- 亲近同学总数
// 返回: [int]  --- 找到的类别总数
// 作者: C语言课程组
// 日期: 2019年1月16日
//----------------------------------------
void Output(int *sno, int n)
{
    int i;

    if(n > 0)
    {
        for(i = 0; i < n - 1; i++)
        {
            printf("%d ", sno[i]);
        }
        printf("%d\n", sno[i]); // 避免最后输出多1个空格
    }
    else
    {
        printf("Lonely Xiao Ming\n");
    }
}



