#include <stdio.h>
#include <stdlib.h>

struct StuNode
{
    int ID;
    char name[20];
    char gender[12];
    int age;
};

int main()
{
    struct StuNode stu01;                                          /*声明变量*/
    struct StuNode stu02 = {102, "Tom", "male", 35}; /*声明变量*/
    struct StuNode *pStu;                                          /*声明指针*/

    return 0;
}
