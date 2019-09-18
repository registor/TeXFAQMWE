/*--------------------------------------------------------------------------------
* Copyright (c) 2017,����ũ�ֿƼ���ѧ��ϢѧԺ�������ѧϵ
* All rights reserved.
*
* �ļ����ƣ�main.c
* �ļ���ʶ�������ù���ƻ���
* ժҪ����ʾ��ά�����һά��ʽ������ָ�뷽ʽ�������βεĲ�����
*           ����һ������(��ά����)�İ���Ϊ����һ������İ�����ָ��
*           ����λ���ϵ�Ԫ���ڸ���������ڸ�������С��
* ����˼�룺
*            ����ɨ�������ȡ����ǰi����Ϊһ��һά���飬�ҵ���
*            ���ֵλ��nMaxColPos������ȡ��nMaxColPos�е�����
*            ��Ϊһ��һά���飬�ҵ�����Сֵλ��nMinRowPos����
*            nMinRowPos�ȵ�ǰ��i������һ�����㡣
*            ���⣬һ����������ж������
*            ��������ʾ����һ��ָ��(һά��ʽ���ʶ�ά����)��������ָ��
*            ���ֺ����β�ģʽ����ʹ����C99�ı䳤������Ϊ�����βΡ�
* ��ǰ�汾��2.0
* ���ߣ����
* ������ڣ�2017��11��22��
*
* ȡ���汾��1.0
* ԭ���ߣ����
* ������ڣ�2010��12��16��
------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����ԭ��
void Input1D(int *, int, int); // ��������(1ά��ʽ)
void Output1D(int *, int, int); // �������(1ά��ʽ)
void Input2D(int m, int n, int (*)[n] ); // ��������(����ָ�룬2ά��ʽ)
void Output2D(int m, int n, int (*)[n]); // �������(����ָ�룬2ά��ʽ)

int GetMaxPos(int *, int); // ��ȡһ���������������λ��
int GetMinPos(int *, int); // ��ȡһ����������С����λ��

void GetOneRow1D(int *, int *, int, int); // ��ȡ��ά�����һ������(1ά��ʽ)
void GetOneRow2D(int n, int (*)[n], int *, int); // ��ȡ��ά�����һ������(����ָ�룬2ά��ʽ)

void GetOneCol1D(int *, int *, int, int, int); // ��ȡ��ά�����һ������(1ά��ʽ)
void GetOneCol2D(int m, int n, int (*)[n], int *, int); // ��ȡ��ά�����һ������(����ָ�룬2ά��ʽ)
int GetSaddlePoint1D(int *, int, int, int *, int *); // ��һ����ά�����еİ���
int GetSaddlePoint2D(int m, int n, int (*a)[n], int *, int *); // ��һ����ά�����еİ���(����ָ�룬2ά��ʽ)

void test1D(void); // ������1ά��ʽ����2ά������Ұ���
void test2D(void); // ���Բ��ñ䳤���飬������ָ�����2ά������Ұ���

int main(void)
{
    test1D();
    test2D();

    return 0;
}

// ���Ժ���
void test1D(void)
{
    /*
        ����1��1   2   3   4   5
                 2   4   6   8   10
                 3   6   9   12  15
                 4   8   12   16  20
        ����2��1   12    3    4    5
               2    4    16   8    10
               3    6    9    12    15
               4    8    12    16    20
         */
