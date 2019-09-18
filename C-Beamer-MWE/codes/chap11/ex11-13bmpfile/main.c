/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示图像文件的读写。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月14日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月14日
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>

#define NAME_LEN 255

//设定结构体以字节为单位
#pragma pack(1)

/*文件头*/
typedef struct
{
    unsigned short int type;      /* 标识                     */
    unsigned int size;            /* 文件大小（bytes）        */
    unsigned short int reserved1; /* 保留字                   */
    unsigned short int reserved2;
    unsigned int offset;          /* 图像数据偏移地址（bytes）*/
} FILEHEADER;

/*图像信息头*/
typedef struct
{
    unsigned int size;               /* 信息头大小（bytes） */
    int width, height;               /* 图像宽和高（pixels) */
    unsigned short int planes;       /* 颜色平面            */
    unsigned short int bits;         /* 颜色深度            */
    unsigned int compression;        /* 压缩类型            */
    unsigned int imagesize;          /* 图像数据大小(bytes) */
    int xresolution, yresolution;    /* 单位长度像素数      */
    unsigned int ncolours;           /* 颜色数              */
    unsigned int importantcolours;   /* 重要颜色数          */
} INFOHEADER;

/*图像数据信息*/
typedef struct
{
    unsigned int width;       /* 位图的宽度，以像素为单位 */
    unsigned int height;      /* 位图的高度，以像素为单位 */
    unsigned int widthbytes;  /* 位图的字节宽度           */
    unsigned char *data;      /* 图像数据指针             */
} BMP_Data;

/*图像数据信息*/
typedef struct
{
    unsigned char b; /* 蓝 */
    unsigned char g; /* 绿 */
    unsigned char r; /* 红 */
} RGB;

// 函数原型
/* 读入图像 */
bool Load_BMP(const char *file_name, BMP_Data *bmp_data);
/* 保存图像 */
bool Save_BMP(const char *file_name, const BMP_Data *bmp_data);
/* 读入指定像素值 */
RGB GetPixel(int x, int y, BMP_Data *bmp_data);
/* 设定指定像素值 */
void SetPixel(int x, int y, RGB rgb, BMP_Data *bmp_data);

/* 灰度化 */
void RGB2Gray(BMP_Data *);
/* 截取感兴趣区域(ROI)子图像 */
BMP_Data * GetROI(int, int, int, int, BMP_Data *);
/* 在原图像中按指定坐标绘制直线 */
void DrawLine(int, int, int, int, BMP_Data *);
/* 按比例融合两副图像数据 */
void BlendTwoBMP(double, BMP_Data *, BMP_Data *);

/* 启动操作 */
void run(void);

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

    run();

    return 0;
}

