/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：实现memcpy的演示代码。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2018年12月04日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 函数原型
void * MemCpyBytesNonOverlap(void *, const void *, size_t); // 不重叠，单字节复制
void * MemCpyBlocksNonOverlap(void *, const void *, size_t); // 不重叠，块复制
void * MemCpyBytesOverlap(void *, const void *, size_t); // 有重叠，单字节复制
void * MemCpyBlocksOverlap(void *, const void *, size_t); // 有重叠，块复制

// 测试
int main()
{
    char src[101] = "1234567890";
    char dst[101] = {'\0'};

    // 测试系统函数memcpy
    memcpy(dst, src, 10);
    puts(dst);

    // 测试无重叠按字节复制
    MemCpyBytesNonOverlap(dst + 20, dst, 10);
    puts(dst + 20);

    // 测试无重叠按块复制
    MemCpyBlocksNonOverlap(dst + 20, dst, 10);
    puts(dst + 20);

    // 测试有重叠按字节复制
    memset(dst, '\0', 101);
    memcpy(dst, src, 10);
    MemCpyBytesOverlap(dst + 5, dst, 10);
    puts(dst + 5);

    // 测试有重叠按块复制
    memset(dst, '\0', 101);
    memcpy(dst, src, 10);
    MemCpyBlocksOverlap(dst + 6, dst, 10);
    puts(dst + 6);

    memset(dst, '\0', 101);
    memcpy(dst, src, 6);
    MemCpyBlocksOverlap(dst + 3, dst, 6);
    puts(dst + 3);

    memset(dst, '\0', 101);
    MemCpyBlocksOverlap(dst, src, 10);
    MemCpyBlocksOverlap(dst + 10, src, 10);
    MemCpyBlocksOverlap(dst + 20, src, 10);
    MemCpyBlocksOverlap(dst + 15, dst, 30);
    puts(dst + 15);

    return 0;
}

// 函数定义

//-----------------------------------------------------------------------------------------------
// 名称: void *MemCpy(void *dst, const void *src, size_t count)
// 功能: 实现内存拷贝的代码
// 参数:
//         [void *dst] --- 目标内存首地址
//         [const void *src] --- 源内存首地址
//         [size_t count] --- 需要复制的内存字节数
// 返回: [void *]  --- 目标内存首地址
// 作者: 耿楠
// 日期: 2018年12月05日
// 注意: 该代码是错误代码：
//          (1) 无法对void *类型的指针执行*间接寻址操作
//          (2) 无法对void类型(*dst)进行赋值操作
//          (3) void *类型的指针执行++操作，含义不明确
//-----------------------------------------------------------------------------------------------
/*void * MemCpy(void *dst, const void *src, size_t count)
{
    if ((src == NULL) || (dst == NULL))
    {
        return NULL;
    }

    while (count--)
    {
        *dst++ = *src++;
    }

    return dst;
}*/

//-----------------------------------------------------------------------------------------------
// 名称: void *MemCpyBytesNonOverlap(void *dst, const void *src, size_t count)
// 功能: 不重叠，按单字节复制实现内存拷贝
// 算法: 将目标和源指针转换成char *类型的指针进行拷贝操作
// 参数:
//         [void *dst] --- 目标内存首地址
//         [const void *src] --- 源内存首地址
//         [size_t count] --- 需要复制的内存字节数
// 返回: [void *]  --- 目标内存首地址
// 作者: 耿楠
// 日期: 2018年12月05日
//-----------------------------------------------------------------------------------------------
void * MemCpyBytesNonOverlap(void *dst, const void *src, size_t count)
{
    // 数据有效性检查
    if ((src == NULL) || (dst == NULL) || (count < 0))
    {
        return NULL;
    }

    // 类型转换
    const char *psrc = (char *)src;
    char *pdst = (char *)dst;

    // 按字节拷贝
    while (count--)
    {
        *pdst++ = *psrc++;
    }

    return dst; // 返回目的地址
}

//-----------------------------------------------------------------------------------------------
// 名称: void *MemCpyBlocksNonOverlap(void *dst, const void *src, size_t count)
// 功能: 不重叠，按块复制实现内存拷贝
// 算法: 当要拷贝的空间大于等于一个long的长度时，计算出占有long的个数，
//          对这一部分数据按long的长度进行拷贝。
//          对剩下的数据按char单字节拷贝。
// 参数:
//         [void *dst] --- 目标内存首地址
//         [const void *src] --- 源内存首地址
//         [size_t count] --- 需要复制的内存字节数
// 返回: [void *]  --- 目标内存首地址
// 作者: 耿楠
// 日期: 2018年12月05日
//-----------------------------------------------------------------------------------------------
void * MemCpyBlocksNonOverlap(void *dst, const void *src, size_t count)
{
    // 数据有效性检查
    if ((src == NULL) || (dst == NULL) || (count < 0))
    {
        return NULL;
    }

    size_t word_count  = count / sizeof(long); // 按long块拷贝个数
    size_t slice =   count % sizeof(long); // 剩余的按字节拷贝个数

    // 类型转换
    const long *psrc = (long *)src;
    long *pdst = (long *)dst;

    // 块拷贝
    while(word_count--)
    {
        *pdst++ = *psrc++;
    }

    // 剩余的按字节拷贝
    // 类型转换
    const char *ps = (char *)psrc;
    char *pd = (char *)pdst;

    while (slice--)
    {
        *pd++ = *ps++;
    }

    return dst; // 返回目的地址
}

