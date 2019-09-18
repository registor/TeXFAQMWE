/*--------------------------------------------------------------------------------
* Copyright (c) 2019,����ũ�ֿƼ���ѧ��ϢѧԺ�������ѧϵ
* All rights reserved.
*
* �ļ����ƣ�main.c
* �ļ���ʶ�������ù���ƻ���
* ժҪ����ȡ���ֵ����ֿ����ʾ���롣
*
* ��ǰ�汾��1.0
* ���ߣ����
* ������ڣ�2019��01��13��
*
* ȡ���汾����
* ԭ���ߣ�
* ������ڣ�
--------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// �궨��
#define ASCROW 16
#define ASCCOL 8

#define HZROW 16
#define HZCOL 16

// Ӣ���ַ����ݽṹ
typedef struct
{
    unsigned char ch;                                                               // Ӣ���ַ�
    unsigned char rawdata[ASCROW * ASCCOL / 8]; // ��ģ����
    char dispchar[ASCROW][ASCCOL + 1];               // ��ʾ�ַ��ַ�������
} ASCIICHAR;

// �����ַ����ݽṹ
typedef struct
{
    unsigned char ch[3];                                        // Ӣ���ַ�
    unsigned char rawdata[HZROW * HZCOL / 8]; // ��ģ����
    char dispchar[HZROW][HZCOL + 1];               // ��ʾ�ַ��ַ�������
} HZCHAR;

// ����ԭ��
// ��ȡ��ģ
int GetASCIICode(ASCIICHAR *, const char *, const char *); // ��ASC16Ӣ����ģ���ж�ȡһ��Ӣ���ַ�������
int GetHZKCode(HZCHAR *, const char *, const char *); // ��HZK16������ģ���ж�ȡһ�������ַ�������

// �ַ�������
int ASCProc(ASCIICHAR *, const char *, const char *, const char *); // ����Ӣ���ַ���
int HZProc(HZCHAR *, const char *, const char *, const char *); // ���������ַ���

// ������
void PrintASCII(const ASCIICHAR *, int); // ��ʾӢ���ַ����
void PrintHZK(const HZCHAR *, int); // ��ʾ�����ַ����

// ��������
int ReadLine(char *, int); // ���벻����ָ�����ȵ�һ���ַ���

// ����ԭ��
void run(void); // ���Ժ���

// ����
int main()
{
    run(); // ���������

    return 0;
}

// ��������

//-----------------------------------------------------------------------------------------------
// ����: void run(void)
// ����: �������ܲ��Ժ���
// �㷨: �������ô���NULL�ĺ���ָ���������������ָ������ͨ��ѭ������ÿ��������
//         �����º���������Ӧ���Ƽ������鼴�ɡ�
// ����:
//         [void] --- ��
// ����: [void]  --- ��
// ����: ���
// ����: 2019��01��13��
//-----------------------------------------------------------------------------------------------
void run(void)
{
    // ����Ӣ���ַ�
    char str[10] = "AbC!";
    int len = strlen(str);

    ASCIICHAR *pch1 = malloc(len * sizeof(ASCIICHAR)); // ����ռ�
    ASCProc(pch1, str, "ASC16", " #"); // ��ȡ��������ģ����
    PrintASCII(pch1, len); // ���
    free(pch1); // �ͷ��ڴ�

    // ���������ַ�
    char zh[10] = "���ѧ";
    len = strlen(zh);
    HZCHAR *pch2 = malloc(len * sizeof(HZCHAR)); // ����ռ�
    HZProc(pch2, zh, "HZK16", " *"); // ��ȡ��������ģ����
    PrintHZK(pch2, len / 2); // �����ע�⺺�ֳ���Ҫ��2
    free(pch2); // �ͷ��ڴ�
}

//-----------------------------------------------------------------------------------------------
// ����: int ReadLine(char *str, int n)
// ����: ����ָ�����ȵ��ַ���
// �㷨: ��������ַ���ֱ�������س�����EOF���ǳ��ȴ���ָ�����ȡ�
// ����:
//         [char *str] --- ����ַ���
//         [int n] --- ����������󳤶�
// ����: [int]  --- ���ض����ַ��ĸ���
// ����: ���
// ����: 2019��01��13��
//-----------------------------------------------------------------------------------------------
int ReadLine(char *str, int n)
{
    int ch, i = 0;

    // ����ǰ���ո�
    while(isspace(ch = getchar()))
    {
        ;
    }

    // ��������
    while(ch != '\n' && ch != EOF)
    {
        if(i < n)
        {
            str[i++] = ch;
        }
        ch = getchar(); // ������һ���ַ�
    }

    str[i] = '\0'; // �ַ�����ֹ�ַ�

    return i;
}

//-----------------------------------------------------------------------------------------------
// ����: int GetASCIICode(ASCIICHAR *pch, const char *filename, const char *otab)
// ����: ����ģ�ļ��ж���1��Ӣ���ַ�����ģ����
// �㷨: ��ָ���ļ��ж�ȡ��ģ�ṹ���ַ���Ա����ģ���ݣ����Զ�������ݷ�����
//         ����ģ��ʾ�ַ����ұ������ģ�ṹ���еĿ���ʾ�ַ���ά���顣
//         ���㷨����"λ��"��"��λ"����ʵ�֡�
// ����:
//         [ASCIICHAR *pch] --- �ַ����ݽṹ��ָ��
//         [const char *filename] --- ��ģ�ļ������ַ���
//         [const char *otab] --- ��ģ��ʾ�ַ����ұ�
// ����: [int]  --- �ɹ�����1�����򷵻�0
// ����: ���
// ����: 2019��01��13��
//-----------------------------------------------------------------------------------------------
int GetASCIICode(ASCIICHAR *pch, const char *filename, const char *otab)
{
    // ������Ч�Լ���
    if(pch == NULL || filename == NULL || otab == NULL)
    {
        return 0; // ������Ч�Լ���
    }

    FILE *fp;

    // ����ģ�ļ�
    fp = fopen(filename, "rb");
    if(fp == NULL)
    {
        printf("Can't open data file!");
        return 0;
    }

    // ������Ҫ��ȡ�ַ�����ģ����ƫ�Ƶ�ַ
    unsigned long pos = 0L;
    pos = (long)(pch->ch * (ASCROW * ASCCOL / 8) + 1);
    // �ļ���λ
    fseek(fp, pos, SEEK_SET);
    // ��������(ASCROW * ASCCOL / 8 ���ֽ�)
    fread(pch->rawdata, ASCROW * ASCCOL / 8, 1, fp);

    // ����ģ����ת��Ϊ��ʾ�ַ�
    int i, j, k;
    for(i = 0; i < ASCROW; i++)
    {
        for(j = 0; j < ASCCOL / 8; j++)
        {
            unsigned char curr; // ��ǰ״̬
            unsigned char mask = 0x80; // ����(1000 0000)
            for(k = 0; k < 8; k++)
            {
                // ע��j + i * (ASCCOL / 8)
                curr = pch->rawdata[j + i * (ASCCOL / 8)] & mask; // ָ��λ����ԭ״������λ��0
                if(curr) // ��λ��Ϊ0
                {
                    pch->dispchar[i][k + 8 * j] = otab[1]; // ��ʾ�ַ���ֵ(ǰ���ַ�)
                }
                else
                {
                    pch->dispchar[i][k + 8 * j] = otab[0]; // ��ʾ�ַ���ֵ(�����ַ�)
                }
                mask = mask >> 1; // ��������1λ
            }
        }
        pch->dispchar[i][k + 8 * (j - 1)] = '\0'; // �ַ�����ֹ�ַ�(ע��j-1)
    }

    // �ر���ģ�ļ�
    fclose(fp);

    return 1;
}

//-----------------------------------------------------------------------------------------------
// ����: int GetHZCode(HZCHAR *pch, const char *filename, const char *otab)
// ����: ����ģ�ļ��ж���1�������ַ�����ģ����
// �㷨: ��ָ���ļ��ж�ȡ��ģ�ṹ���ַ���Ա����ģ���ݣ����Զ�������ݷ�����
//         ����ģ��ʾ�ַ����ұ������ģ�ṹ���еĿ���ʾ�ַ���ά���顣
//         ���㷨����"λ��"��"��λ"����ʵ�֡�
// ����:
//         [HZCHAR *pch] --- �ַ����ݽṹ��ָ��
//         [const char *filename] --- ��ģ�ļ������ַ���
//         [const char *otab] --- ��ģ��ʾ�ַ����ұ�
// ����: [int]  --- �ɹ�����1�����򷵻�0
// ����: ���
// ����: 2019��01��13��
//-----------------------------------------------------------------------------------------------
int GetHZCode(HZCHAR *pch, const char *filename, const char *otab)
{
    // ������Ч�Լ���
    if(pch == NULL || filename == NULL || otab == NULL)
    {
        return 0; // ������Ч�Լ���
    }

    FILE *fp;

    // ����ģ�ļ�
    fp = fopen(filename, "rb");
    if(fp == NULL)
    {
        printf("Can't open data file!");
        return 0;
    }

    // ������Ҫ��ȡ�ַ�����ģ����ƫ�Ƶ�ַ
    unsigned long pos = 0L;

    // ���㺺����ģ����ƫ�Ƶ�ַ
    /*����=����(���ֽ�)-0xA0  λ��=����(���ֽ�)-0xA0*/
    unsigned int rownum = pch->ch[0] - 0xA0;
    unsigned int colnum = pch->ch[1] - 0xA0;
    pos = (94 * (rownum - 1) + (colnum - 1)) * 32L; /*����ú������ֿ���ƫ����*/
    // �ļ���λ
    fseek(fp, pos, SEEK_SET);
    // ��������(ASCROW * ASCCOL / 8 ���ֽ�)
    fread(pch->rawdata, HZROW * HZCOL / 8, 1, fp); //

    // ����ģ����ת��Ϊ��ʾ�ַ�
    int i, j, k;
    for(i = 0; i < HZROW; i++)
    {
        for(j = 0; j < HZCOL / 8; j++)
        {
            unsigned char curr; // ��ǰ״̬
            unsigned char mask = 0x80; // ����(1000 0000)
            for(k = 0; k < 8; k++)
            {
                // ע��j + i * (HZCOL / 8)
                curr = pch->rawdata[j + i * (HZCOL / 8)] & mask; // ָ��λ����ԭ״������λ��0
                if(curr) // ��λ��Ϊ0
                {
                    pch->dispchar[i][k + 8 * j] = otab[1]; // ��ʾ�ַ���ֵ(ǰ���ַ�)
                }
                else
                {
                    pch->dispchar[i][k + 8 * j] = otab[0]; // ��ʾ�ַ���ֵ(�����ַ�)
                }
                mask = mask >> 1; // ��������1λ
            }
        }
        pch->dispchar[i][k + 8 * (j - 1)] = '\0'; // �ַ�����ֹ�ַ�(ע��j-1)
    }

    // �ر���ģ�ļ�
    fclose(fp);

    return 1;
}

