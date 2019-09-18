/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：traversal.h
* 文件标识：见配置管理计划书
* 摘要：遍历数组函数原型的声明。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月28日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月28日
------------------------------------------------------------------------------------*/

#ifndef TRAVERSAL_H_INCLUDED
#define TRAVERSAL_H_INCLUDED

#define N 1000 // 数组长度
#define STRLEN 100 // 字符串长度

// 产生随机数组
void RandIntArray(void *, size_t, size_t); // 随机产生一个整数数组
void RandDfArray(void *, size_t, size_t); // 随机产生一个浮点数数组
void Rand2DCharArray(void *, size_t, size_t); // 随机产生一个字符串数组(二维字符型数组)
void RandStrPtArray(void *, size_t, size_t, size_t); // 随机产生一个字符串数组(字符型指针数组)

// 数组遍历中操作数组单个元素的功能函数
void InputInt(void *); // 用scanf输入一个整数
void RandInt(void *); // 用随机生成一个整数
void OutputInt(void *); // 用printf输出一个整数
void InputDf(void *);  // 用scanf输入一个浮点数
void RandDf(void *); // 用随机生成一个浮点数
void OutputDf(void *);  // 用printf输出一个浮点数
void InputStr(void *);  // 用scanf输入一个字符串
void OutputStr(void *);  // 用puts输出一个字符串
void OutputStrPt(void *);  // 用puts输出一个字符串
void OutputStu(void *);  // 输出一个结构体内容
void OutputStuPt(void *);  // 输出一个结构体内容

// 排序比较函数
int GreaterInt(const void *, const void *); // 比较两个整型数大小(>)
int LesserInt(const void *, const void *); // 比较两个整型数大小(<)
int GreaterDf(const void *, const void *); // 比较两个浮点数大小(>)
int LesserDf(const void *, const void *); // 比较两个浮点数大小(<)
int GreaterStr(const void *, const void *); // 比较两个字符串大小(>)
int LesserStr(const void *, const void *); // 比较两个字符串大小(<)
int GreaterStrPt(const void *, const void *); // 比较两个字符串(指针数组)大小(>)
int LesserStrPt(const void *, const void *); // 比较两个字符串(指针数组)大小(<)
int GreaterStu(const void *, const void *); // 比较两个结构体大小(>)
int LesserStu(const void *, const void *); // 比较两个结构体大小(<)
int GreaterStuPt(const void *, const void *); // 比较两个结构体大小(>)
int LesserStuPt(const void *, const void *); // 比较两个结构体大小(<)

#endif // TRAVERSAL_H_INCLUDED