//-----------------------------------------------------------------------------------------------
// 名称: void *MemCpyBytesOverlap(void *dst, const void *src, size_t count)
// 功能: 有重叠，按单字节复制实现内存拷贝
// 算法: 目标地址和源地址之间的关系可能有：
//          (1) |_;_;_;_;_;_|                        (src)
//              ^                     |_;_;_;_;_;_|  (dst)
//                                    ^
//          (2) |_;_;_;_;_;_|                        (dst)
//              ^                     |_;_;_;_;_;_|  (src)
//                                    ^
//          (3) |_;_;_;_;_;_|                        (src)
//              ^     |_;_;_;_;_;_|                  (dst)
//                    ^
//          (4) |_;_;_;_;_;_|                        (dst)
//              ^     |_;_;_;_;_;_|                  (src)
//                    ^
//          其中，(1)和(2)中dst没有重叠src，按常规操作就可以实现数据拷贝，
//          (4)中由于dst在src之前，从低地址端向高地址端拷贝不会产生错误，
//          但(3)中src在dst之前，当从低地址端向高地址端拷贝时，则会覆盖
//          src中重叠部分的数据，从而产生错误，因此此时应该从高地址向地地址拷贝。
// 参数:
//         [void *dst] --- 目标内存首地址
//         [const void *src] --- 源内存首地址
//         [size_t count] --- 需要复制的内存字节数
// 返回: [void *]  --- 目标内存首地址
// 作者: 耿楠
// 日期: 2018年12月05日
//-----------------------------------------------------------------------------------------------
void * MemCpyBytesOverlap(void *dst, const void *src, size_t count)
{
    // 数据有效性检查
    if ((src == NULL) || (dst == NULL) || (count < 0))
    {
        return NULL;
    }

    // 声明指针
    const char *psrc;
    char *pdst;

    // 有重叠
    if((src < dst) && ((char*)src + count > (char*)dst))
    {
        // 类型转换
        psrc = (char *)((char *)src + count - 1); // 指向源地址高端
        pdst = (char *)((char *)dst + count - 1); // 指向目标地址高端

        // 从高端地址向低端地址复制
        while (count --)
        {
            *pdst-- = *psrc--;
        }
    }
    else // 无重叠
    {
        // 类型转换
        psrc = (char *)src;
        pdst = (char *)dst;

        // 从低端地址向高端地址复制
        while (count--)
        {
            *pdst++ = *psrc++;
        }
    }

    return dst; // 返回目的地址
}

//-----------------------------------------------------------------------------------------------
// 名称: void *MemCpyBlocksOverlap(void *dst, const void *src, size_t count)
// 功能: 有重叠，按块复制实现内存拷贝
// 算法: 当要拷贝的空间大于等于一个long的长度时，计算出占有long的个数，
//          对这一部分数据按long的长度进行拷贝。
//          对剩下的数据按char单字节拷贝。
//          目标地址和源地址之间的关系可能有：
//          (1) |_;_;_;_;_;_|                        (src)
//              ^                     |_;_;_;_;_;_|  (dst)
//                                    ^
//          (2) |_;_;_;_;_;_|                        (dst)
//              ^                     |_;_;_;_;_;_|  (src)
//                                    ^
//          (3) |_;_;_;_;_;_|                        (src)
//              ^     |_;_;_;_;_;_|                  (dst)
//                    ^
//          (4) |_;_;_;_;_;_|                        (dst)
//              ^     |_;_;_;_;_;_|                  (src)
//                    ^
//          其中，(1)和(2)中dst没有重叠src，按常规操作就可以实现数据拷贝，
//          (4)中由于dst在src之前，从低地址端向高地址端拷贝不会产生错误，
//          但(3)中src在dst之前，当从低地址端向高地址端拷贝时，则会覆盖
//          src中重叠部分的数据，从而产生错误，因此此时应该从高地址向地地址拷贝。
// 参数:
//         [void *dst] --- 目标内存首地址
//         [const void *src] --- 源内存首地址
//         [size_t count] --- 需要复制的内存字节数
// 返回: [void *]  --- 目标内存首地址
// 作者: 耿楠
// 日期: 2018年12月05日
//-----------------------------------------------------------------------------------------------
void * MemCpyBlocksOverlap(void *dst, const void *src, size_t count)
{
    // 数据有效性检查
    if ((src == NULL) || (dst == NULL) || (count < 0))
    {
        return NULL;
    }

    size_t word_count = count / sizeof(long); // 按块拷贝的数量
    size_t slice = count % sizeof(long); // 按字节拷贝的数量

    if((src < dst) && ((char*)src + count > (char*)dst)) // 有数据重叠
    {
        if(word_count > 0)  //要拷贝的空间大于等于一个long的情况！
        {
            // 类型转换
            const long *psrc = (long*)((char*)src + count);
            long *pdst = (long*)((char*)dst + count);

            // 按块拷贝
            while(word_count--)
            {
                pdst--;
                psrc--;
                *pdst = *psrc;
            }

            // 剩余部分按字节拷贝
            // 类型转换
            const char *ps = (char *)psrc;
            char *pd = (char *)pdst;
            while(slice--)
            {
                ps--;
                pd--;
                *pd = *ps;
            }
        }
        else  // 要拷贝的空间小于一个long的情况！
        {
            // 类型转换
            const char *psrc = (char*)src + count - 1;
            char *pdst = (char*)dst + count - 1;

            // 按字节拷贝
            while(slice--)
            {
                *pdst-- = *psrc--;
            }
        }
    }
    else  // 无重叠情况
    {
        // 类型转换
        const long *psrc = (long*)src;
        long *pdst = (long*)dst;

        // 块拷贝
        while(word_count--)
        {
            *pdst++ = *psrc++;
        }

        // 类型转换
        const char *ps = (char*)psrc;
        char *pd = (char*)pdst;

        // 字节拷贝
        while(slice--)
        {
            *pd++ = *ps++;
        }
    }

    return dst; // 返回地址
}
