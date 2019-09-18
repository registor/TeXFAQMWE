/*-------------------------------------------------------
* Copyright (c) 2010,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：bmp.c
* 文件标识：见配置管理计划书
* 摘要：Load_BMP()、Save_BMP()、GetPixel()、SetPixel()
        函数实现。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2010年12月30日
*
* 取代版本：无
* 原作者：无
* 完成日期：无
-------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h" // 图像读写头文件

//-------------------------------------------------------------------------
// 名称：int Load_BMP(const char *file_name, BMP_Data *bmp_data)
// 功能：读入24位真彩色图像
// 参数：
//           [const char *file_name] --- BMP图像文件名
//           [BMP_Data *bmp_data] --- 图像数据指针
// 返回：[int] --- 成功返回1，失败返回0
// 作者：耿楠
// 日期：2010年12月30日
//-------------------------------------------------------------------------
int Load_BMP(const char *file_name, BMP_Data *bmp_data)
{
    /* 变量声明 */
    FILEHEADER fHeader;
    INFOHEADER imgHeader;
    FILE *bmp_file;

    /* 打开图像文件 */
    if(!(bmp_file = fopen(file_name, "rb")))
    {
        return 0;
    }

    /* 读入文件头数据 */
    fread( &fHeader, sizeof(FILEHEADER), 1, bmp_file);
    /* 读入图像头数据 */
    fread( &imgHeader, sizeof(INFOHEADER), 1, bmp_file);

    /* 仅处理24位BMP图像 */
    if( *((char *)&fHeader.type) != 'B' &&
            *(((char *)&fHeader.type) + 1) != 'M' &&
            imgHeader.bits != 24 )
    {
        fclose( bmp_file );
        return 0;
    }

    /* 图像宽度和高度(像素) */
    bmp_data->width = imgHeader.width;
    bmp_data->height = imgHeader.height;

    /* 实际每行存储字节数 */
    bmp_data->widthbytes = ((bmp_data->width * 3) % 4 == 0) ?
                           (bmp_data->width * 3) : ((bmp_data->width * 3) / 4 * 4 + 4);

    /* 位图数据大小(字节) */
    unsigned int size = bmp_data->widthbytes * imgHeader.height * 3;

    /* 为存储图像数据分配内存 */
    bmp_data->data = (unsigned char *)malloc( size );

    /* 调整文件指针到图像数据区 */
    fseek( bmp_file, fHeader.offset, SEEK_SET);
    fread( bmp_data->data, size, 1, bmp_file);

    /* 关闭图像文件 */
    fclose( bmp_file );

    return 1;
}

//---------------------------------------------------------------------------
// 名称：int FlipUpDown(BMP_Data *bmp_data)
// 功能：图像数据垂直翻转
// 参数：
//           [BMP_Data *bmp_data] --- 图像数据指针
// 返回：[int] --- 成功返回1，失败返回0
// 作者：耿楠
// 日期：2019年1月16日
//---------------------------------------------------------------------------
int FlipUpDown(BMP_Data *bmp_data)
{
    // 每一行占用的字节数
    size_t colsize = bmp_data->widthbytes * sizeof(unsigned char);

    // 申请存储一行数据的内存空间
    unsigned char *p = malloc(colsize);
    if(p == NULL)
    {
        printf("Not enough memory!\n");
        return 0;
    }
    // 初始化
    memset(p, 0, colsize);

    // 图像数据指针
    unsigned char *q = bmp_data->data;
    // 参数预置
    unsigned int hf = bmp_data->height / 2;
    unsigned int hb = bmp_data->height - 1;

    /* 图像数据高度方向对调 */
    for(int i = 0; i < hf; i++)
    {
        memcpy(p, q + i * bmp_data->widthbytes, colsize);
        memcpy(q + i * bmp_data->widthbytes, q + (hb - i) * bmp_data->widthbytes, colsize);
        memcpy(q + (hb - i) * bmp_data->widthbytes, p, colsize);
    }

    // 释放内存
    free(p);

    return 1;
}

