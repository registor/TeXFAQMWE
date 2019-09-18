/*-------------------------------------------------------
* Copyright (c) 2010,����ũ�ֿƼ���ѧ��ϢѧԺ�������ѧϵ
* All rights reserved.
*
* �ļ����ƣ�bmp.c
* �ļ���ʶ�������ù���ƻ���
* ժҪ��Load_BMP()��Save_BMP()��GetPixel()��SetPixel()
        ����ʵ�֡�
*
* ��ǰ�汾��1.0
* ���ߣ����
* ������ڣ�2010��12��30��
*
* ȡ���汾����
* ԭ���ߣ���
* ������ڣ���
-------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

//--------------------------------------------------------------
// ���ƣ�int Load_BMP(const char *file_name, BMP_Data *bmp_data)
// ���ܣ�����24λ���ɫͼ��
// ������[const char *file_name] --- BMPͼ���ļ���
//       [BMP_Data *bmp_data] --- ͼ������ָ��
// ���أ�int --- �ɹ�����1��ʧ�ܷ���0
// ���ߣ����
// ���ڣ�2010��12��30��
//--------------------------------------------------------------
int Load_BMP(const char *file_name, BMP_Data *bmp_data)
{
    FILEHEADER fHeader;
    INFOHEADER imgHeader;
    FILE *bmp_file;

    if( !(bmp_file = fopen(file_name, "rb")) )
        return 0;

    /* �����ļ�ͷ����*/
    fread( &fHeader, sizeof(FILEHEADER), 1, bmp_file);
    /* ����ͼ��ͷ����*/
    fread( &imgHeader, sizeof(INFOHEADER), 1, bmp_file);

    /* �ж��ǲ���24λBMPͼ��*/
    if( *((char *)&fHeader.type) != 'B' &&
        *(((char *)&fHeader.type) + 1) != 'M' &&
            imgHeader.bits != 24 )
    {
        fclose( bmp_file );
        return 0;
    }

    //ͼ���Ⱥ͸߶ȣ����أ�
    bmp_data->width = imgHeader.width;
    bmp_data->height = imgHeader.height;

    //ʵ��ÿ�д洢�ֽ���
    bmp_data->widthbytes = ((bmp_data->width * 3) % 4 == 0) ?
                           (bmp_data->width * 3) : ((bmp_data->width * 3) / 4 * 4 + 4);
    //λͼ���ݴ�С���ֽڣ�
    unsigned int size = bmp_data->widthbytes * imgHeader.height * 3;
    /* Ϊ�洢ͼ�����ݷ����ڴ�*/
    bmp_data->data = (unsigned char *)malloc( size );

    //�����ļ�ָ�뵽ͼ��������
    fseek( bmp_file, fHeader.offset, SEEK_SET);
    fread( bmp_data->data, size, 1, bmp_file);

    fclose( bmp_file );

    return 1;
}

//--------------------------------------------------------------
// ���ƣ�int Save_BMP(const char *file_name, BMP_Data *bmp_data)
// ���ܣ��洢24λ���ɫͼ��
// ������[const char *file_name] --- BMPͼ���ļ���
//       [BMP_Data *bmp_data] --- ͼ������ָ��
// ���أ�int --- �ɹ�����1��ʧ�ܷ���0
// ���ߣ����
// ���ڣ�2010��12��30��
//--------------------------------------------------------------
int Save_BMP(const char *file_name, const BMP_Data *bmp_data)
{
    FILEHEADER fHeader;
    INFOHEADER imgHeader;
    FILE *bmp_file;

    int imagsize = bmp_data->widthbytes * bmp_data->height;

    memset(&fHeader, 0, sizeof(FILEHEADER));
    memset(&imgHeader, 0, sizeof(INFOHEADER));

    //BMP�ļ���־
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
        return 0;

    fwrite( &fHeader, sizeof(fHeader), 1, bmp_file);
    fwrite( &imgHeader, sizeof(imgHeader), 1, bmp_file);
    fwrite( bmp_data->data, imagsize, 1, bmp_file);

    fclose(bmp_file);

    return 1;
}

//--------------------------------------------------------------
// ���ƣ�RGB GetPixel(int x, int y, BMP_Data *bmp_data)
// ���ܣ���ȡͼ������ֵ
// ������[int x] --- ����x����
//       [int y] --- ����y���꣨δ���ǵ���
//       [BMP_Data *bmp_data] --- ͼ������
// ���أ�RGB --- ����ֵ
// ���ߣ����
// ���ڣ�2010��12��30��
//--------------------------------------------------------------
RGB GetPixel(int x, int y, BMP_Data *bmp_data)
{
    RGB temprgb;
    unsigned char *p;

    // ͼ����������ָ��
    p = bmp_data->data;
    // ƫ������y��
    p += y * bmp_data->widthbytes;
    // ƫ������x��
    p += x * 3;

    // ������ֵ�������ֽڣ�
    memcpy(&temprgb, p, 3);

    return temprgb;
}

//--------------------------------------------------------------
// ���ƣ�void SetPixel(int x, int y, RGB rgb, BMP_Data *bmp_data)
// ���ܣ���ȡͼ������ֵ
// ������[int x] --- ����x����
//       [int y] --- ����y���꣨δ�ܿ��ǵ���
//       [RGB rgb] --- ����ֵ
//       [BMP_Data *bmp_data] --- ͼ������
// ���أ���
// ���ߣ����
// ���ڣ�2010��12��30��
//--------------------------------------------------------------
void SetPixel(int x, int y, RGB rgb, BMP_Data *bmp_data)
{
    unsigned char *p;

    // ͼ����������ָ��
    p = bmp_data->data;
    // ƫ������y��
    p += y * bmp_data->widthbytes;
    // ƫ������x��
    p += x * 3;

    // д����ֵ�������ֽڣ�
    memcpy(p, &rgb, 3);
}

