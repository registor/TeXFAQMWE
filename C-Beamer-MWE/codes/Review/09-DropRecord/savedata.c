#include <stdio.h>
#include <string.h>
#include "savedata.h"
#include "genericlib.h"
#include "callback.h"

// 结果存储为文本文件
size_t saveDataTXT(const char *fname, Student **pst, size_t len)
{
    FILE *fp; // 文件指针

    size_t cnt = 0;

    fp = fopen(fname, "w");  // 文本写方式打开(未进行错误判断！)

    fprintf(fp, "%zd\n", len);

    while(*pst != NULL)
    {
        fprintf(fp, "%d %s %0.2f %0.2f %0.2f %0.2f %d\n",
                (*pst)->ID, (*pst)->name,
                (*pst)->grade[0], (*pst)->grade[1], (*pst)->grade[2],
                (*pst)->average, (*pst)->rank);
        pst++;
        cnt++;
    }

    fclose(fp);
    return cnt; // 返回写入的记录个数
}

// 结果存储为二进制文件
size_t saveDataBIN(const char *fname, Student **pst, size_t len)
{
    FILE *fp; // 文件指针
    size_t cnt = 0;

    fp = fopen(fname, "wb"); // 二进制写方式打开(未进行错误判断！)

    fwrite(&len, sizeof(size_t), 1, fp); // 写入记录个数

    while(*pst != NULL)
    {
        fwrite(*pst, sizeof(Student), 1, fp); // 写入一个结构体对象
        pst++;
        cnt++;
    }

    fclose(fp);
    return cnt;
}


// 查看写入的二进制数据是否正确
size_t checkDataBIN(const char *fname)
{
    Student **pst, **p;
    FILE *fp; // 文件指针
    size_t cnt = 0;
    size_t len = 0;

    long file_end;

    fp = fopen(fname, "rb"); // 二进制读方式打开(未进行错误判断！)

    fseek(fp, 0L, SEEK_END); // 移动到文件尾
    file_end = ftell(fp); // 获取文件尾位置
    rewind(fp); // 回到文件头

    fread(&len, sizeof(size_t), 1, fp); // 读入记录个数

    pst = malloc((len + 1) * sizeof(Student*)); // 申请指针数组
    memset(pst, 0, (len + 1) * sizeof(Student*)); // 清0

    p = pst;

    while(file_end != ftell(fp)) // 判断是不是文件尾(使用feof()会多读一次，有待分析)
    {
        *pst = malloc(sizeof(Student)); // 申请结构体内存
        memset(*pst, 0, sizeof(Student)); // 清0
        fread(*pst, sizeof(Student), 1, fp); // 读入一个结构体对象
        pst++;
        cnt++;
    }
    fclose(fp);

    printf("Saved binary result file is: \n");
    Traversal(p, cnt, sizeof(Student*), OutputStuPt);
    printf("\n");

    // 释放空间
    Traversal(p, cnt, sizeof(Student*), FreeStu);
    free(p);
    p = NULL;

    return cnt;
}
