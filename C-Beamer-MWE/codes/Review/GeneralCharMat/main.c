/*--------------------------------------------------------------------------------
* Copyright (c) 2019,����ũ�ֿƼ���ѧ��ϢѧԺ�������ѧϵ
* All rights reserved.
*
* �ļ����ƣ�main.c
* �ļ���ʶ�������ù���ƻ���
* ժҪ����ȡ�����ֿ����ʾ���롣
*
* ��ǰ�汾��1.0
* ���ߣ����
* ������ڣ�2019��01��14��
*
* ȡ���汾����
* ԭ���ߣ�
* ������ڣ�
--------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

// �궨��
#define HZROW 16
#define HZCOL 16

// �����ַ����ݽṹ
typedef struct
{
    unsigned char ch[3];              // �ַ��ַ���(������3���ֽ�ͳһ��ʾ)
    unsigned short row;               // ��������
    unsigned short col;                // ��������
    unsigned short bytes;            // ÿ��ռ�е��ֽ���
    unsigned int tranflag;            // ��ģ�Ƿ���Ҫת��
    unsigned long offset;             // �ֿ��ļ���ַƫ����
    char filename[20];                   // �ֿ��ļ�����
    unsigned char *rawdata;         // ��ģ����
    unsigned char fgch;                // ǰ������ʾ�ַ�
    unsigned char bgch;               // ��������ʾ�ַ�
    unsigned char *disdata;          // ��ʾ�ַ��ַ�������
} CHARTYPE;

// ����ԭ��
int GetMatCode(CHARTYPE *); // ����ģ���ļ��ж�ȡ������һ���ַ�����
int SetCharInfo(CHARTYPE *, const unsigned char *, unsigned short, unsigned short,
                const char *, unsigned char, unsigned char); // �����ַ�����
int ProcString(CHARTYPE **, const unsigned char *, const char *, const char *,
               unsigned char, unsigned char); // �����ַ���
void PrintChars(const CHARTYPE *, int); // ��ʾ���

// ��������
int ReadLine(char *, int); // ���벻����ָ�����ȵ�һ���ַ���

// ����ԭ��
void run(void); // ���Ժ���

// ����
int main()
{
    // ���������
    srand((unsigned)time( NULL ));
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
// ����: 2019��01��14��
//-----------------------------------------------------------------------------------------------
void run(void)
{
    // ����Ӣ���ַ�
    unsigned char str[80] = "СϢLove C/C++��";
    int cnts = 0;

    CHARTYPE *ps;

    cnts = ProcString(&ps, str, "fonts/ASC12", "fonts/HZK16", '*', ' '); // �����ַ���
    PrintChars(ps, cnts); // ��ʾ���

    for(int i = 0; i < cnts; i++)
    {
        free(ps[i].rawdata);
        free(ps[i].disdata);
    }

    free(ps);
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
// ����: 2019��01��14��
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
// ����: int Transpose(unsigned char *pmat, unsigned short n)
// ����: ��ά�����ת��
// ����:
//         [unsigned char *pmat] --- ����ָ��
//         [unsigned short n] --- ������
// ����: [int]  --- �ɹ�����1�����򷵻�0
// ����: ���
// ����: 2019��01��14��
// ��ע: ����һ����������
//-----------------------------------------------------------------------------------------------
int Transpose(unsigned char *pmat, unsigned short n)
{
    // ������Ч�Լ���
    if(pmat == NULL)
    {
        return 0;
    }
    unsigned char ch;
    int i = 0, j = 0;

    for(i = 0; i < n; i++)
    {
        for (j = i; j < n; j++)
        {
            ch = pmat[j + i * n];
            pmat[j + i * n] = pmat[i + j * n];
            pmat[i + j * n] = ch;
        }
    }

    return 1;
}

//-----------------------------------------------------------------------------------------------
// ����: int GetMatCode(CHARTYPE *pch)
// ����: ����ģ�ļ��ж���1���ַ�����ģ����
// �㷨: ��ָ���ļ��ж�ȡ��ģ�ṹ���ַ���Ա����ģ���ݣ����Զ�������ݷ�����
//         ����ģ��ʾ�ַ����ұ������ģ�ṹ���еĿ���ʾ�ַ���ά���顣
//         ���㷨����"λ��"��"��λ"����ʵ�֡�
// ����:
//         [ASCIICHAR *pch] --- 1���ַ����ݽṹ��ָ��
// ����: [int]  --- �ɹ�����1�����򷵻�0
// ����: ���
// ����: 2019��01��14��
//-----------------------------------------------------------------------------------------------
int GetMatCode(CHARTYPE *pch)
{
    // ������Ч�Լ���
    if(pch == NULL)
    {
        return 0;
    }

    FILE *fp;

    // ����ģ�ļ�
    fp = fopen(pch->filename, "rb");
    if(fp == NULL)
    {
        printf("Can't open mat data file!\n");
        return 0;
    }

    // Ϊ��ģ�����������ڴ�
    size_t rawsize = pch->row * pch->bytes;
    size_t dissize = pch->row * pch->col;

    pch->rawdata = malloc(rawsize * sizeof(char));
    if(pch->rawdata == NULL)
    {
        printf("Not enough memory!\n");
        return 0;
    }
    pch->disdata = malloc(dissize * sizeof(char));
    if(pch->disdata == NULL)
    {
        printf("Not enough memory!\n");
        return 0;
    }

    // �ļ���λ
    fseek(fp, pch->offset, SEEK_SET);
    // ����1���ַ�����ģ����
    fread(pch->rawdata, rawsize, 1, fp);

    // ����ģ����ת��Ϊ����ʾ�ַ�
    int i, j, k;
    for(i = 0; i < pch->row; i++)
    {
        for(j = 0; j < pch->bytes; j++)
        {
            unsigned char flag; // �жϽ��
            unsigned char mask = 0x80; // ����(1000 0000)
            unsigned short cnt = 8; // λ��

            // ���һ���ֽ���Ҫ�����λ��
            if(((j + 1) * 8) > pch->col)
            {
                cnt = pch->col % 8;
            }

            // ����ģת��Ϊ����ʾ�ַ�
            for(k = 0; k < cnt; k++)
            {
                // ע��j + i * (ASCCOL / 8)
                flag = pch->rawdata[j + i * pch->bytes] & mask; // ָ��λ����ԭ״������λ��0
                if(flag) // ��λ��Ϊ0
                {
                    pch->disdata[k + 8 * j + i * pch->col] = pch->fgch; // ǰ���ַ�
                }
                else
                {
                    pch->disdata[k + 8 * j + i * pch->col] = pch->bgch; // �����ַ�
                }
                mask = mask >> 1; // ��������1λ
            }
        }
    }

    // ��ӡ������������Ҫ����ת�ò���
    if(pch->tranflag)
    {
        Transpose(pch->disdata, pch->row);
    }

    // �ر���ģ�ļ�
    fclose(fp);

    return 1; // ����������1
}

//-----------------------------------------------------------------------------------------------
// ����: int SetCharInfo(CHARTYPE *pch, const unsigned char *str,
//                            unsigned short row, unsigned short col,
//                            const char *filename,
//                            unsigned char fg, unsigned char bg)
// ����: ����һ���ַ��Ļ�����Ϣ
// ����:
//         [CHARTYPE *pch] --- 1���ַ����ݽṹ��ָ��
//         [unsigned char *str] --- �ַ���������2���ֽڵ��ַ���ͳһ����
//         [unsigned short row] --- ��ģ����
//         [unsigned short col] --- ��ģ����
//         [const char *filename] --- ��ģ�ļ��ļ�����
//         [unsigned char fg] --- ��ģ����ʾǰ���ַ�
//         [unsigned char bg] --- ��ģ����ʾ�����ַ�
// ����: [int]  --- �ɹ�����1�����򷵻�0
// ����: ���
// ����: 2019��01��14��
//-----------------------------------------------------------------------------------------------
int SetCharInfo(CHARTYPE *pch, const unsigned char *str,
                unsigned short row, unsigned short col,
                const char *filename,
                unsigned char fg, unsigned char bg)
{
    // ������Ч�Լ���
    if(pch == NULL || str == NULL || filename == NULL)
    {
        return 0;
    }

    memset(pch->ch, 0, 3);

    memcpy(pch->ch, str, 3);
    pch->row = row;
    pch->col = col;

    // ÿ���ֽ���
    if(pch->col % 8 == 0)
    {
        pch->bytes = pch->col / 8;
    }
    else
    {
        pch->bytes = pch->col / 8 + 1;
    }

    // ������ģ����ƫ�Ƶ�ַ
    if(pch->ch[1] == 0 && pch->ch[2] == 0)
    {
        // ��ȡ�����ļ���
        char *pstr = malloc((strlen(filename) + 1) * sizeof(char));
        if(pstr == NULL)
        {
            printf("Not enoght memory!\n");
            return 0;
        }
        strcpy(pstr, filename);

        char *ptok = strtok(pstr, "/");
        char *qtok = NULL;
        qtok = ptok;
        while(ptok != NULL)
        {
            qtok = ptok;
            ptok = strtok(NULL, "/");
        }

        // Ӣ����ģ�ļ�
        if(strcmp(qtok, "ASC16") == 0)
        {
            // UCDOS��ģ�ļ�
            pch->offset = (unsigned long)(pch->ch[0] * (pch->row * pch->bytes) + 1);
        }
        else
        {
            // ������ģ�ļ�
            pch->offset = (unsigned long)((pch->ch[0] - 0x20) * (pch->row * pch->bytes));
        }

        free(pstr);
    }
    else
    {
        // ������ģ�ļ�

        // ��ȡ�����ļ���
        char *pstr = malloc((strlen(filename) + 1) * sizeof(char));
        if(pstr == NULL)
        {
            printf("Not enoght memory!\n");
            return 0;
        }
        strcpy(pstr, filename);

        char *ptok = strtok(pstr, "/");
        char *qtok = NULL;
        qtok = ptok;
        while(ptok != NULL)
        {
            qtok = ptok;
            ptok = strtok(NULL, "/");
        }

        char *p[] = {"HZK24F", "HZK24H", "HZK24K", "HZK24S", "HZK40S", "HZK48S"};
        int flag = 0;
        for(int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
        {
            if(strcmp(qtok, p[i]) == 0)
            {
                flag = 1;
                break;
            }
        }

        /*����=����(���ֽ�)-0xA0  λ��=����(���ֽ�)-0xA0*/
        unsigned int rown = pch->ch[0] - 0xA0;
        unsigned int coln = pch->ch[1] - 0xA0;

        /*����ú������ֿ���ƫ����*/
        if(flag)
        {
            pch->offset = (unsigned long)((94 * (rown - 16) + (coln - 1)) * pch->row * pch->bytes);
            pch->tranflag = 1; // ��Ҫת��
        }
        else
        {
            pch->offset = (unsigned long)((94 * (rown - 1) + (coln - 1)) * pch->row * pch->bytes);
            pch->tranflag = 0; // ����ת��
        }
        free(pstr);
    }

    strcpy(pch->filename, filename);
    pch->fgch = fg;
    pch->bgch = bg;

    return 1; // �ɹ�����1
}