//--------------------------------------------------------------
// 名称：void run(void)
// 功能：启动图像处理操作
// 参数：
//           [void] --- 无
// 返回：[void] --- 无
// 作者：耿楠
// 日期：2017年11月14日
//--------------------------------------------------------------
void run(void)
{
    char srcfile1[NAME_LEN + 1] = "Penguins.bmp";
    char srcfile2[NAME_LEN + 1] = "Lighthouse.bmp";
    char desfile[NAME_LEN + 1] = "";

    BMP_Data srcData1;
    BMP_Data srcData2;
    BMP_Data *pDesData;

    puts("image loading...");
    // 读入图像
    if( !Load_BMP(srcfile1, &srcData1) )
    {
        fprintf(stderr, "src image1 loading error!\n");
        exit(EXIT_FAILURE);
    }

    if( !Load_BMP(srcfile2, &srcData2) )
    {
        fprintf(stderr, "src image2 loading error!\n");
        exit(EXIT_FAILURE);
    }

    puts("image processing...");

    // 测试灰度化函数
    strcpy(desfile, "PenguinsGray.bmp");
    RGB2Gray(&srcData1);
    if( !Save_BMP(desfile, &srcData1) )
    {
        fprintf(stderr, "save src image1 gray error!\n");
        exit(EXIT_FAILURE);
    }

    strcpy(desfile, "LighthouseGray.bmp");
    RGB2Gray(&srcData2);
    if( !Save_BMP(desfile, &srcData2) )
    {
        fprintf(stderr, "save src image2 gray error!\n");
        exit(EXIT_FAILURE);
    }

    // 测试(ROI)子图像函数
    strcpy(desfile, "PenguinsROI.bmp");
    pDesData = GetROI(50, 345, 320, 240, &srcData1);
    if( !Save_BMP(desfile, pDesData) )
    {
        fprintf(stderr, "save src image1 ROI error!\n");
        exit(EXIT_FAILURE);
    }
    free(pDesData->data);
    free(pDesData);

    strcpy(desfile, "LighthouseROI.bmp");
    pDesData = GetROI(30, 10, 640, 480, &srcData2);
    if( !Save_BMP(desfile, pDesData) )
    {
        fprintf(stderr, "save src image2 ROI error!\n");
        exit(EXIT_FAILURE);
    }
    free(pDesData->data);
    free(pDesData);

    // 测试绘制直线函数
    strcpy(desfile, "PenguinsLine.bmp");
    DrawLine(100, 100, 200, 200, &srcData1);
    if( !Save_BMP(desfile, &srcData1) )
    {
        fprintf(stderr, "save src image1 line error!\n");
        exit(EXIT_FAILURE);
    }

    strcpy(desfile, "LighthouseLine.bmp");
    DrawLine(50, 50, 100, 200, &srcData2);
    if( !Save_BMP(desfile, &srcData2) )
    {
        fprintf(stderr, "save src image2 line error!\n");
        exit(EXIT_FAILURE);
    }

    // 测试按比例融合两副图像函数
    strcpy(desfile, "BlendedImage.bmp");
    BlendTwoBMP(0.5, &srcData2, &srcData1);
    if( !Save_BMP(desfile, &srcData2) )
    {
        fprintf(stderr, "save image blend error!\n");
        exit(EXIT_FAILURE);
    }

    // 释放内存空间
    free(srcData1.data);
    free(srcData2.data);
}
//--------------------------------------------------------------
// 名称：bool Load_BMP(const char *file_name, BMP_Data *bmp_data)
// 功能：读入24位真彩色图像
// 参数：
//           [const char *file_name] --- BMP图像文件名
//           [BMP_Data *bmp_data] --- 图像数据指针
// 返回：[bool] --- 成功返回true，失败返回false
// 作者：耿楠
// 日期：2017年11月14日
//--------------------------------------------------------------
bool Load_BMP(const char *file_name, BMP_Data *bmp_data)
{
    FILEHEADER fHeader;
    INFOHEADER imgHeader;
    FILE *bmp_file;

    if( !(bmp_file = fopen(file_name, "rb")) )
    {
        return false;
    }

    /* 读入文件头数据*/
    fread( &fHeader, sizeof(FILEHEADER), 1, bmp_file);
    /* 读入图像头数据*/
    fread( &imgHeader, sizeof(INFOHEADER), 1, bmp_file);

    /* 判断是不是24位BMP图像*/
    if( *((char *)&fHeader.type) != 'B' &&
            *(((char *)&fHeader.type) + 1) != 'M' &&
            imgHeader.bits != 24 )
    {
        fclose( bmp_file );
        return false;
    }

    // 图像宽度和高度（像素）
    bmp_data->width = imgHeader.width;
    bmp_data->height = imgHeader.height;

    // 实际每行存储字节数
    bmp_data->widthbytes = ((bmp_data->width * 3) % 4 == 0) ?
                           (bmp_data->width * 3) : ((bmp_data->width * 3) / 4 * 4 + 4);
    // 位图数据大小（字节）
    unsigned int size = bmp_data->widthbytes * imgHeader.height * 3;

    /* 为存储图像数据分配内存*/
    bmp_data->data = (unsigned char *)malloc( size );

    //调整文件指针到图像数据区
    fseek( bmp_file, fHeader.offset, SEEK_SET);
    fread( bmp_data->data, size, 1, bmp_file);

    fclose( bmp_file );

    return true;
}

