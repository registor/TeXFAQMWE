#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#define NAME_LEN 255

//�趨�ṹ�����ֽ�Ϊ��λ
#pragma pack(1)

/*�ļ�ͷ*/
typedef struct
{
    unsigned short int type;      /* ��ʶ                     */
    unsigned int size;            /* �ļ���С��bytes��        */
    unsigned short int reserved1; /* ������                   */
    unsigned short int reserved2;
    unsigned int offset;          /* ͼ������ƫ�Ƶ�ַ��bytes��*/
} FILEHEADER;

/*ͼ����Ϣͷ*/
typedef struct
{
    unsigned int size;               /* ��Ϣͷ��С��bytes�� */
    int width,height;                /* ͼ���͸ߣ�pixels) */
    unsigned short int planes;       /* ��ɫƽ��            */
    unsigned short int bits;         /* ��ɫ���            */
    unsigned int compression;        /* ѹ������            */
    unsigned int imagesize;          /* ͼ�����ݴ�С(bytes) */
    int xresolution,yresolution;     /* ��λ����������      */
    unsigned int ncolours;           /* ��ɫ��              */
    unsigned int importantcolours;   /* ��Ҫ��ɫ��          */
} INFOHEADER;

/*ͼ��������Ϣ*/
typedef struct
{
    unsigned int width;       /* λͼ�Ŀ�ȣ�������Ϊ��λ */
    unsigned int height;      /* λͼ�ĸ߶ȣ�������Ϊ��λ */
    unsigned int widthbytes;  /* λͼ���ֽڿ��           */
    unsigned char *data;      /* ͼ������ָ��             */
} BMP_Data;

/*ͼ��������Ϣ*/
typedef struct
{
    unsigned char b; /* �� */
    unsigned char g; /* �� */
    unsigned char r; /* �� */
} RGB;

#endif // DEFINE_H_INCLUDED
