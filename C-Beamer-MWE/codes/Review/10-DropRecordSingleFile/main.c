/**
现有两个文本文件，分别保存了一组学生的高考成绩，
不过两个文件中的数据中有些学生的信息是重复的。
请为每个同学计算高考平均成绩，并将学生信息去重合并后
按高考平均成绩从高到低的次序输出各学生的信息。

注：
请将结果分别按文本文件和二进制文件的形式保存。
**/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define NAMELEN 20
#define NGRADE 3

// 类型重定义
typedef struct
{
    unsigned int ID;
    char name[NAMELEN];
    double grade[NGRADE];
    double average;
    unsigned int rank;
} Student;
typedef void (*itemFuncType)(Student *);

// 函数原型
size_t Traversal(Student **, itemFuncType); // 遍历数组
void OutputStuPt(Student *);// 输出一个结构体的内容
void setAverage(Student *); // 设置一个学生成绩的平均值

//  qsort排序函数使用的比较函数
int cmpStuID(const void *, const void *); // 按学号比较两个结构体大小(>)
int cmpStuAvg(const void *, const void *); // 按平均成绩比较两个结构体大小(<)

// 读取数据(两种方式)
Student ** loadDataWithScanSet(const char *, const char *);
Student ** loadDataWithGets(const char *, const char *);

// 写入数据(文本和二进制格式)
size_t saveDataTXT(const char *, Student **, size_t);
size_t saveDataBIN(const char *, Student **, size_t);

// 检查二进制格式文件结果是否正确
size_t checkDataBIN(const char *);

size_t getDataSize(Student **); // 获取数据个数(元素个数)
size_t dropRecord(Student**, size_t); // 删除重复的记录
void setAvgRank(Student **); // 设置排名
void Destroy(Student **pst);// 销毁内存

void run(); // 启动程序

// 主函数(驱动程序)
int main(void)
{
    run();

    return 0;
}

// 启动程序
void run()
{
    Student **pData = NULL;

    size_t datasize = 0;

    //pData = loadDataWithScanSet("recode1.dat", "recode2.dat"); // 通过%[^0-9]扫描字符集方式读入数据
    pData = loadDataWithGets("recode1.dat", "recode2.dat"); // 通过分割字符串方式读入数据

    datasize = getDataSize(pData);
    printf("Original data is: \n");
    Traversal(pData, OutputStuPt);
    printf("\n");

    datasize = dropRecord(pData, datasize);

    Traversal(pData, setAverage); // 计算平均成绩

    qsort(pData, datasize, sizeof(Student*), cmpStuAvg); // 使用qsort按平均成绩排序
    setAvgRank(pData); // 设置排名

    printf("Sort and drop duplicate record is: \n");
    Traversal(pData, OutputStuPt);
    printf("\n");

    saveDataTXT("resulttxt.dat", pData, datasize);
    saveDataBIN("resultbin.dat", pData, datasize);

    checkDataBIN("resultbin.dat");
    Destroy(pData);
}

// 遍历指针数组(用元素值是否为NULL结束循环)
// itemFuncType pf为处理元素的函数指针
size_t Traversal(Student **p, itemFuncType pf)
{
    int cnt = 0; // 元素个数计数

    while(*p != NULL)
    {
        pf(*p); // 将遍历到的数据传入操作函数
        p++;
        cnt++;
    }

    return cnt; // 返回处理的元素个数
}

// 输出一个结构体的内容
void OutputStuPt(Student * p)
{
    // 输出
    printf("%d %s %0.2f %0.2f %0.2f %0.2f %d\n", p->ID, p->name,
           p->grade[0],
           p->grade[1],
           p->grade[2],
           p->average,
           p->rank
          );
}

// 释放一个结构体占有的内存
void freeStu(Student * p)
{
    // 释放
    free(p);
}

// 设置一个学生成绩的平均值
void setAverage(Student *p)
{
    p->average = 0.0;
    for(int i = 0; i < NGRADE; i++)
    {
        p->average += p->grade[i]; // 求和
    }
    p->average /= NGRADE; // 求平均值
}

// 用于根据学号比较两个结构体大小的比较函数(升序)
// (采用指针数组方式存储数据，比较的是学号，调整的是指针的指向)
int cmpStuID(const void *s1, const void *s2)
{
    // 强制类型转换
    Student * p1 = *((Student **)s1);
    Student * p2 = *((Student **)s2);

    // 按学号比较(返回1、0、-1)
    return ((p1->ID > p2->ID) - (p1->ID < p2->ID));
}

// 用于根据平均成绩比较两个结构体大小的比较函数(降序)
// (采用指针数组方式存储数据，比较的是平均成绩，调整的是指针的指向)
int cmpStuAvg(const void *s1, const void *s2)
{
    // 强制类型转换
    Student * p1 = *((Student **)s1);
    Student * p2 = *((Student **)s2);

    // 按学号比较(返回1、0、-1)
    return ((p1->average < p2->average) - (p1->average > p2->average));
}

