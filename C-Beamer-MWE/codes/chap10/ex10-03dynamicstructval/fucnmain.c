...
// 构体类型
typedef struct
{
    int year;    // 年
    int month;  // 月
    int day;     // 日
} Date;
typedef struct
{
    int ID;                       // 学号
    char name[20];            // 姓名
    char gender[13];         // 性别
    Date birthday;  // 生日
} StuNode, *StuNodePt;

int main(void)
{
    StuNodePt pst = NULL;
    // 动态分配内存
    pst = (StuNodePt)malloc(1 * sizeof(StuNode));
    // 成员赋值
    pst->ID = 101;
    strcpy(pst->name, "Alise");
    strcpy(pst->gender, "female");
    pst->birthday.year = 1998;
    pst->birthday.month = 10;
    pst->birthday.day = 23;
    ...
    // 释放内存
    free(pst);
    pst = NULL
    return 0;
}
