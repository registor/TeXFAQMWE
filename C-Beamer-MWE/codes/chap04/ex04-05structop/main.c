#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    pStu = &stu01;

    stu01.ID = 101;
    strcpy(stu01.name, "Alise");
    strcpy(pStu->gender, "female");
    pStu->age = 25;

    pStu = &stu02;

    printf("ID\tName\tGender\tAge\n");
    printf("%d\t%s\t%s\t%d\n", stu01.ID,
           stu01.name, stu01.gender, stu01.age);
    printf("%d\t%s\t%s\t%d\n", pStu->ID,
           pStu->name, pStu->gender, pStu->age);

    return 0;
}
