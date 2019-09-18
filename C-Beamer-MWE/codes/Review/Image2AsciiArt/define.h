#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

/* 文件名称最大长度 */
#define NAME_LEN 255

/* 设定结构体以单字节对齐(确保读入正确的字节数) */
#pragma pack(1)

/* 文件头结构体定义 */
typedef struct
{
    unsigned short int type;           /* 标识                                  */
    unsigned int size;                      /* 文件大小(bytes)               */
    unsigned short int reserved1;  /* 保留字                              */
    unsigned short int reserved2;
    unsigned int offset;                   /* 图像数据偏移地址(bytes) */
} FILEHEADER;

/* 图像信息头结构体定义 */
typedef struct
{
    unsigned int size;                        /* 信息头大小(bytes)     */
    int width, height;                         /* 图像宽和高(pixels)    */
    unsigned short int planes;          /* 颜色平面                    */
    unsigned short int bits;               /* 颜色深度                    */
    unsigned int compression;          /* 压缩类型                   */
    unsigned int imagesize;              /* 图像数据大小(bytes) */
    int xresolution, yresolution;        /* 单位长度像素数         */
    unsigned int ncolours;                 /* 颜色数                       */
    unsigned int importantcolours;  /* 重要颜色数                */
} INFOHEADER;

/* 图像数据信息结构体定义 */
typedef struct
{
    unsigned int width;           /* 位图的宽度，以像素为单位 */
    unsigned int height;         /* 位图的高度，以像素为单位 */
    unsigned int widthbytes;  /* 位图的字节宽度                  */
    unsigned char *data;         /* 图像数据指针                     */
} BMP_Data;

/* 图像数据信息结构体定义 */
typedef struct
{
    unsigned char b; /* 蓝 */
    unsigned char g; /* 绿 */
    unsigned char r;  /* 红 */
} RGB;

/* 函数类型定义 */
typedef double (*GETBLOCKFOO)(unsigned char *, int, int);

/* 转换符号表 */
static const unsigned char ascii_char_table1[] =
{
    ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
    '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
    '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'
};

static const unsigned char ascii_char_table2[] =
{
    '#', '@', '&', '$', '%', '|', '!', ';', ':', '\'', '`', '.', ' '
};

#endif // DEFINE_H_INCLUDED