//-----------------------------------------------------------------------------------------------
// ����: int ASCProc(ASCIICHAR *pch, const char *str, const char *filename, const char *otab)
// ����: ����¼������ַ���
// �㷨: ���ַ���������ַ�������ȡ���ٵ��ö�ȡ��ģ���ݺ�����
//          ���㷨����"λ��"����ʵ��
// ����:
//       [ASCIICHAR *pch] --- �ַ����ݽṹ��ָ��
//       [char *str] --- Ҫ������ַ���
//       [const char *filename] --- ��ģ�ļ��ļ�����
//       [const char *otab] --- ��ģ��ʾ���ұ�
// ����: [int]  --- �ɹ�����1�����򷵻�0
// ����: ���
// ����: 2019��01��13��
//-----------------------------------------------------------------------------------------------
int ASCProc(ASCIICHAR *pch, const char *str,  const char *filename, const char *otab)
{
    // ������Ч�Լ���
    if(str == NULL || pch == NULL || filename == NULL)
    {
        return 0;
    }

    // ����ÿһ���ַ�
    while(*str != '\0')
    {
        pch->ch = *str;
        GetASCIICode(pch, filename, otab);
        pch++;
        str++;
    }

    return 1;
}

//-----------------------------------------------------------------------------------------------
// ����: int HZProc(HZCHAR *pch, const char *str, const char *filename, const char *otab)
// ����: ����¼������ַ���
// �㷨: ���ַ���������ַ�������ȡ���ٵ��ö�ȡ��ģ���ݺ�����
//          ���㷨����"λ��"����ʵ��
// ����:
//       [HZCHAR *pch] --- �ַ����ݽṹ��ָ��
//       [char *str] --- Ҫ������ַ���
//       [const char *filename] --- ��ģ�ļ��ļ�����
//       [const char *otab] --- ��ģ��ʾ���ұ�
// ����: [int]  --- �ɹ�����1�����򷵻�0
// ����: ���
// ����: 2019��01��13��
//-----------------------------------------------------------------------------------------------
int HZProc(HZCHAR *pch, const char *str,  const char *filename, const char *otab)
{
    // ������Ч�Լ���
    if(str == NULL || pch == NULL || filename == NULL)
    {
        return 0;
    }

    // ����ÿһ���ַ�
    while(*str != '\0')
    {
        pch->ch[0] = str[0];
        pch->ch[1] = str[1];
        pch->ch[2] = '\0';
        GetHZCode(pch, filename, otab);
        pch++;
        str += 2;
    }

    return 1;
}


