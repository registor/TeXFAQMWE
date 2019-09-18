#include <stdio.h>
#include <stdlib.h>

/*定义结构体类型*/
struct StuInfo
{
    int ID; //学号
    char name[21]; //姓名
    double c_score; //C语言成绩
};

/*计算学生的平均成绩*/
double AvgStu(struct StuInfo st1, struct StuInfo st2)
{
    return (st1.c_score + st2.c_score) / 2.0;
}

/*主函数*/
int main()
{
    struct StuInfo st1 = {101, "Tom", 90.5}, st2 = {102, "Jerry", 64.0};

    printf("The average score is %f\n", AvgStu(st1, st2)); //函数调用
    return 0;
}
