/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示采用多文件结构实现泛型程序设计。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月28日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月19日
------------------------------------------------------------------------------------*/
#include <time.h>
#include <genericlib.h>

#include "callback.h"
#include "test.h"

int main()
{
    // 置随机种子， 只需要执行1次，不必要在每个函数中都执行
    srand(time(NULL));

    //testIntSort();
    //testDfSort();

    //testStringSort();
    //testStringPtSort();
    testStuSort();

    return 0;
}