//
    // ��������
    int a[][3] =
    {
        {1, 6, 8}, {2, 4, 7}, {3, 5, 9}
    };

    int i, m = 0, n = 0;
    int nCount = 0;

    // ���������������
    m = sizeof(a) / sizeof(a[0]);
    n = sizeof(a[0]) / sizeof(a[0][0]);

    // �������ڴ洢���С���λ�õĶ�̬����ָ��
    int *pRow = NULL, *pCol = NULL;

    // ��̬����Ĵ�С(�ٶ���m * n������)
    int nSize = m * n * sizeof(int);

    if ((pRow = (int *)malloc(nSize)) == NULL)
    {
        exit(1); // �ڴ����ʧ��
    }

    memset(pRow, 0, nSize); // ��0

    if ((pCol = (int *)malloc(nSize)) == NULL)
    {
        free(pRow); // �ͷ��ڴ�
        exit(1); // �ڴ����ʧ��
    }

    memset(pCol, 0, nSize); // ��0

    printf("the 2D array is: \n");
    Output1D((int *)a, m, n); // ���ԭʼ����

    nCount = GetSaddlePoint1D((int*)a, m, n, pRow, pCol);

    if(nCount != 0)
    {
        printf("\nThe total saddle is: %d, they are: \n", nCount);

        for(i = 0; i < nCount; i++)
        {
            printf("a[%d][%d] = %d\n", pRow[i], pCol[i], a[pRow[i]][pCol[i]]);
        }
    }
    else
    {
        printf("There is no saddle(s)!\n");
    }

    free(pRow);
    free(pCol);
}

void test2D(void)
{
    /*
        ����1��1   2   3   4   5
                 2   4   6   8   10
                 3   6   9   12  15
                 4   8   12   16  20
        ����2��1   12    3    4    5
               2    4    16   8    10
               3    6    9    12    15
               4    8    12    16    20
         */
//
    // ��������
    int a[][5] =
    {
        {1, 2, 3, 4, 5},
        {2, 4, 6, 8, 10},
        {3, 6, 9, 12, 15},
        {4, 8, 12, 16, 20}
    };

    int i, m = 0, n = 0;
    int nCount = 0;

    // ���������������
    m = sizeof(a) / sizeof(a[0]);
    n = sizeof(a[0]) / sizeof(a[0][0]);

    // �������ڴ洢���С���λ�õĶ�̬����ָ��
    int *pRow = NULL, *pCol = NULL;

    // ��̬����Ĵ�С(�ٶ���m * n������)
    int nSize = m * n * sizeof(int);

    if ((pRow = (int *)malloc(nSize)) == NULL)
    {
        exit(1); // �ڴ����ʧ��
    }

    memset(pRow, 0, nSize); // ��0

    if ((pCol = (int *)malloc(nSize)) == NULL)
    {
        free(pRow); // �ͷ��ڴ�
        exit(1); // �ڴ����ʧ��
    }

    memset(pCol, 0, nSize); // ��0

    printf("the 2D array is: \n");
    Output2D(m, n, a); // ���ԭʼ����

    nCount = GetSaddlePoint2D(m, n, a, pRow, pCol);

    if(nCount != 0)
    {
        printf("\nThe total saddle is: %d, they are: \n", nCount);

        for(i = 0; i < nCount; i++)
        {
            printf("a[%d][%d] = %d\n", pRow[i], pCol[i], a[pRow[i]][pCol[i]]);
        }
    }
    else
    {
        printf("There is no saddle(s)!\n");
    }

    free(pRow);
    free(pCol);
}

//------------------------------------------------
// ���ƣ�void Input1D(int *a, int m, int n)
// ���ܣ�¼�������Ԫ�ص�ֵ
// ������
//           [int *a] --- ����ָ�룬ָ���ά������ʼ��ַ(&a[0][0])
//           [int m] --- ��������
//           [int n] --- ��������
// ���أ���
// ���ߣ����
// ���ڣ�2010��12��16��
//------------------------------------------------
void Input1D(int *a, int m, int n)
{
    int i, j;

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            // �ȼ���&a[i][j]
            // a + i * n���ҵ���i�У�
            // (a + i * n) + j���ҵ���j��
            scanf("%d", a + i * n + j);
        }
    }
}

