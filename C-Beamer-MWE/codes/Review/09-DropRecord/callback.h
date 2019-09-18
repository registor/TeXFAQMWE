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

// 数组遍历中操作数组单个元素的功能函数
void FreeStu(void *);  // 释放一个结构体占有的内存
void OutputStuPt(void *);  // 输出一个结构体内容

int cmpStuID(const void *, const void *); // 按学号比较两个结构体大小(>)
int cmpStuAvg(const void *, const void *); // 按平均成绩比较两个结构体大小(<)

#endif // TRAVERSAL_H_INCLUDED