//--------------------------------------------------------------
// 名称：bool Save_BMP(const char *file_name, BMP_Data *bmp_data)
// 功能：存储24位真彩色图像
// 参数：
//           [const char *file_name] --- BMP图像文件名
//           [BMP_Data *bmp_data] --- 图像数据指针
// 返回：[bool] --- 成功返回true，失败返回false
// 作者：耿楠
// 日期：2017年11月14日
//--------------------------------------------------------------
bool Save_BMP(const char *file_name, const BMP_Data *bmp_data)
{
    FILEHEADER fHeader;
    INFOHEADER imgHeader;
    FILE *bmp_file;

    int imagsize = bmp_data->widthbytes * bmp_data->height;

    memset(&fHeader, 0, sizeof(FILEHEADER));
    memset(&imgHeader, 0, sizeof(INFOHEADER));

    //BMP文件标志
    fHeader.type = 0x4D42;
    fHeader.size = imagsize + 54;
    fHeader.offset = 54;

    imgHeader.size = 40;
    imgHeader.width = bmp_data->width;
    imgHeader.height = bmp_data->height;
    imgHeader.bits = 24;
    imgHeader.imagesize = imagsize;
    imgHeader.planes = 1;

    if( !(bmp_file = fopen(file_name, "wb")) )
    {
        return false;
    }

    fwrite( &fHeader, sizeof(fHeader), 1, bmp_file);
    fwrite( &imgHeader, sizeof(imgHeader), 1, bmp_file);
    fwrite( bmp_data->data, imagsize, 1, bmp_file);

    fclose(bmp_file);

    return true;
}

//--------------------------------------------------------------
// 名称：RGB GetPixel(int x, int y, BMP_Data *bmp_data)
// 功能：读取图像像素值
// 参数：
//           [int x] --- 像素x坐标
//           [int y] --- 像素y坐标（未考虑倒序）
//           [BMP_Data *bmp_data] --- 图像数据
// 返回：[RGB] --- 像素值
// 作者：耿楠
// 日期：2017年11月14日
//--------------------------------------------------------------
RGB GetPixel(int x, int y, BMP_Data *bmp_data)
{
    RGB temprgb;
    unsigned char *p;

    // 图像数据区首指针
    p = bmp_data->data;
    // 偏移至第y行
    p += y * bmp_data->widthbytes;
    // 偏移至第x列
    p += x * 3;

    // 读像素值（三个字节）
    memcpy(&temprgb, p, 3);

    return temprgb;
}

//--------------------------------------------------------------
// 名称：void SetPixel(int x, int y, RGB rgb, BMP_Data *bmp_data)
// 功能：读取图像像素值
// 参数：
//          [int x] --- 像素x坐标
//          [int y] --- 像素y坐标（未能考虑倒序）
//          [RGB rgb] --- 像素值
//          [BMP_Data *bmp_data] --- 图像数据
// 返回：无
// 作者：耿楠
// 日期：2017年11月14日
//--------------------------------------------------------------
void SetPixel(int x, int y, RGB rgb, BMP_Data *bmp_data)
{
    unsigned char *p;

    // 图像数据区首指针
    p = bmp_data->data;
    // 偏移至第y行
    p += y * bmp_data->widthbytes;
    // 偏移至第x列
    p += x * 3;

    // 写像素值（三个字节）
    memcpy(p, &rgb, 3);
}

//--------------------------------------------------------------
// 名称：void RGB2Gray(BMP_Data *bmp_data)
// 功能：将RGB真彩色图像转换为灰度图像
// 参数：
//          [BMP_Data *bmp_data] --- 图像数据
// 返回：无
// 作者：耿楠
// 日期：2017年11月14日
//--------------------------------------------------------------
void RGB2Gray(BMP_Data *data)
{
    int x, y;
    RGB temp;
    int gray;

    for(y = 0; y < data->height; y++)
    {
        for(x = 0; x < data->width; x++)
        {
            temp = GetPixel(x, y, data);
            // 求R、G、B平均值
            gray = (temp.r + temp.g + temp.b) / 3;
            temp.r = gray;
            temp.g = gray;
            temp.b = gray;
            SetPixel(x, y, temp, data);
        }
    }
}

