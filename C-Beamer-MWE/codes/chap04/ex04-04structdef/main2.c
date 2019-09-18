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
    struct StuNode stu01;
    struct StuNode stu02 = 
      {102, "Tom", "male", 35};

    struct StuNode *pStu; 

    return 0;
}