//------------------------------------------------
// ���ƣ�void Output1D(int *a, int m, int n)
// ���ܣ���ʾ�����Ԫ�ص�ֵ
// ������
//           [int *a] --- ����ָ�룬ָ���ά������ʼ��ַ(&a[0][0])
//           [int m] --- ��������
//           [int n] --- ��������
// ���أ���
// ���ߣ����
// ���ڣ�2010��12��16��
//------------------------------------------------
void Output1D(int *a, int m, int n)
{
    int i, j;

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            //<==>a[i][j]
            //a + i * n���ҵ���i�У�
            //(a + i * n) + j���ҵ���j��
            printf("%8d", *(a + i * n + j));
        }

        printf("\n");
    }
}

//------------------------------------------------
// ���ƣ�void Input2D(int m, int n, int (*p)[n])
// ���ܣ�¼�������Ԫ�ص�ֵ��ͨ���䳤���飬����ָ�����ʽʵ��
// ������
//           [int m] --- ��������
//           [int n] --- ��������������������ָ���β�֮ǰ��
//                           ��Ϊ����ָ��ָ��������Ǳ䳤����
//           [int (*p)[n]] --- ����ָ�룬ָ���ά����(�䳤���飬��ҪC99)
// ���أ���
// ���ߣ����
// ���ڣ�2017��11��22��
//------------------------------------------------
void Input2D(int m, int n, int (*p)[n])
{
    int i, j;

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &p[i][j]);
        }
    }
}

//------------------------------------------------
// ���ƣ�void Output2D(int m, int n, int (*p)[n])
// ���ܣ���ʾ�����Ԫ�ص�ֵ��ͨ���䳤���飬����ָ�����ʽʵ��
// ������
//           [int m] --- ��������
//           [int n] --- ��������������������ָ���β�֮ǰ��
//                           ��Ϊ����ָ��ָ��������Ǳ䳤����
//           [int (*p)[n]] --- ����ָ�룬ָ���ά����(�䳤���飬��ҪC99)
// ���أ���
// ���ߣ����
// ���ڣ�2017��11��22��
//------------------------------------------------
void Output2D(int m, int n, int (*p)[n])
{
    int i, j;

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%8d", p[i][j]);
        }

        printf("\n");
    }
}

//------------------------------------------------
// ���ƣ�int GetMaxPos(int *a, int n)
// ���ܣ�����һ�������е����ֵ��λ��
// ������
//           [int *a] --- ����ָ�룬ָ��һά������ʼ��ַ
//           [int n] --- ���鳤��
// ���أ�int --- ���ֵ��λ��
// ���ߣ����
// ���ڣ�2010��12��16��
//------------------------------------------------
int GetMaxPos(int *a, int n)
{
    int max, Pos = 0;
    int i;

    max = a[0]; // ���ֵ��ʼֵ������a[0]

    for(i = 0; i < n; i++)
    {
        if(a[i] > max)
        {
            max = a[i];
            Pos = i; // ����
        }
    }

    return Pos;
}

//------------------------------------------------
// ���ƣ�int GetMinPos(int *a, int n)
// ���ܣ�����һ�������е���Сֵ��λ��
// ������
//           [int *a] --- ����ָ�룬ָ��һά������ʼ��ַ
//           [int n] --- ���鳤��
// ���أ�int --- ��Сֵ��λ��
// ���ߣ����
// ���ڣ�2010��12��16��
//------------------------------------------------
int GetMinPos(int *a, int n)
{
    int min, Pos = 0;
    int i;

    min = a[0]; // ��Сֵ��ʼֵ������a[0]

    for(i = 0; i < n; i++)
    {
        if(a[i] < min)
        {
            min = a[i];
            Pos = i; // ����
        }
    }

    return Pos;
}

//------------------------------------------------
// ���ƣ�void GetOneRow1D(int *a, int *p, int n, int i)
// ���ܣ���ȡ��ά������ָ����(��һά��ʽ����)
// ������
//           [int *a] --- ����ָ�룬ָ���ά������ʼ��ַ(&a[0][0])
//           [int *p] --- ����ָ�룬ָ����һά����
//           [int n] --- ��ά��������
//           [int i] --- ��Ҫ��ȡ����
// ���أ�[void] --- ��
// ���ߣ����
// ���ڣ�2017��11��22��
//------------------------------------------------
void GetOneRow1D(int *a, int *p, int n, int i)
{

    int nRow = n * sizeof(int); // һ��ռ�е��ֽ���
    int *pt = a + i * n; // �����i�е���ʼ��ַ

    memcpy(p, pt, nRow); // ���ݿ���
}