//---------------------------------------------------------------------------
// 名称：int Save_BMP(const char *file_name, BMP_Data *bmp_data)
// 功能：存储24位真彩色图像
// 参数：
//           [const char *file_name] --- BMP图像文件名
//           [BMP_Data *bmp_data] --- 图像数据指针
// 返回：[int] --- 成功返回1，失败返回0
// 作者：耿楠
// 日期：2010年12月30日
//---------------------------------------------------------------------------
int Save_BMP(const char *file_name, const BMP_Data *bmp_data)
{
    /* 变量声明 */
    FILEHEADER fHeader;
    INFOHEADER imgHeader;
    FILE *bmp_file;

    /* 图像大小(注意行字节数处理) */
    int imagsize = bmp_data->widthbytes * bmp_data->height;

    /* 初始化 */
    memset(&fHeader, 0, sizeof(FILEHEADER));
    memset(&imgHeader, 0, sizeof(INFOHEADER));

    /* BMP文件标志 */
    fHeader.type = 0x4D42;
    fHeader.size = imagsize + 54;
    fHeader.offset = 54;

    /* 图像信息头 */
    imgHeader.size = 40;
    imgHeader.width = bmp_data->width;
    imgHeader.height = bmp_data->height;
    imgHeader.bits = 24;
    imgHeader.imagesize = imagsize;
    imgHeader.planes = 1;

    /* 打开文件准备写 */
    if( !(bmp_file = fopen(file_name, "wb")) )
    {
        return 0;
    }

    /* 写入文件头 */
    fwrite( &fHeader, sizeof(fHeader), 1, bmp_file);
    /* 写入图像信息头 */
    fwrite( &imgHeader, sizeof(imgHeader), 1, bmp_file);
    /* 写入图像数据 */
    fwrite( bmp_data->data, imagsize, 1, bmp_file);

    /* 关闭文件 */
    fclose(bmp_file);

    return 1;
}

//--------------------------------------------------------------
// 名称：RGB GetPixel(int x, int y, BMP_Data *bmp_data)
// 功能：读取图像指定位置的像素值
// 参数：
//           [int x] --- 像素x坐标
//           [int y] --- 像素y坐标(未考虑倒序)
//           [BMP_Data *bmp_data] --- 图像数据
// 返回：[RGB] --- 像素值
// 作者：耿楠
// 日期：2010年12月30日
//--------------------------------------------------------------
RGB GetPixel(int x, int y, BMP_Data *bmp_data)
{
    RGB temprgb;
    unsigned char *p;

    /* 图像数据区首指针 */
    p = bmp_data->data;
    /* 偏移至第y行 */
    p += y * bmp_data->widthbytes;
    /* 偏移至第x列 */
    p += x * 3;

    /* 读像素值(三个字节) */
    memcpy(&temprgb, p, 3);

    return temprgb;
}

//-------------------------------------------------------------------------
// 名称：void SetPixel(int x, int y, RGB rgb, BMP_Data *bmp_data)
// 功能：读取图像像素值
// 参数：
//           [int x] --- 像素x坐标
//           [int y] --- 像素y坐标(未能考虑倒序)
//           [RGB rgb] --- 像素值
//           [BMP_Data *bmp_data] --- 图像数据
// 返回：无
// 作者：耿楠
// 日期：2010年12月30日
//-------------------------------------------------------------------------
void SetPixel(int x, int y, RGB rgb, BMP_Data *bmp_data)
{
    unsigned char *p;

    /* 图像数据区首指针 */
    p = bmp_data->data;
    /* 偏移至第y行 */
    p += y * bmp_data->widthbytes;
    /* 偏移至第x列 */
    p += x * 3;

    /* 写像素值(三个字节) */
    memcpy(p, &rgb, 3);
}
