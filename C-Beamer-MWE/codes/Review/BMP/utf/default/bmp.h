/*-------------------------------------------------------
* Copyright (c) 2010,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：bmp.h
* 文件标识：见配置管理计划书
* 摘要：图像文件头FILEHEADER、信息头INFOHEADER、数据BMP_Data
        、颜色RGB结构体的定义，函数原型声明。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2010年12月30日
*
* 取代版本：无
* 原作者：无
* 完成日期：无
-------------------------------------------------*/

#ifndef READ_BMP_H_INCLUDED
#define READ_BMP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "define.h"

/* 读入图像 */
int Load_BMP(const char *file_name, BMP_Data *bmp_data);
/* 保存图像 */
int Save_BMP(const char *file_name, const BMP_Data *bmp_data);
/* 读入指定像素值 */
RGB GetPixel(int x, int y, BMP_Data *bmp_data);
/* 设定指定像素值 */
void SetPixel(int x, int y, RGB rgb, BMP_Data *bmp_data);

#endif /* READ_BMP_H_INCLUDED*/