//-----------------------------------------------------------------------------------------------
// ����: void PrintASCII(const ASCIICHAR *pch, int n)
// ����: �ÿ���ʾ�ַ���ʾ��ģ�ṹ�������е��ַ�
// �㷨: ����ģ�ṹ�������е������ַ���ÿ�п���ʾ�ַ���ƴװ��һ�������ַ����������
// ����:
//         [const ASCIICHAR *pch] --- �ַ����ݽṹ������ָ��
//         [int n] --- �ַ�����
// ����: [void]  --- ��
// ����: ���
// ����: 2019��01��13��
//-----------------------------------------------------------------------------------------------
void PrintASCII(const ASCIICHAR *pch, int n)
{
    // ������Ч�Լ���
    if(pch == NULL)
    {
        return;
    }

    char **pstr = NULL;

    // �����ַ���ָ������
    pstr = malloc(ASCROW * sizeof(char *));
    if(pstr == NULL)
    {
        printf("Not enough memory!");
        return;
    }
    // ����ÿ������������
    for(int i = 0; i < ASCROW; i++)
    {
        pstr[i] = malloc((n * ASCCOL + 1) * sizeof(char));
        if(pstr[i] == NULL)
        {
            printf("Not enough memory!");
            return;
        }
        memset(pstr[i], 0, (n * ASCCOL + 1) * sizeof(char)); // ��ʼ��
    }

    // ��ÿ���ַ�����ʾ�ַ���ƴ��һ���ַ���
    for(int i = 0; i < ASCROW; i++)
    {
        for(int j = 0; j < n; j++)
        {
            strcat(pstr[i], pch[j].dispchar[i]); // ƴװ
        }
    }

    // ���ƴ�ɵ��ַ���
    for(int i = 0; i < ASCROW; i++)
    {
        puts(pstr[i]);
    }

    // �ͷ��ڴ�
    for(int i = 0; i < ASCROW; i++)
    {
        free(pstr[i]);
    }
    free(pstr);
}

