...
// 学生结构体类型
struct StuInfo
{
    int ID;                   // 学号
    char *name;            // 姓名
} ;
// 与声明分开使用typedef
typedef struct StuInfo StuNode;

// 函数原型
bool InitNode(StuNode *, int, const char *);
bool CopyStu(StuNode * const, const StuNode *);
void DestroyNode(StuNode *);
void Output(const StuNode *);

int main(void)
{
    StuNode stu1 = {0}, stu2 = {0}; // 指针=NULL
    // 创建对象
    InitNode(&stu1, 101, "Alise");
    CopyStu(&stu2, &stu1);
    // 释放内存
    DestroyNode(&stu2);
    // name指向的内存已释放
    Output(&stu1); 
    DestroyNode(&stu1);
    return 0;
}
bool CopyStu(StuNode * const pTarget, const StuNode * pSource)
{
    ...
    if(pTarget->name != NULL)
    {
        free(pTarget->name); // 若已分配了内存空间，则需要先释放
    }
    // 分配内存
    pTarget->name=(char *)malloc((strlen(pSource->name)+1)*sizeof(char));
    ...
    // 复制字符串
    pTarget->ID = pSource->ID;
    strcpy(pTarget->name, pSource->name);
    return true;
}
