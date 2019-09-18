/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：检查单词是否为变位词(相同字母的重新排列)的演示代码。
* 题目：在英语中，如果两个单词中出现的字母相同，
*           并且每个字符出现的次数也相同，
*           那么这两个单词互为变位词(Anagram)。例如：
*           slient与listen、evil与live等互为变位词。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2018年12月07日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 函数原型
int IsAnagramMaps(const char *, const char *); // 检查单词是否为变位词(映射数组算法)
int IsAnagramSorted(const char *, const char *); // 检查单词是否为变位词(排序算法)

int main()
{
    char str1[] = "listen";
    char str2[] = "slient";
    char str3[] = "alient";
    char str4[] = "evil";
    char str5[] = "live";
    char str6[] = "eil";
    char str7[] = "evil1";
    char str8[] = "live1";

    // 映射表算法
//    int ret1 = IsAnagramMaps(str1, str2);
//    int ret2 = IsAnagramMaps(str1, str3);
//    int ret3 = IsAnagramMaps(str4, str5);
//    int ret4 = IsAnagramMaps(str6, str5);
//    int ret5 = IsAnagramMaps(str7, str8);

    // 排序算法
    int ret1 = IsAnagramSorted(str1, str2);
    int ret2 = IsAnagramSorted(str1, str3);
    int ret3 = IsAnagramSorted(str4, str5);
    int ret4 = IsAnagramSorted(str6, str5);
    int ret5 = IsAnagramSorted(str7, str8);

    if(ret1)
    {
        printf("%s and %s is angram.\n", str1, str2);
    }
    else
    {
        printf("%s and %s is not angram.\n", str1, str2);
    }

    if(ret2)
    {
        printf("%s and %s is angram.\n", str1, str3);
    }
    else
    {
        printf("%s and %s is not angram.\n", str1, str3);
    }

    if(ret3)
    {
        printf("%s and %s is angram.\n", str4, str5);
    }
    else
    {
        printf("%s and %s is not angram.\n", str4, str5);
    }

    if(ret4)
    {
        printf("%s and %s is angram.\n", str6, str5);
    }
    else
    {
        printf("%s and %s is not angram.\n", str6, str5);
    }

    if(ret5)
    {
        printf("%s and %s is angram.\n", str7, str8);
    }
    else
    {
        printf("%s and %s is not angram.\n", str7, str8);
    }

    return 0;
}

// 函数定义

//-----------------------------------------------------------------------------------------------
// 名称: int IsAnagramMaps(const char *str1, const char *str2)
// 功能: 检查两个单词是否为变位词(相同字母的重新排列)
// 算法: 可以用1个一维数组映射第1个字符串中的每个字母，统计字符串中每个字母出现的次数，
//          当扫描到第1个字符串中出现的每个字母时，为数组对应元素值加1。
//          接下来扫描第2个字符串，扫描到每个字母时，为数组对应元素值减1。
//          如果扫描完整个字符串后，数组中所有的值都是0，那么这两个字符串互为变位词。
//          可参考《C语言程序设计_现代方法(第2版)》P125编程题第2题的思路。
// 注意: 如果两个字符串长度不相等，则一定不是变位词。
//          如果字符串中含有非字母字符也一定不是变位词。
// 参数:
//         [const char *str1] --- 指向第1个单词的指针
//         [const char *str2] --- 指向第2个单词的指针
// 返回: [int]  --- 1表示是变位词，0表示不是变位词
// 作者: 耿楠
// 日期: 2018年12月07日
//-----------------------------------------------------------------------------------------------
int IsAnagramMaps(const char *str1, const char *str2)
{
    // 数据有效性检查
    if(str1 == NULL || str2 == NULL)
    {
        return 0;
    }

    //如果长度不等，则一定不是变位词
    if(strlen(str1) != strlen(str2))
    {
        return 0;
    }

    // 创建映射数组，元素下标为字母编号，数组值是该字母出现的次数
    unsigned char alphamaps[52] = { 0 };
    const char *p = str1; // 指向第1个字符串

    // 处理第1个字符串，创建映射数组
    while (*p != '\0')
    {
        if(*p >= 'A' && *p <= 'Z')
        {
            alphamaps[*p - 'A']++;  // 大写字母映射
        }
        else if(*p >= 'a' && *p <= 'z')
        {
            alphamaps[*p - 'a' + 26]++;// 小字字母映射
        }
        else
        {
            return 0; // 出现其它字母，则一定不是变位词
        }
        p++;
    }

    // 处理第2个字符串
    p = str2;
    while (*p != '\0')
    {
        if(*p >= 'A' && *p <= 'Z')
        {
            alphamaps[*p - 'A']--;  // 大写字母映射
        }
        else if(*p >= 'a' && *p <= 'z')
        {
            alphamaps[*p - 'a' + 26]--;// 小字字母映射
        }
        else
        {
            return 0; // 出现其它字母，则一定不是变位词
        }
        p++;
    }

    int i;
    for(i = 0; i < 52; i++)
    {
        if(alphamaps[i] != 0)
        {
            return 0; // 如果数组值不为0，代表两个字符串中出现的字母符不完全一致，不是变位词
        }
    }

    return 1;
}

