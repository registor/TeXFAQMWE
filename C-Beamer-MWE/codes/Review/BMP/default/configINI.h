/**-------------------------------------------------------
* Copyright (c) 2010,����ũ�ֿƼ���ѧ��ϢѧԺ�������ѧϵ
* All rights reserved.
*
* �ļ����ƣ�configINI.h
* �ļ���ʶ�������ù���ƻ���
* ժҪ������.INI�����ļ���ָ���ڡ�ָ�����ļ�ֵ��getKeyValue�ĺ���ԭ��������
*
* ��ǰ�汾��1.0
* ���ߣ����
* ������ڣ�2013��12��13��
*
* ȡ���汾����
* ԭ���ߣ���
* ������ڣ���
-------------------------------------------------**/
#ifndef CONFIGINI_H_INCLUDED
#define CONFIGINI_H_INCLUDED

void creat_outputFilePathName(char *strFilePathName, const char *configfilename, const char *extName);

void creat_inputFilePathName(char *strFilePathName, const char *configfilename, const char *key);

char* getKeyValue(const char *filename, const char *section, const char *key);

#endif // CONFIGINI_H_INCLUDED
