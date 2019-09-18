/*-------------------------------------------------------
* Copyright (c) 2010,����ũ�ֿƼ���ѧ��ϢѧԺ�������ѧϵ
* All rights reserved.
*
* �ļ����ƣ�bmp.h
* �ļ���ʶ�������ù���ƻ���
* ժҪ��ͼ���ļ�ͷFILEHEADER����ϢͷINFOHEADER������BMP_Data
        ����ɫRGB�ṹ��Ķ��壬����ԭ��������
*
* ��ǰ�汾��1.0
* ���ߣ����
* ������ڣ�2010��12��30��
*
* ȡ���汾����
* ԭ���ߣ���
* ������ڣ���
-------------------------------------------------*/

#ifndef READ_BMP_H_INCLUDED
#define READ_BMP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "define.h"

/* ����ͼ�� */
int Load_BMP(const char *file_name, BMP_Data *bmp_data);
/* ����ͼ�� */
int Save_BMP(const char *file_name, const BMP_Data *bmp_data);
/* ����ָ������ֵ */
RGB GetPixel(int x, int y, BMP_Data *bmp_data);
/* �趨ָ������ֵ */
void SetPixel(int x, int y, RGB rgb, BMP_Data *bmp_data);

#endif /* READ_BMP_H_INCLUDED*/