//-----------------------------------------------------------------------------------------------
// 名称: int cmpalpha(const void *alph1, const void *alph2)
// 功能: 比较两个字符的大小
// 参数:
//         [const void *alph1] --- 指向第1个数据的指针
//         [const void *alph2] --- 指向第2个数据的指针
// 返回: [int]  --- 大于返回1，等于返回0，小于返回-1
// 作者: 耿楠
// 日期: 2018年12月07日
// 备注: 该函数是用于qsort快速排序的比较函数
//-----------------------------------------------------------------------------------------------
int cmpalpha(const void *alph1, const void *alph2)
{
    char ch1 = *(const char *)alph1;
    char ch2 = *(const char *)alph2;

    return (ch1 > ch2) - (ch1 < ch2);
}

//-----------------------------------------------------------------------------------------------
// 名称: int IsAnagrams(const char *str1, const char *str2)
// 功能: 检查两个单词是否为变位词(相同字母的重新排列)
// 算法: 由于组成变位词的字母是一模一样的，所以按照字典序排序后，
//          两个字符串是相等的。因此，可以先排序再判断两个字符串是不是相等即可。
// 注意: 如果两个字符串长度不相等，则一定不是变位词。
//          如果字符串中含有非字母字符也一定不是变位词。
// 参数:
//         [const char *str1] --- 指向第1个单词的指针
//         [const char *str2] --- 指向第2个单词的指针
// 返回: [int]  --- 1表示是变位词，0表示不是变位词
// 作者: 耿楠
// 日期: 2018年12月07日
//-----------------------------------------------------------------------------------------------
int IsAnagramSorted(const char *str1, const char *str2)
{
    // 数据有效性检查
    if(str1 == NULL || str2 == NULL)
    {
        return 0;
    }

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    //如果长度不等，则一定不是变位词
    if(len1 != len2)
    {
        return 0;
    }

    const char *p = str1; // 指向第1个字符串

    while (*p != '\0')
    {
        if(!((*p >= 'a' && *p <= 'z') ||  (*p >= 'A' && *p <= 'Z')))
        {
            return 0; // 出现其它字母，则一定不是变位词
        }
        p++;
    }

    // 第2个字符串
    p = str2;
    while (*p != '\0')
    {
        if(!((*p >= 'a' && *p <= 'z') ||  (*p >= 'A' && *p <= 'Z')))
        {
            return 0; // 出现其它字母，则一定不是变位词
        }
        p++;
    }

    // 复制字符串，以确保不改变原字符串
    char *s1 = (char*)malloc((len1 + 1) * sizeof(char));
    if(s1 == NULL)
    {
        return 0;
    }
    strcpy(s1, str1);

    char *s2 = (char*)malloc((len2 + 1) * sizeof(char));
    if(s2 == NULL)
    {
        return 0;
    }
    strcpy(s2, str2);

    // 调用qsort对字符串排序
    qsort(s1, len1, sizeof(s1[0]), cmpalpha);
    qsort(s2, len2, sizeof(s2[0]), cmpalpha);

    // 两个字符串相等是变位词，不相等则不是
    if(strcmp(s1, s2) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
