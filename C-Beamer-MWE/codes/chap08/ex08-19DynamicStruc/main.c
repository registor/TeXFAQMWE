/*动态分配结构体内存*/
#include <stdio.h>
#include <stdlib.h>

/*结构体声明*/
struct student
{
    int id; /* 学号 */
    char name[20]; /* 姓名 */
    char gender[12]; /* 性别 */
    int age; /* 年龄 */
};

int main(void)
{
    struct student *pstd;

    /*分配内存*/
    pstd = (struct student*)malloc(1 * sizeof(struct student));
    if(pstd == NULL)
    {
        printf("Not Enough Memory, Exiting... \n");
        return 0;
    }

    /*使用内存*/
    scanf("%d", &pstd->id);
    scanf(" "); /* 清理输入缓冲区 */
    gets(pstd->name);
    scanf(" ");
    gets(pstd->gender);
    scanf(" ");
    scanf("%d", &pstd->age);

    printf("ID: %d, Name: %s, Gender: %s, Age: %d\n",
           pstd->id, pstd->name, pstd->gender, pstd->age);

    // 释放内存
    free(pstd);

    return 0;
}