//------------------------------------------------
// ���ƣ�void GetOneRow2D(int n, int (*a)[n], int *p, int i)
// ���ܣ���ȡ��ά������ָ����(���ñ䳤�����β�ʵ��)
// ������
//           [int n] --- ��ά��������������������ָ���β�֮ǰ��
//                           ��Ϊ����ָ��ָ��������Ǳ䳤����
//           [int (*a)[n]] --- ����ָ�룬ָ���ά����(�䳤���飬��ҪC99)
//           [int *p] --- ����ָ�룬ָ����һά����

//           [int i] --- ��Ҫ��ȡ����
// ���أ�[void] --- ��
// ���ߣ����
// ���ڣ�2017��11��22��
//------------------------------------------------
void GetOneRow2D(int n, int (*a)[n], int *p, int i)
{

    int nRow = n * sizeof(int); // һ��ռ�е��ֽ���

    memcpy(p, a[i], nRow); // ���ݿ���
}

//------------------------------------------------
// ���ƣ�void GetOneCol1D(int *a, int *p, int m, int n, int j)
// ���ܣ���ȡ��ά������ָ����(��һά��ʽ����)
// ������
//           [int *a] --- ����ָ�룬ָ���ά������ʼ��ַ(&a[0][0])
//           [int *p] --- ����ָ�룬ָ����һά����
//           [int m] --- ��������
//           [int n] --- ��ά��������
//           [int j] --- ��Ҫ��ȡ����
// ���أ�[void] --- ��
// ���ߣ����
// ���ڣ�2017��11��22��
//------------------------------------------------
void GetOneCol1D(int *a, int *p, int m, int n, int j)
{
    //ȡ������j��ÿ�е�Ԫ��
    for(int i = 0; i < m; i++)
    {
        p[i] = *(a + i * n + j);
    }
}

//------------------------------------------------
// ���ƣ�void GetOneCol2D(int m, int n, int (*a)[n], int *p, int j)
// ���ܣ���ȡ��ά������ָ����(��������ָ���β�ʵ��)
// ������
//           [int m] --- ��������
//           [int n] --- ��ά��������������������ָ���β�֮ǰ��
//                           ��Ϊ����ָ��ָ��������Ǳ䳤����
//           [int (*a)[n]] --- ����ָ�룬ָ���ά����(�䳤���飬��ҪC99)
//           [int *p] --- ����ָ�룬ָ����һά����
//           [int j] --- ��Ҫ��ȡ����
// ���أ�[void] --- ��
// ���ߣ����
// ���ڣ�2017��11��22��
//------------------------------------------------
void GetOneCol2D(int m, int n, int (*a)[n], int *p, int j)
{
    //ȡ������j��ÿ�е�Ԫ��
    for(int i = 0; i < m; i++)
    {
        p[i] = a[i][j];
    }
}