// 销毁内存
void Destroy(Student **p)
{
    Traversal(p, freeStu);
    free(p); // 释放指针数组
}

// 获取动态指针数组的长度
size_t getDataSize(Student **p)
{
    size_t len = 0;

    while(*p != NULL) // 通过指针数组最后一个多出的NULL结束循环
    {
        len++;
        p++;
    }

    return len; // 数据长度
}

// 设置排名(要求已排序)
void setAvgRank(Student **p)
{
    unsigned int r = 1; // 排名
    while(*p != NULL)
    {
        (*p)->rank = r; // 排名

        p++;
        r++;
    }
}

// 删除字符串起始与结尾空白
void trimWhitespace(char * s)
{
    char * p = s;
    int l = strlen(p); // 字符串长度

    while(isspace(p[l - 1])) // 是空白字符
    {
        p[--l] = 0; // 赋为'\0'，长度减1
    }

    while(* p && isspace(* p)) // 是空白字符
    {
        ++p; // 调整指针
        --l; // 长度减1
    }

    memmove(s, p, l + 1); // 数据移动到起始地址
}

// 利用scanf的扫描字符集读入带有空白的字符串
// 详情参见：K.N. King 著, 吕秀锋 黄倩译. C语言程序设计:现代方法(第2版), 北京:人民邮电出版社, 2013, PP: 400-401.
void scanDataWithSet(const char *strin, unsigned int *pID, char *name, double *pgrade)
{
    int offset = 0;

    // %[^0-9]用于读到发现数字为止
    // %n用于统计到目前为止读入的字符数量
    sscanf(strin, "%d %[^0-9]%n", pID, name, &offset);

    strin += offset;
    for(int i = 0; i < NGRADE; i++)
    {
        // sscanf返回值用于检测是否正常读入了1个数。
        if(sscanf(strin, " %lf%n", pgrade + i, &offset) != 1)
        {
            break;
        }
        strin += offset; // 调整字符串指针
    }
    // %[^0-9]用于读到发现数字为止
//    sscanf(strin, "%d %[^0-9] %lf %lf %lf", pID, name,
//           &pgrade[0], &pgrade[1], &pgrade[2]); // 未能处理NGRADE个数据的情况

    // 清除姓名字符串开始和结束空白符
    trimWhitespace(name);
}

// 找到需要读取的字符串的起始和结束地址，然后读入
// 注意：本函数只能读入前导和后继为数字的1个字符串
void scanDataWithStr(char *strin, unsigned int *pID, char *name, double *pgrade)
{
    char *pstart = NULL, *pend = NULL; // 字符串起始结束指针

    char *p = strin;

    while(*p != '\0') // 扫描字符串
    {
        if(*(p + 2) != '\0')
        {
            if(isdigit(*p) && isspace(*(p + 1))) // 前导是数字，当前是空白
            {
                pstart = p + 2; // 字符串起始地址
                p++;
                continue;
            }
        }

        if(*(p + 1) != '\0')
        {
            if(isspace(*p) && isdigit(*(p + 1))) // 当前是空白， 后继是数字
            {
                pend = p; // 字符串结束地址
                break; // 只处理一个字符串
            }
        }
        p++;
    }

    if(pstart != NULL && pend != NULL) // 找到字符串
    {
        *(pstart - 1) = '\0'; // 置'\0'，目的是分割为3节字符串
        *pend = '\0';
    }

    sscanf(strin, "%d", pID); // 读入学号
    strcpy(name, pstart); // 读入字符串(只处理1个字符串)
    trimWhitespace(name); // 清除开始和结束空白符

    int offset = 0;
    pend++;

    for(int i = 0; i < NGRADE; i++)
    {
        // %n用于统计到目前为止读入的字符数量
        // sscanf返回值用于检测是否正常读入了1个数。
        if(sscanf(pend, " %lf%n", pgrade + i, &offset) != 1)
        {
            break;
        }
        pend += offset; // 调整字符串指针
    }

//    int idx = 0; //
//    while(sscanf(pend, " %lf%n", pgrade + idx, &offset) == 1)
//    {
//        idx++;
//        pend += offset;
//    }

    //sscanf(pend + 1, "%lf %lf %lf", &pgrade[0], &pgrade[1], &pgrade[2]); // 读入其它数据（未能处理NGRADE个数据的情况）
}