//-----------------------------------------------------------------------------------------------
// ����: void PrintHZK(const HZCHAR *pch, int n)
// ����: �ÿ���ʾ�ַ���ʾ��ģ�ṹ�������е��ַ�
// �㷨: ����ģ�ṹ�������е������ַ���ÿ�п���ʾ�ַ���ƴװ��һ�������ַ����������
// ����:
//         [const HZCHAR *pch] --- �ַ����ݽṹ������ָ��
//         [int n] --- �ַ�����
// ����: [void]  --- ��
// ����: ���
// ����: 2019��01��13��
//-----------------------------------------------------------------------------------------------
void PrintHZK(const HZCHAR *pch, int n)
{
    // ������Ч�Լ���
    if(pch == NULL)
    {
        return;
    }

    char **pstr = NULL;

    // �����ַ���ָ������
    pstr = malloc(HZROW * sizeof(char *));
    if(pstr == NULL)
    {
        printf("Not enough memory!");
        return;
    }
    // ����ÿ������������
    for(int i = 0; i < HZROW; i++)
    {
        pstr[i] = malloc((n * HZCOL + 1) * sizeof(char));
        if(pstr[i] == NULL)
        {
            printf("Not enough memory!");
            return;
        }
        memset(pstr[i], 0, (n * HZCOL + 1) * sizeof(char)); // ��ʼ��
    }

    // ��ÿ���ַ�����ʾ�ַ���ƴ��һ���ַ���
    for(int i = 0; i < HZROW; i++)
    {
        for(int j = 0; j < n; j++)
        {
            strcat(pstr[i], pch[j].dispchar[i]); // ƴװ
        }
    }

    // ���ƴ�ɵ��ַ���
    for(int i = 0; i < HZROW; i++)
    {
        puts(pstr[i]);
    }

    // �ͷ��ڴ�
    for(int i = 0; i < HZROW; i++)
    {
        free(pstr[i]);
    }
    free(pstr);
}
