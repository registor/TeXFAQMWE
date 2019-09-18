/**
INI�ļ����������ļ�.ini
    ��ע����Ŀ�е������ļ���������Ŀ���õġ�
    ���׺��.ini�����磺�˿�����.ini��
��ʽ��
    INI�ļ��ɽڡ�����ֵ��ɡ�
�ڣ�
    [section]
����������=ֵ��
    name=value
ע�⣺
    ע��ʹ��#�ű�ʾ����#�ź�������֣�ֱ�����н�β��ȫ��Ϊע�⡣
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "define.h"
#include "configINI.h"

//--------------------------------------------------------------
// ���ƣ�void creat_inputFilePathName(char *strFilePathName,
//                                    const char *configfilename,
//                                    const char *key)
// ���ܣ�����һ������·����Ϣ�Ķ���ͼ���ļ�����
// ������[char *strFilePathName] --- �ļ�����ָ��
//       [char *configfilename] --- .ini�����ļ��ļ���
//       [const char *key] --- .ini�����ļ���ֵ
// ���أ���
// ���ߣ����
// ���ڣ�2013��12��13��
//--------------------------------------------------------------
void creat_inputFilePathName(char *strFilePathName, const char *configfilename, const char *key)
{
    char *pstrTemp;

    //����INI�����ļ�����Ӧ�����ݣ������������ļ����ƣ��������·����Ϣ��
    pstrTemp = getKeyValue(configfilename, "[img_path]", "in");
    strcpy(strFilePathName, pstrTemp);
    pstrTemp = getKeyValue(configfilename, "[img_name]", key);
    strcat(strFilePathName, pstrTemp);
    strcat(strFilePathName, ".bmp");
}

//--------------------------------------------------------------
// ���ƣ�void creat_outputFilePathName(char *strFilePathName,
//                                     const char *configfilename,
//                                     const char *extName)
// ���ܣ�����һ������·����Ϣ������ļ�����
// ������[char *strFilePathName] --- �ļ�����ָ��
//       [char *configfilename] --- .ini�����ļ��ļ���
//       [const char *extName] --- ��������׺
// ���أ���
// ���ߣ����
// ���ڣ�2013��12��13��
//--------------------------------------------------------------
void creat_outputFilePathName(char *strFilePathName, const char *configfilename, const char *extName)
{
    char *pstrTemp;

    //����INI�����ļ�����Ӧ�����ݣ�����������ļ����ƣ��������·����Ϣ��
    pstrTemp = getKeyValue(configfilename, "[img_path]", "out");
    strcpy(strFilePathName, pstrTemp);
    pstrTemp = getKeyValue(configfilename, "[img_name]", "in_1");
    strcat(strFilePathName, pstrTemp);
    strcat(strFilePathName, extName);
}


//--------------------------------------------------------------
// ���ƣ�char* getKeyValue(const char *filename, const char *section, const char *key)
// ���ܣ�����.ini�����ļ�ָ���ڡ�ָ�����ļ�ֵ
// ������[char *filename] --- .ini�����ļ��ļ���
//       [char *section] --- ������
//       [char *key] --- ������
// ���أ�char * --- ��ֵ�ַ�����ָ��
// ���ߣ����
// ���ڣ�2010��12��30��
//--------------------------------------------------------------
char* getKeyValue(const char *filename, const char *section, const char *key)
{
    char line[NAME_LEN + 1];
    char sectname[NAME_LEN + 1];

    char *skey, *valu;
    char seps[] = "=";
    bool flag = false;

    //�������ļ�
    FILE *fp = fopen(filename, "r");
    assert(fp != NULL);

    //�ַ�����0
    memset(line, 0, NAME_LEN + 1);

    //������������������δ��[��]ʱ��Ϊ�����[��]
    if (!strchr(section, '['))
    {
        strcpy(sectname,"[");
        strcat(sectname,section);
        strcat(sectname,"]");
    }
    else
    {
        strcpy(sectname,section);
    }

    while (fgets(line, NAME_LEN, fp) != NULL)
    {
        //���Ҳ�����ָ���ַ����ַ����е�1�γ���λ�õ�ָ�롣
        valu = strchr(line, '\n');
        //��'\n'�滻Ϊ'\0'
        *valu = 0;

        if (flag)
        {
            /**
            char *strtok(char s[], const char *delim);
            �ֽ��ַ���Ϊһ���ַ�����sΪҪ�ֽ���ַ�����delimΪ�ָ����ַ�����
            strtok()�������ַ����ָ��һ����Ƭ�Ρ�����sָ�����ָ�� �ַ�����
            ����delim��Ϊ�ָ��ַ����а����������ַ���
            ��strtok()�ڲ���s���ַ����з��ֲ���delim�а����ķָ��ַ�ʱ,
            ��Ὣ���ַ���Ϊ\0 �ַ���
            �ڵ�һ�ε���ʱ��strtok()����������s�ַ���������ĵ����򽫲���s���ó�NULL��
            ÿ�ε��óɹ��򷵻�ָ�򱻷ָ��Ƭ�ε�ָ�롣
            **/
            //�ָ��������
            skey = strtok(line, seps);
            if (strcmp(skey , key) == 0)
            {
                //���ؼ�ֵ�ַ���
                return strtok(NULL, seps);
            }
        }
        else
        {
            //�ҵ�ָ���Ľ�
            if (strcmp(sectname,line) == 0)
            {
                //�趨�����ֵ��־
                flag = true;  //find the section
            }

        }
    }

    return NULL;
}