// 按扫描字符集方式读入数据
Student ** loadDataWithScanSet(const char *fname1, const char *fname2)
{
    FILE *fp1, *fp2; // 文件指针

    Student **pst, **p;

    char buffer[1024]; // 字符串缓冲区

    fp1 = fopen(fname1, "r"); // 打开文件(注意没有处理错误！)
    fp2 = fopen(fname2, "r");

    int l1;
    int l2;
    int length;

    fscanf(fp1, "%d", &l1); // 第1个文件中记录的个数
    fgets(buffer, sizeof(buffer), fp1); // 跳过'\n'

    fscanf(fp2, "%d", &l2); // 第2个文件中记录的个数
    fgets(buffer, sizeof(buffer), fp2); // 跳过'\n'

    length = l1 + l2; // 总计记录个数

    pst = malloc((length + 1) * sizeof(Student*)); // 申请指针数组内存(多申请1个，为了用NULL结束循环)
    memset(pst, 0, (length + 1) * sizeof(Student*)); // 清0(NULL)

    p = pst;
    for(int i = 0; i < l1; i++)
    {
        fgets(buffer, sizeof(buffer), fp1); // 读入一行字符串
        p[i] = malloc(sizeof(Student)); // 申请1个结构体空间
        memset(p[i], 0, sizeof(Student)); // 清0

        scanDataWithSet(buffer, &p[i]->ID, p[i]->name, p[i]->grade); // 读入数据
    }

    p = pst + l1; // 另一组数据
    for(int i = 0; i < l2; i++)
    {
        fgets(buffer, sizeof(buffer), fp2); // 读入一行字符串
        p[i] = malloc(sizeof(Student)); // 申请1个结构体空间
        memset(p[i], 0, sizeof(Student)); // 清0

        scanDataWithSet(buffer, &p[i]->ID, p[i]->name, p[i]->grade); // 读入数据
    }

    // 关闭文件
    fclose(fp1);
    fclose(fp2);

    return pst; // 返回指针
}

// 在字符串中通过扫描找到姓名字段的开始和结束指针
// 然后用'\0'分割为3个子字符串，再读入数据
Student ** loadDataWithGets(const char *fname1, const char *fname2)
{
    FILE *fp1, *fp2; // 文件指针

    Student **pst, **p;

    char buffer[1024]; // 字符串缓冲区

    fp1 = fopen(fname1, "r"); // 打开文件(注意没有处理错误！)
    fp2 = fopen(fname2, "r");

    int l1;
    int l2;
    int length;

    fscanf(fp1, "%d", &l1); // // 第1个文件中记录的个数
    fgets(buffer, sizeof(buffer), fp1); // 跳过'\n'
    fscanf(fp2, "%d", &l2); // 第2个文件中记录的个数
    fgets(buffer, sizeof(buffer), fp2); // 跳过'\n'

    length = l1 + l2; // 记录总个数

    pst = malloc((length + 1) * sizeof(Student*)); // 申请指针数组(多申请1个，为了用NULL结束循环)
    memset(pst, 0, (length + 1) * sizeof(Student*)); // 清0

    p = pst;
    for(int i = 0; i < l1; i++)
    {
        fgets(buffer, sizeof(buffer), fp1); // 读入一行字符串
        p[i] = malloc(sizeof(Student)); // 申请1个结构体空间
        memset(p[i], 0, sizeof(Student)); // 清0

        scanDataWithStr(buffer, &p[i]->ID, p[i]->name, p[i]->grade); // 读入数据
    }

    p = pst + l1; // 另一级数据
    for(int i = 0; i < l2; i++)
    {
        fgets(buffer, sizeof(buffer), fp2);  // 读入一行字符串
        p[i] = malloc(sizeof(Student)); // 申请1个结构体空间
        memset(p[i], 0, sizeof(Student)); // 清0

        scanDataWithStr(buffer, &p[i]->ID, p[i]->name, p[i]->grade); // 读入数据
    }

    //  关闭文件
    fclose(fp1);
    fclose(fp2);

    return pst; // 返回指针
}

// 删除重复记录
size_t  dropRecord(Student**pData, size_t len)
{
    size_t datasize = len;

    qsort(pData, len, sizeof(Student*), cmpStuID); // 使用qsort函数按ID排序

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
                pData[datasize - 1] = NULL; // 最后一个赋为NULL(不能释放内存)
                datasize--;
            }
            else
            {
                j++; //当没有重复的时候才++
            }
        }
    }

    return datasize;
}

// 将结果存储为文本文件
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

// 读入存储的二进制文件中的数据，查看是否正确
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

    // 判断是不是文件尾
    // 注意：如果用feof()，则会多读一次，因为只有读一次文件尾才能得到EOF
    while(file_end != ftell(fp))
    {
        *pst = malloc(sizeof(Student)); // 申请结构体内存
        memset(*pst, 0, sizeof(Student)); // 清0
        fread(*pst, sizeof(Student), 1, fp); // 读入一个结构体对象
        pst++;
        cnt++;
    }
    fclose(fp);

    printf("Saved binary result file is: \n");
    Traversal(p, OutputStuPt);
    printf("\n");

    // 释放内存
    Traversal(p, freeStu);
    free(p);

    return cnt;
}
