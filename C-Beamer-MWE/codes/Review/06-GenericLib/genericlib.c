/*--------------------------------------------------------------------------------
* Copyright (c) 2017,����ũ�ֿƼ���ѧ��ϢѧԺ�������ѧϵ
* All rights reserved.
*
* �ļ����ƣ�genericsort.c
* �ļ���ʶ�������ù���ƻ���
* ժҪ����������ĺ�������(��̬���ӿ�)��
*
* ��ǰ�汾��1.0
* ���ߣ����
* ������ڣ�2017��12��12��
*
* ȡ���汾����
* ԭ���ߣ����
* ������ڣ�2017��12��12��
------------------------------------------------------------------------------------*/
#include <string.h>
#include "genericlib.h"

#define QSORTMINLEN 20 // �ڵݹ����������תΪ�����������ֵ

//-----------------------------------------------------------------------------------------------
// ���ƣ�void Traversal(void *ptr, size_t count, size_t size, void (*pf)(void *))
// ���ܣ�ʵ������ı���(�ڴ����Ҫ����)
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [size_t count] --- ���鳤��
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(a[0])
//       [void (*pf)(void *)] --- �����������һ��Ԫ�صĺ����ĺ���ָ��
// ���أ���
// ���ߣ����
// ���ڣ�2017��11��19��
//-----------------------------------------------------------------------------------------------
void Traversal(void *ptr, size_t count, size_t size, itemFuncType pf)
{
    for(int i  = 0; i < count; i++)
    {
        pf(ptr + i * size); // ����ÿ��Ԫ�صĵ�ַ�������������
    }
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�void GenericSwap(void *p1, void *p2, size_t size)
// ���ܣ�ʵ�������������Ľ���
// ������
//       [void *p1] --- ��һ������ʼ��ַ��ָ��
//       [void *p2] --- �ڶ�������ʼ��ַ��ָ��
//       [size_t size] --- ����ռ���ڴ�Ĵ�С(�ֽ�)
// ���أ���
// ע�⣺�����ڴ濽����ʽʵ�֣���Ҫ֪��ռ�е��ڴ��С
// ���ߣ����
// ���ڣ�2017��11��19��
//-----------------------------------------------------------------------------------------------
void GenericSwap(void *p1, void *p2, size_t size)
{
    void *pt = malloc(size); // ����1��Ԫ�ش�С���ڴ�

    // ��0
    memset(pt, 0, size);

    // �����ڴ������
    memcpy(pt, p1, size);
    memcpy(p1, p2, size);
    memcpy(p2, pt, size);

    // �ͷ��ڴ�
    free(pt);
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�void GenericBubbleSort(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ�����ð������(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
//            �����˽�ǰһ����󽻻�λ����Ϊ�´�ѭ���߽���Ż��㷨��
//            �����Ż��㷨�μ���http://www.algorithmist.com/index.php/Bubble_sort
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [size_t count] --- ���鳤��
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ���
// ���ߣ����
// ���ڣ�2017��11��19��
//-----------------------------------------------------------------------------------------------
void GenericBubbleSort(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    int bound = count - 1, new_bound = 0;

    for(int i = 0; i < count - 1; i++ )
    {
        for(int j = 0; j < bound; j++)
        {
            if(comp(ptr + j * size, ptr + (j + 1) * size) > 0) // �Ƚϣ�ǰһ�����Ⱥ�һ�����󣬷�����ֵ
            {
                GenericSwap(ptr + j * size, ptr + (j + 1) * size, size); // ����
                new_bound = j; // �������һ�η���������λ��
            }
        }
        bound = new_bound; // �����ڲ�ѭ���Ͻ�
    }
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�void GenericSelectSort(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ�����ѡ������(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
//           �㷨����μ���http://www.algorithmist.com/index.php/Bubble_sort
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [size_t count] --- ���鳤��
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ���
// ���ߣ����
// ���ڣ�2017��11��24��
//-----------------------------------------------------------------------------------------------
void GenericSelectSort(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    for(int i = 0; i < count; i++ )
    {
        int selpos = i;
        for(int j = i + 1; j < count; j++)
        {
            if(comp(ptr + selpos * size, ptr + j * size) > 0) // �Ƚ�
            {
                selpos = j;
            }
        }
        if(selpos != i) // ���ֽ���Ԫ��
        {
            GenericSwap(ptr + i * size, ptr + selpos * size, size); // ����
        }
    }
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�void GenericInsertSort(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ����Ͳ�������(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
//           �㷨����μ���http://www.algorithmist.com/index.php/Bubble_sort
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [size_t count] --- ���鳤��
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ���
// ���ߣ����
// ���ڣ�2017��11��24��
//-----------------------------------------------------------------------------------------------
void GenericInsertSort(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    int i = 1;
    int j;

    // �������ڿճ�λ�õ���ʱ�ռ�
    void *p = malloc(size); // ����һ��Ԫ�ش�С(�ֽ�)���ڴ�����

    while(i < count)
    {
        if(comp(ptr + i * size, ptr + (i - 1) * size) < 0) // ��������������������
        {
            memcpy(p, ptr + i * size, size); // ���浱ǰԪ�أ�������λ
            j = i - 1;
            while (j >= 0 && comp(ptr + j * size, p) > 0) // �ҵ������
            {
                //memcpy(ptr + (j + 1) * size, ptr + j * size, size); // �����������
                j--;
            }
            memmove(ptr + (j + 2) * size, ptr + (j + 1) * size, (i - 1 - j) * size); // �����������
            memcpy(ptr + (j + 1) * size, p, size); // �ڿ�λ���뱣�������һ��Ԫ��
        }
        i++;
    }

    free(p);
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�void GenericRecursiveSelSort(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ�����ð������(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
//           ���õݹ�ʵ�֡�
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [size_t count] --- ���鳤��
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ���
// ���ߣ����
// ���ڣ�2017��11��21��
//-----------------------------------------------------------------------------------------------
void GenericRecursiveBubbleSort(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    if(count < 2)
    {
        return;
    }

    for(int i = 0; i < count - 1; i++) // һ���ڵ�����
    {
        if(comp(ptr + i * size, ptr + (i + 1) * size) > 0) // �Ƚ�
        {
            GenericSwap(ptr + i * size, ptr + (i + 1) * size, size); // ����
        }
    }
    GenericRecursiveBubbleSort(ptr, count - 1, size, comp); // �ݹ鵽��һ��
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�void GenericRecursiveSelectSort(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ�����ѡ������(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
//           ���õݹ�ʵ�֡�
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [size_t count] --- ���鳤��
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ���
// ���ߣ����
// ���ڣ�2017��11��21��
//-----------------------------------------------------------------------------------------------
void GenericRecursiveSelectSort(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    if(ptr == NULL)   //�ж������Ƿ�Ϊ��
    {
        return;
    }
    else
    {
        void *p = ptr; // ��¼��ʼ��ַ

        if(count == 1) // count==1��ʾ�����Ѿ���ɣ��ݹ����
        {
            return;
        }

        int selIdx = 0; // �ٶ���0��Ԫ��Ϊ��С(��)��
        for(int i = 1; i < count; i++) // ���Ҹ�С(��)����λ��
        {
            if(comp(p + selIdx * size, p + i * size) > 0) // �Ƚ�
            {
                selIdx = i; // ������С(��)ֵ��λ��
                //GenericSwap(p, p + i * size, size); // ����
            }
        }

        if(selIdx != 0)
        {
            GenericSwap(p, p + selIdx * size, size); // ����������С(��)��������ǰ��
        }

        // �ݹ�����ʣ�µ�����
        p += size; // ǰ��1��Ԫ��
        count--; // Ԫ�س��ȼ�1
        GenericRecursiveSelectSort(p, count, size, comp);
    }
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�void GenericRecursiveInsertSort(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ����Ͳ�������(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
//           ���õݹ�ʵ�֡�
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [size_t count] --- ���鳤��
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ���
// ���ߣ����
// ���ڣ�2017��11��21��
//-----------------------------------------------------------------------------------------------
void GenericRecursiveInsertSort(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    // �������������ݹ�
    if (count <= 1)
    {
        return;
    }

    // �ݹ飬����ǰ n - 1 ��Ԫ��
    GenericRecursiveInsertSort(ptr, count - 1, size, comp);

    // �����һ��Ԫ�ز��뵽������������еĺ���λ��
    void *p = malloc(size); // ����һ��Ԫ�ش�С(�ֽ�)���ڴ�����
    memcpy(p, ptr + (count - 1) * size, size); // �������һ��Ԫ��
    int j = count - 2;

    // ��ptr[0..i-1]�д�(С)�����һ��Ԫ�ص�Ԫ�غ���һ��λ�ã�
    // �Ա�Ϊ�����Ԫ��������λ
    while (j >= 0 && comp(ptr + j * size, p) > 0)
    {
        //memcpy(ptr + (j + 1) * size, ptr + j * size, size); // �����������
        j--;
    }
    memmove(ptr + (j + 2) * size, ptr + (j + 1) * size, (count - 2 - j) * size); // �����������
    memcpy(ptr + (j + 1) * size, p, size); // �ڿ�λ���뱣�������һ��Ԫ�أ�ע��j��--��λ

    free(p); // �ͷ���ʱ�ռ�
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�static int PartitionByFirst(void *ptr, int low, int high, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ����Ϳ�����������ָ��(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
//           �㷨����μ���K.N. King ��, ����� ��ٻ��. C���Գ������:�ִ�����(��2��), ����:�����ʵ������, 2013, PP: 145-147.
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [int low] --- ������ʼ�����±�
//       [int high] --- ������������±�
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ�[static int] --- ����ָ�λ�ã���ߵ�С(��)�ڷָ�λ�õ�Ԫ�أ��ұ߷�֮
// ע�⣺[static int] --- static��Ŀ���ǽ��ڴ��ļ���ʹ�øú���
// ���ߣ����
// ���ڣ�2017��11��24��
//-----------------------------------------------------------------------------------------------
static int PartitionByFirst(void *ptr, int low, int high, size_t size, cmpFuncType comp)
{
    // ��lowλ�õ�Ԫ�ر��ݣ�������λ
    void *p = malloc(size); // ����һ��Ԫ�ش�С(�ֽ�)���ڴ�����
    memcpy(p, ptr + low * size, size); // ����

    // ����ѭ��(ͨ���ж�����break����)
    for (;;)
    {
        // ��hight��low������С�ڣ����ڣ��ָ�Ԫ�ص�Ԫ��
        while (low < high && comp(ptr + high * size, p) > 0)
        {
            high--;
        }
        // �����������˳�ѭ��
        if (low >= high)
        {
            break;
        }
        // ��С�ڣ����ڣ��ָ�Ԫ�ص�Ԫ�ص�����lowλ
        // Ȼ��low + 1
        memcpy(ptr + low * size, ptr + high * size, size);
        low++;

        // ��low��hight�����Ҵ��ڣ�С�ڣ��ָ�Ԫ�ص�Ԫ��
        while (low < high && comp(ptr + low * size, p) < 0)
        {
            low++;
        }
        // �����������˳�ѭ��
        if (low >= high)
        {
            break;
        }
        // �����ڣ�С�ڣ��ָ�Ԫ�ص�Ԫ�ص�����highλ
        // Ȼ��high - 1
        memcpy(ptr + high * size, ptr + low * size, size);
        high--;
    }

    // ���ָ�Ԫ�������ҵ���λ��(��λ)
    // ��ʱ��ߵ�����Ԫ��С��(����)�ָ�Ԫ��
    // �ұߵ�����Ԫ�ش���(С��)�ָ�Ԫ��
    memcpy(ptr + high * size, p, size);

    // �ͷſռ�
    free(p);
    // ���طָ�Ԫ�ص�λ��
    return high;
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�static int PartitionByMedian(void *ptr, int low, int high, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ����Ϳ�����������ָ��(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
//           �㷨�����õ�1�������1�����м���3��Ԫ�ص���ֵ��Ϊ����Ԫ�ء�
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [int low] --- ������ʼ�����±�
//       [int high] --- ������������±�
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ�[static int] --- ����ָ�λ�ã���ߵ�С(��)�ڷָ�λ�õ�Ԫ�أ��ұ߷�֮
// ע�⣺[static int] --- static��Ŀ���ǽ��ڴ��ļ���ʹ�øú���
// ���ߣ����
// ���ڣ�2017��11��24��
//-----------------------------------------------------------------------------------------------
static int PartitionByMedian(void *ptr, int low, int high, size_t size,  cmpFuncType comp)
{
    int pivot; // ����Ԫ��λ��
    int mid = low + (high - low) / 2; // �м�Ԫ��λ��

    // �ҵ��������Ĵ���λ��
    pivot = comp(ptr + low * size, ptr + mid * size) > 0 ? low : mid;

    // �ҵ���С����λ��
    if(comp(ptr + pivot * size, ptr + high * size) > 0)
    {
        pivot = high;
    }

    // ������Ԫ�����1��Ԫ�ؽ��н���
    GenericSwap(ptr + pivot * size, ptr + low * size, size);
    pivot = low; // ��ʼ����λ��

    while(low < high)
    {
        //  �����ǰ(low)Ԫ��С(��)�����Ԫ��(high)���򽻻�����λ�����1��Ԫ�أ�
        //  ����pivot++������low++
        if(comp(ptr + low * size, ptr + high * size) <= 0)
        {
            GenericSwap(ptr + pivot * size, ptr + low * size, size); // ����
            pivot++;
        }
        low++;
    }

    // ��������(pivot)�����(high)λ�õ�Ԫ��
    // ��ʱ����(pivot)ǰ���ȫС(��)������(pivot)Ԫ�أ��ұ����෴
    GenericSwap(ptr + pivot * size, ptr + high * size, size);

    return pivot; // ��������λ��
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�static int PartitionByLast(void *ptr, int low, int high, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ����Ϳ�����������ָ��(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
//           �㷨���������1����Ϊ����Ԫ�ء�
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [int low] --- ������ʼ�����±�
//       [int high] --- ������������±�
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ�[static int] --- ����ָ�λ�ã���ߵ�С(��)�ڷָ�λ�õ�Ԫ�أ��ұ߷�֮
// ע�⣺[static int] --- static��Ŀ���ǽ��ڴ��ļ���ʹ�øú���
// ���ߣ����
// ���ڣ�2017��11��27��
//-----------------------------------------------------------------------------------------------
static int PartitionByLast(void *ptr, int low, int high, size_t size, cmpFuncType comp)
{
    void *p = NULL; // �洢����λ���ϵ�Ԫ��ֵ
    int i = low - 1; // ��СԪ�ص�����

    p = malloc(size); // ����ռ�
    memcpy(p, ptr + high * size, size); // �����һ��Ԫ����Ϊ����

    for(int j = low; j <= high - 1; j++)
    {
        // ��ǰԪ��С(��)�ڻ��������Ԫ��
        if(comp(p, ptr + j * size) >= 0)
        {
            i++; // ��СԪ��������1
            GenericSwap(ptr + i * size, ptr + j * size, size);
        }
    }
    GenericSwap(ptr + (i + 1) * size, ptr + high * size, size);
    free(p);

    return i + 1; // ��������λ��
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�static int PartitionByMiddle(void *ptr, int low, int high, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ����Ϳ�����������ָ��(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
//           �㷨�������м�Ԫ����Ϊ����Ԫ��(Standard Hoare partition scheme)��
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [int low] --- ������ʼ�����±�
//       [int high] --- ������������±�
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ�[static int] --- ����ָ�λ�ã���ߵ�С(��)�ڷָ�λ�õ�Ԫ�أ��ұ߷�֮
// ע�⣺[static int] --- static��Ŀ���ǽ��ڴ��ļ���ʹ�øú���
// ���ߣ����
// ���ڣ�2017��11��27��
//-----------------------------------------------------------------------------------------------
static int PartitionByMiddle(void *ptr, int low, int high, size_t size, cmpFuncType comp)
{
    int pivot = low + (high - low) / 2;
    void *p = NULL; // �洢����λ���ϵ�Ԫ��ֵ

    p = malloc(size); // ����ռ�
    memcpy(p, ptr + pivot * size, size); // ���м�Ԫ����Ϊ����

    int leftI = low - 1;
    int rightI = high + 1;

    while(leftI <= rightI)
    {
        while(comp(p, ptr + (++leftI) * size) > 0)
        {
            ;
        }
        while(comp(p, ptr + (--rightI) * size) < 0)
        {
            ;
        }
        if(leftI >= rightI)
        {
            break;
        }
        GenericSwap(ptr + leftI * size, ptr + rightI * size, size);
    }

    free(p);
    return rightI;
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�void GenericIterativeQuickSort(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ��ǵݹ鷺�Ϳ�������(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
//           �㷨����ջ����ÿһ���������Ӵ�����βԪ���±꣬��һ��whileѭ��ʱȡ�������Χ��
//                     ����������н���PartitionByFirst������
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [size_t count] --- ���鳤��
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ���
// ���ߣ����
// ���ڣ�2017��11��24��
//-----------------------------------------------------------------------------------------------
void GenericIterativeQuickSort(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    int startIndex = 0; // ��Ԫ���±�
    int endIndex = count - 1; // βԪ���±�

    int top = -1; // ջ��
    int* stack = (int*)malloc(sizeof(int) * count); // ����ջ�ռ�

    stack[++top] = startIndex; // ��Ԫ���±�ѹջ
    stack[++top] = endIndex; // βԪ���±�ѹջ

    while (top >= 0)
    {
        endIndex = stack[top--]; // ������Ԫ���±�
        startIndex = stack[top--]; // ����βԪ���±�

        int p = PartitionByFirst(ptr, startIndex, endIndex, size, comp); // ���ҷָ�Ԫ��λ��

        if (p - 1 > startIndex) // ǰ���
        {
            stack[++top] = startIndex; // ��Ԫ���±�ѹջ
            stack[++top] = p - 1; // βԪ���±�ѹջ
        }

        if (p + 1 < endIndex) // ����
        {
            stack[++top] = p + 1; // ��Ԫ���±�ѹջ
            stack[++top] = endIndex; // βԪ���±�ѹջ
        }
    }

    free(stack); // �ͷ�ջ�ռ�
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�static void QuickSort(void *ptr, int low, int high, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ����Ϳ�������ݹ麯��(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
//           �㷨����μ���K.N. King ��, ����� ��ٻ��. C���Գ������:�ִ�����(��2��), ����:�����ʵ������, 2013, PP: 145-147.
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [int low] --- ������ʼ�����±�
//       [int high] --- ������������±�
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ���
// ע�⣺[static void] --- static��Ŀ���ǽ��ڴ��ļ���ʹ�øú���
// ���ߣ����
// ���ڣ�2017��11��24��
//-----------------------------------------------------------------------------------------------
static void QuickSort(void *ptr, int low, int high, size_t size,
                      cmpFuncType comp, // �ȽϺ���
                      int (*partition)(void *, int, int, size_t, cmpFuncType)
                     )
{
    int pivot; // �ָ�Ԫ��λ��(����)

    if (low >= high) // �ݹ�������������龰��
    {
        return;
    }

    // �ָ����飬���ָ�Ԫ�ص��������ʵ�λ��
    // �����طָ�Ԫ���������е�λ��
    pivot = partition(ptr, low, high, size, comp);
    // ��low��splitpos - 1֮���Ԫ�صݹ�����
    QuickSort(ptr, low, pivot - 1, size, comp, partition);
    // ��splitpos + 1��high֮���Ԫ�صݹ�����
    QuickSort(ptr, pivot + 1, high, size, comp, partition);
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�void GenericQuickSortRecursiveByFirst(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ��ݹ鷺�Ϳ��������װ������(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
//           �㷨����μ���K.N. King ��, ����� ��ٻ��. C���Գ������:�ִ�����(��2��), ����:�����ʵ������, 2013, PP: 145-147.
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [size_t count] --- ���鳤��
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ���
// ע�⣺��ֻ��һ����װ������������Ϊ�����������ṩһ��ͳһ�Ľӿڡ�
// ���ߣ����
// ���ڣ�2017��11��24��
//-----------------------------------------------------------------------------------------------
void GenericQuickSortRecursiveByFirst(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    QuickSort(ptr, 0, count - 1, size, comp, PartitionByFirst); // ���������Ŀ���������
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�static void QuickSortTailRecursive(void *ptr, int low, int high, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ����Ϳ�������ݹ麯��(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
//           �㷨������β���Ż��ݹ飬���ҵ����鳤��С��QSORTMINLEN(����ȡ20)ʱת���������
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [size_t count] --- ���鳤��
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ���
// ע�⣺[static void] --- static��Ŀ���ǽ��ڴ��ļ���ʹ�øú���
// ���ߣ����
// ���ڣ�2017��11��24��
//-----------------------------------------------------------------------------------------------
static void QuickSortTailRecursive(void *ptr, int low, int high, size_t size, cmpFuncType comp)
{
    while(high - low > QSORTMINLEN)  // С�ڸ�������ʱ�����ݹ�
    {
        int pivot; // �ָ�Ԫ��λ��(����)

        // �ָ����飬���ָ�Ԫ�ص��������ʵ�λ��
        // �����طָ�Ԫ���������е�λ��
        pivot = PartitionByMedian(ptr, low, high, size, comp);

        // ���������鳤��ѡ����ʵĵݹ�;��
        if(pivot - low < high - pivot)
        {
            // ��low��pivot - 1֮���Ԫ�صݹ�����
            QuickSortTailRecursive(ptr, low, pivot - 1, size, comp);
            low = pivot + 1;
        }
        else
        {
            // ��pivot + 1��high֮���Ԫ�صݹ�����
            QuickSortTailRecursive(ptr, pivot + 1, high, size, comp);
            high = pivot - 1;
        }
    }
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�void GenericQuickSortRecursiveByMedian(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ��ݹ鷺�Ϳ��������װ������(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [size_t count] --- ���鳤��
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ���
// ע�⣺��ֻ��һ����װ������������Ϊ�����������ṩһ��ͳһ�Ľӿڡ�
// ���ߣ����
// ���ڣ�2017��11��24��
//-----------------------------------------------------------------------------------------------
void GenericQuickSortRecursiveByMedian(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    QuickSortTailRecursive(ptr, 0, count - 1, size, comp); // �����Ż��ݹ����������
    GenericInsertSort(ptr, count, size, comp); // ���ò�������
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�void GenericQuickSortRecursiveByLast(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ��ݹ鷺�Ϳ��������װ������(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
//           �㷨���������һ��Ԫ��Ϊ����Ԫ��
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [size_t count] --- ���鳤��
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ���
// ע�⣺��ֻ��һ����װ������������Ϊ�����������ṩһ��ͳһ�Ľӿڡ�
// ���ߣ����
// ���ڣ�2017��11��27��
//-----------------------------------------------------------------------------------------------
void GenericQuickSortRecursiveByLast(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    QuickSort(ptr, 0, count - 1, size, comp, PartitionByLast); // ���������Ŀ���������
}


//-----------------------------------------------------------------------------------------------
// ���ƣ�static void QuickSortRecursiveByMiddle(void *ptr, int low, int high, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ����Ϳ�������ݹ麯��(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
//           �㷨�������м�ֵ��Ϊ����Ԫ��(Standard Hoare partition scheme)��
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [int low] --- ������ʼ�����±�
//       [int high] --- ������������±�
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ���
// ע�⣺[static void] --- static��Ŀ���ǽ��ڴ��ļ���ʹ�øú�����
//                                   ���ڱ�׼�㷨�ݹ鷽ʽ��first��last��һ�£��������һ������
// ���ߣ����
// ���ڣ�2017��11��27��
//-----------------------------------------------------------------------------------------------
static void QuickSortRecursiveByMiddle(void *ptr, int low, int high, size_t size, cmpFuncType comp)
{
    int pivot;

    if(low >= high)
    {
        return;
    }

    pivot = PartitionByMiddle(ptr, low, high, size, comp);

    QuickSortRecursiveByMiddle(ptr, low, pivot, size, comp);
    QuickSortRecursiveByMiddle(ptr, pivot + 1, high, size, comp);
}

//-----------------------------------------------------------------------------------------------
// ���ƣ�void GenericQuickSortRecursiveByMiddle(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// ���ܣ��ݹ鷺�Ϳ��������װ������(����ָ�����ڱȽϣ�ʵ�ֲ�ͬ�������͵���/����)
//           �㷨�������м�Ԫ��Ϊ����Ԫ��(Standard Hoare partition scheme)��
// ������
//       [void *ptr] --- ������ʼ��ַ��ָ��
//       [size_t count] --- ���鳤��
//       [size_t size] --- ����һ��Ԫ�صĴ�С(�ֽ�)������ʹ��sizeof(ptr[0])
//       [cmpFuncType comp] --- �Ƚ�����Ԫ�ش�С�ĺ����ĺ���ָ��
//                         Ҫ����ǰһ���Ⱥ�һ���󣬷�����ֵ�����򷵻�0��ֵ��
// ���أ���
// ע�⣺��ֻ��һ����װ������������Ϊ�����������ṩһ��ͳһ�Ľӿڡ�
// ���ߣ����
// ���ڣ�2017��11��27��
//-----------------------------------------------------------------------------------------------
void GenericQuickSortRecursiveByMiddle(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    QuickSortRecursiveByMiddle(ptr, 0, count - 1, size, comp); // ���������Ŀ���������
}
