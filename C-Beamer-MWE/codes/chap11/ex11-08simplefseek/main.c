/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示fseek、ftell函数的使用。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月12日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月13日
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int main(void)
{
    /* 定义一个数组A */
    double A[SIZE] = {1., 2., 3., 4., 5.};
    /* 写入文件 */
    FILE * fp = fopen("test.bin", "wb");
    fwrite(A, sizeof(double), SIZE, fp);
    fclose (fp);

    /* 读入数据到数组B */
    double B[SIZE];
    fp = fopen("test.bin", "rb");

    /* 将文件指针定位在第3个元素前 */
    if (fseek(fp, sizeof(double) * 2L, SEEK_SET) != 0)
    {
        if (ferror(fp))
        {
            perror("fseek()");
            fprintf(stderr, "fseek() failed in file %s at line # %d\n",
             __FILE__, __LINE__ - 5);  /* __FILE__是当前文件，__LINE__是当前行 */
            exit(EXIT_FAILURE);
        }
    }

    fread(B, sizeof(double), 1, fp); /* 读入一个浮点数  */
    printf("%.1f\n", B[0]);                /* 输出一个浮点数 */

    fclose(fp);
    return EXIT_SUCCESS;
}