//------------------------------------------------
// ���ƣ�int GetSaddlePoint1D(int *a, int m, int n, int *pRow, int *pCol)
// ���ܣ����ά�����еİ���λ�ü������
// ������
//           [int *a] --- ����ָ�룬ָ��������ʼ��ַ
//           [int m] --- ��������
//           [int n] --- ��������
//           [int *pRow] --- �������λ������ָ��
//           [int *pCol] --- �������λ������ָ��
// ���أ�int --- ����λ�ü������
// ���ߣ����
// ���ڣ�2010��12��16��
//------------------------------------------------
int GetSaddlePoint1D(int *a, int m, int n, int *pSaddleRow, int *pSaddleCol)
{
    int i, nSizeRow = 0, nSizeCol = 0;
    int *pRow = NULL, *pCol = NULL;
    int nMinRowPos, nMaxColPos;
    int nCount = 0;

    nSizeRow = n * sizeof(int); // ÿ�еĳ���
    nSizeCol = m * sizeof(int); // ÿ�еĳ���

    if ((pRow = (int *)malloc(nSizeRow)) == NULL)
    {
        exit(1); // �ڴ����ʧ��
    }

    memset(pRow, 0, nSizeRow); // ��0

    if ((pCol = (int *)malloc(nSizeCol)) == NULL)
    {
        free(pRow); // �ͷ��ڴ�
        exit(1); // �ڴ����ʧ��
    }

    memset(pCol, 0, nSizeCol); // ��0

    for(i = 0; i < m; i++)
    {
        // ��ȡ��i�е�����
        GetOneRow1D(a, pRow, n, i);
        // �ҵ���i�е����ֵ��λ��
        nMaxColPos = GetMaxPos(pRow, n);

        // ��ȡ��nMaxColPos�е�����
        GetOneCol1D(a, pCol, m, n, nMaxColPos);

        // �ҵ�������Сֵλ��
        nMinRowPos = GetMinPos(pCol, m);

        //������Сֵλ�ڸ��У����ҵ�����
        if(nMinRowPos == i)
        {
            pSaddleRow[nCount] = nMinRowPos;
            pSaddleCol[nCount] = nMaxColPos;
            nCount++;
        }
    }

    //�ͷſռ�
    free(pRow);
    free(pCol);

    //���ذ������
    return nCount;
}

//------------------------------------------------
// ���ƣ�int GetSaddlePoint2D(int m, int n, int (*a)[n], int *pRow, int *pCol)
// ���ܣ����ά�����еİ���λ�ü������(��������ָ���β�ʵ��)
// ������
//           [int m] --- ��������
//           [int n] --- ��ά��������������������ָ���β�֮ǰ��
//                           ��Ϊ����ָ��ָ��������Ǳ䳤����
//           [int (*a)[n]] --- ����ָ�룬ָ���ά����(�䳤���飬��ҪC99)
//           [int *pRow] --- �������λ������ָ��
//           [int *pCol] --- �������λ������ָ��
// ���أ�int --- ����λ�ü������
// ���ߣ����
// ���ڣ�2017��11��22��
//------------------------------------------------
int GetSaddlePoint2D(int m, int n, int (*a)[n], int *pSaddleRow, int *pSaddleCol)
{
    int i, nSizeRow = 0, nSizeCol = 0;
    int *pRow = NULL, *pCol = NULL;
    int nMinRowPos, nMaxColPos;
    int nCount = 0;

    nSizeRow = n * sizeof(int); // ÿ�еĳ���
    nSizeCol = m * sizeof(int); // ÿ�еĳ���

    if ((pRow = (int *)malloc(nSizeRow)) == NULL)
    {
        exit(1); // �����ڴ�ʧ��
    }

    memset(pRow, 0, nSizeRow); // ��0

    if ((pCol = (int *)malloc(nSizeCol)) == NULL)
    {
        free(pRow); // �ͷ��ڴ�
        exit(1); // �����ڴ�ʧ��
    }

    memset(pCol, 0, nSizeCol); // ��0

    for(i = 0; i < m; i++)
    {
        // ��ȡ��i�е�����
        GetOneRow2D(n, a, pRow, i);
        // �ҵ���i�е����ֵ��λ��
        nMaxColPos = GetMaxPos(pRow, n);

        // ��ȡ��nMaxColPos�е�����
        GetOneCol2D(m, n, a, pCol, nMaxColPos);

        // �ҵ�������Сֵλ��
        nMinRowPos = GetMinPos(pCol, m);

        //������Сֵλ�ڸ��У����ҵ�����
        if(nMinRowPos == i)
        {
            pSaddleRow[nCount] = nMinRowPos;
            pSaddleCol[nCount] = nMaxColPos;
            nCount++;
        }
    }

    //�ͷſռ�
    free(pRow);
    free(pCol);

    //���ذ������
    return nCount;
}