//-----------------------------------------------------------------------------------------------
// ����: int SkipNonDigit(const char *str)
// ����: ������0-9 ���ַ�
// �㷨: ����"%*[^0-9]"��ʽ��������0-9 ���ַ���
//         ����"%n"����������ַ���
// ����:
//       [const char *str] --- �ַ���ָ��
// ����: [int]  --- �ַ����е�1�������ַ���λ��
// ����: ���
// ����: 2018��12��19��
// ��ע: ����һ�������������ڶ�ȡ��ģ�ļ����е�����
//-----------------------------------------------------------------------------------------------
int SkipNonDigit(const char *str)
{
    int pos = 0;

    //���������0-9���ַ��������������ַ�������n
    sscanf(str, "%*[^0-9]%n", &pos);

    if(str[pos - 1] == '-')
    {
        return pos - 1; // ǰһ���ַ���'-'��
    }
    else
    {
        return pos;
    }
}

//-----------------------------------------------------------------------------------------------
//int ProcString(CHARTYPE **pc, const unsigned char *str,
//               const char *enname, const char *zhname,
//               unsigned char fgc, unsigned char bgc)
// ����: �����ַ�������������ģ�ṹ�嶯̬����
// ����:
//         [CHARTYPE **pc]  --- �ַ��ṹָ���ָ��
//         [const char *str] --- �ַ���ָ��
//         [const char *enname] --- Ӣ����ģ�ļ���ָ��
//         [const char *zhname] --- Ӣ����ģ�ļ���ָ��
//         [unsigned char fgc] --- ǰ������ʾ�ַ�
//         [unsigned char bgc] --- ��������ʾ�ַ�
// ����: [int]  --- �ַ�����
// ����: ���
// ����: 2019��01��14��
//-----------------------------------------------------------------------------------------------
int ProcString(CHARTYPE **pc, const unsigned char *str,
               const char *enname, const char *zhname,
               unsigned char fgc, unsigned char bgc)
{
    // ������Ч�Լ���
    if(str == NULL || enname == NULL || zhname == NULL)
    {
        return 0;
    }

    int cnt = 0;

    const unsigned char *ptemp  = str;

    // ͳ���ַ�����(������Ӣ���ַ�)
    while(*ptemp != '\0')
    {
        cnt++;
        if((*ptemp) < 128)
        {
            ptemp++;
        }
        else
        {
            ptemp += 2;
        }
    }

    // ����ռ�
    CHARTYPE *pch = (CHARTYPE *)malloc(cnt * sizeof(CHARTYPE));
    if(pch == NULL)
    {
        printf("Not enough memory!\n");
        return 0;
    }

    // ��ʼ������Ҫ��ʹ����ָ��ΪNULL
    memset(pch, 0, cnt * sizeof(CHARTYPE));

    unsigned char ch[3] = {0};
    int pos = 0;
    const char *p;
    int rows = 0;

    // ǰ���ַ���
    char fgch[] = "@#*oO.$?0\xF9";
    int fglen = strlen(fgch);

    cnt = 0;
    // ��������ַ�(������Ӣ���ַ�)
    while(*str != '\0')
    {
        // ǰ���ַ�(�������)
        int idx = rand() % fglen; // x=rand()%(Y-X+1)+X
        fgc = fgch[idx];
        if(*str < 128)
        {
            // Ӣ���ַ�
            memset(ch, 0, 3);
            ch[0] = *str;

            // ��ȡ��ģ�ļ����е�����
            p = enname;
            // ������0-9���ַ�
            pos = SkipNonDigit(p);
            // ������ʼλ��
            p += pos;
            sscanf(p, "%d", &rows);
            if(rows == 10)
            {
                SetCharInfo(&pch[cnt], ch, 10, 8, enname, fgc, bgc);
            }
            else if(rows == 12)
            {
                SetCharInfo(&pch[cnt], ch, 12, 8, enname, fgc, bgc);
            }
            else if(rows == 16)
            {
                SetCharInfo(&pch[cnt], ch, 16, 8, enname, fgc, bgc);
            }
            else
            {
                SetCharInfo(&pch[cnt], ch, 48, 24, enname, fgc, bgc);
            }

            GetMatCode(&pch[cnt]);

            // ��һ���ַ�
            str++;
        }
        else
        {
            // �����ַ�
            memset(ch, 0, 3);
            ch[0] = *str;
            ch[1] = *(str + 1);

            // ��ȡ��ģ�ļ����е�����
            p = zhname;
            // ������0-9���ַ�
            pos = SkipNonDigit(p);
            // ������ʼλ��
            p += pos;
            sscanf(p, "%d", &rows);

            SetCharInfo(&pch[cnt], ch, rows, rows, zhname, fgc, bgc);

            GetMatCode(&pch[cnt]);

            // ��һ���ַ�
            str += 2;
        }
        cnt++;
    }

    // Ϊ�βθ�ֵ
    *pc = pch;

    // �����ַ�����
    return cnt;
}