//--------------------------------------------------------------
// 名称：BMP_Data * GetROI(int x0, int y0, int w, int h, BMP_Data *bmp_data)
// 功能：截取子图像
// 参数：
//          [int x0] --- ROI区域起点x坐标(原点是左下角，向右为正)
//          [int y0] --- ROI区域起点y坐标(原点是左下角，向上为正)
//          [int w] --- ROI区域宽度
//          [int w] --- ROI区域高度
//          [BMP_Data *bmp_data] --- 图像数据
// 返回：[BMP_Data *] --- ROI图像数据
// 作者：耿楠
// 日期：2017年11月14日
//--------------------------------------------------------------
BMP_Data * GetROI(int x0, int y0, int w, int h, BMP_Data *data)
{
    int x, y;
    RGB temp;

    BMP_Data *pImg = (BMP_Data *)malloc(sizeof(*pImg));

    pImg->width = w;
    pImg->height = h;

    //实际每行存储字节数
    pImg->widthbytes = ((pImg->width * 3) % 4 == 0) ?
                       (pImg->width * 3) : ((pImg->width * 3) / 4 * 4 + 4);
    pImg->data = (unsigned char *)malloc(pImg->widthbytes * pImg->height);

    for(y = 0; y < pImg->height; y++)
    {
        for(x = 0; x < pImg->width; x++)
        {
            temp = GetPixel(x0 + x, y0 + y, data);
            SetPixel(x, y, temp, pImg);
        }
    }

    return pImg;
}

//--------------------------------------------------------------
// 名称：void DrawLine(int x0, int y0, int x1, int y1, BMP_Data *bmp_data)
// 功能：在原图像中按指定坐标绘制直线
// 参数：
//          [int x0] --- 起点x坐标(原点是左下角，向右为正)
//          [int y0] --- 起点y坐标(原点是左下角，向上为正)
//          [int x1] --- 终点x坐标(原点是左下角，向右为正)
//          [int y1] --- 终点y坐标(原点是左下角，向上为正)
//          [BMP_Data *bmp_data] --- 图像数据
// 返回：无
// 作者：耿楠
// 日期：2017年11月14日
//--------------------------------------------------------------
void DrawLine(int x0, int y0, int x1, int y1, BMP_Data *data)
{
    int x = 0, y = 0;
    RGB temp;
    double k;

    temp.r = 255;
    temp.g = 0;
    temp.b = 0;

    k  = (double)(y1 - y0) / (double)(x1 - x0); // 计算直线斜率

    for(x = x0; x < x1; x++)
    {
        y = (int)(k * (x - x0) + y0); // 计算y坐标
        SetPixel(x, y, temp, data);
    }
}

//--------------------------------------------------------------
// 名称：void BlendTwoBMP(double blendRatio, BMP_Data *des, BMP_Data *src)
// 功能：按比例融合两副图像
// 参数：
//          [double blendRatio] --- 融合比例
//          [BMP_Data *des] --- 目标图像数据
//          [BMP_Data *src] --- 源图像数据
// 返回：无
// 作者：耿楠
// 日期：2017年11月14日
//--------------------------------------------------------------
void BlendTwoBMP(double blendRatio, BMP_Data *des, BMP_Data *src)
{
    int x, y;
    RGB desrgb, srcrgb;

    for(y = 0; y < des->height; y++)
    {
        for(x = 0; x < des->width; x++)
        {
            desrgb = GetPixel(x, y, des);
            srcrgb = GetPixel(x, y, src);

            desrgb.r = desrgb.r * blendRatio + srcrgb.r * (1 - blendRatio);
            desrgb.g = desrgb.g * blendRatio + srcrgb.g * (1 - blendRatio);
            desrgb.b = desrgb.b * blendRatio + srcrgb.b * (1 - blendRatio);

            SetPixel(x, y, desrgb, des);
        }
    }
}
