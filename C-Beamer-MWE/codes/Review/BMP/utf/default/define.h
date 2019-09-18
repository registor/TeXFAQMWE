#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

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
    int width,height;                /* 图像宽和高（pixels) */
    unsigned short int planes;       /* 颜色平面            */
    unsigned short int bits;         /* 颜色深度            */
    unsigned int compression;        /* 压缩类型            */
    unsigned int imagesize;          /* 图像数据大小(bytes) */
    int xresolution,yresolution;     /* 单位长度像素数      */
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

#endif // DEFINE_H_INCLUDED