//-----------------------------------------------------------------------------------------------
// ����: void PrintChars(const CHARTYPE *pch, int n)
// ����: �ÿ���ʾ�ַ���ʾ��ģ�ṹ�������е��ַ�
// �㷨: ����ģ�ṹ�������е������ַ���ÿ�п���ʾ�ַ���ƴװ��һ�������ַ����������
// ����:
//         [const CHARTYPE *pch] --- �ַ����ݽṹ������ָ��
//         [int n] --- �ַ�����
// ����: [void]  --- ��
// ����: ���
// ����: 2019��01��14��
//-----------------------------------------------------------------------------------------------
void PrintChars(const CHARTYPE *pch, int n)
{
    // ������Ч�Լ���
    if(pch == NULL)
    {
        return;
    }

    // ���������ַ����ܿ��
    size_t rowsize = 0;
    size_t rowmax = 0;
    for(int i = 0; i < n; i++)
    {
        if(pch[i].rawdata != NULL)
        {
            rowsize += pch[i].col;
            if(pch[i].row > rowmax)
            {
                rowmax = pch[i].row;
            }
        }
    }

    // ����ռ�
    char **pstr = NULL;
    // �����ַ���ָ������
    pstr = malloc(rowmax * sizeof(char *));
    if(pstr == NULL)
    {
        printf("Not enough memory!\n");
        return;
    }
    memset(pstr, 0, rowmax * sizeof(char *)); // ��ʼ������Ҫ����ָ��ΪNULL
    // ����ÿ�е��ַ�������
    for(int i = 0; i < rowmax; i++)
    {
        pstr[i] = malloc((rowsize + 1) * sizeof(char));
        if(pstr[i] == NULL)
        {
            printf("Not enough memory!\n");
            return;
        }
        memset(pstr[i], 0, (rowsize + 1) * sizeof(char)); // ��ʼ������ҪĿ������'\0'��ֹ�ַ�
    }

    char *s;

    // ��ÿ���ַ�����ʾ�ַ���ƴ��һ���ַ���
    for(int i = 0; i < rowmax; i++)
    {
        s = pstr[i];
        for(int j = 0; j < n; j++)
        {
            if(pch[j].rawdata != NULL)
            {
                if(i < (rowmax - pch[j].row))
                {
                    memset(s, pch[j].bgch, pch[j].col);
                    s += pch[j].col;
                }
                else
                {
                    unsigned int pos = (i - (rowmax - pch[j].row)) * pch[j].col;
                    memcpy(s, pch[j].disdata + pos, pch[j].col);
                    s += pch[j].col;
                }
            }
        }
    }

    // ���ƴ�ɵ��ַ���
    for(int i = 0; i < rowmax; i++)
    {
        puts(pstr[i]);
    }

    // �ͷ��ڴ�
    for(int i = 0; i < rowmax; i++)
    {
        free(pstr[i]);
    }
    free(pstr);
}
