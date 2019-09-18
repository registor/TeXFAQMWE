#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "define.h"
#include "genericlib.h"
#include "callback.h"
#include "loaddata.h"
#include "droprecord.h"
#include "savedata.h"

// 销毁内存(只在本文件中使用，用static限定)
static void Destroy(Student **pst, size_t len)
{
    Traversal(pst, len, sizeof(Student*), FreeStu); // 遍历数组，释放各个元素
    free(pst); // 释放指针数组
    pst = NULL;
}

// 获取动态指针数组的长度
size_t getDataSize(Student **pst)
{
    size_t length = 0;

    while(*pst != NULL) // 通过指针数组最后一个多出的NULL结束循环
    {
        length++;
        pst++;
    }

    return length;
}

// 设置一个学生成绩的平均值(只在本文件中使用，用static限定)
static void setAverage(void * pData)
{
    // 强制转换指针类型
    Student *p = *((Student **)pData);

    p->average = 0.0;
    for(int i = 0; i < NGRADE; i++)
    {
        p->average += p->grade[i]; // 求和
    }
    p->average /= NGRADE; // 求平均值
}

// 设置排名(要求已排序，只在本文件中使用，用static限定)
static void setAvgRank(Student **p)
{
    unsigned int r = 1; // 排名
    while(*p != NULL)
    {
        (*p)->rank = r; // 排名

        p++;
        r++;
    }
}

void run()
{
    Student **pData = NULL;

    size_t datasize = 0;

    pData = loadDataWithScanSet("recode1.dat", "recode2.dat");// 通过%[^0-9]扫描字符集读入数据
    //pData = loadDataWithGets("recode1.dat", "recode2.dat");// 通过分割字符串读入数据

    datasize = getDataSize(pData);
    printf("Original data is: \n");
    Traversal(pData, datasize, sizeof(Student*), OutputStuPt);
    printf("\n");

    datasize = dropRecord(pData, datasize);

    Traversal(pData, datasize, sizeof(Student*), setAverage); // 计算平均成绩

    GenericInsertSort(pData, datasize, sizeof(Student*), cmpStuAvg); // 使用GenericInsertSort按平均成绩排序

    setAvgRank(pData); // 设置排名

    printf("Sort and drop duplicate record is: \n");
    Traversal(pData, datasize, sizeof(Student*), OutputStuPt);
    printf("\n");

    saveDataTXT("resulttxt.dat", pData, datasize);
    saveDataBIN("resultbin.dat", pData, datasize);

    checkDataBIN("resultbin.dat");
    Destroy(pData, datasize);

}

// 删除重复记录
size_t  dropRecord(Student**pData, size_t len)
{
    size_t datasize = len;

    GenericBubbleSort(pData, len, sizeof(Student*), cmpStuID); // 排序

    // 使用两层for循环嵌套，对数组遍历：
    for(int i = 0; i < datasize - 1; i++)
    {
        // 注意：此时第三个表达式空出，因为当找到重复的数据，
        // 后面的数往前覆盖之后，应该再进行一次对比
        for(int j  = i + 1; j < datasize;)
        {
            if(pData[i]->ID == pData[j]->ID) // 判断如果出现相同数据
            {
                free(pData[j]); // 释放内存
                memmove(pData + j, pData + j + 1, (datasize - 1 - j) * sizeof(Student*)); // 则将后面的数据往前移一位
                pData[datasize - 1] = NULL; // 剩下的指针赋为NULL，不能释放内存
                datasize--;
            }
            else
            {
                j++; // 当没有重复的时候才++
            }
        }
    }

    return datasize;
}

