...
// 学生结构体类型
struct StuInfo
{
    int ID;                   // 学号
    char *name;            // 姓名
};
// 与声明分开使用typedef
typedef struct StuInfo StuNode;
// 函数原型
bool InitNode(StuNode *, int, const char *);
void DestroyNode(StuNode *);
void Output(const StuNode *);
int main(void)
{
    StuNode stu1, stu2;
    // 创建对象
    InitNode(&stu1, 101, "Alise");
    stu2 = stu1;
    // 释放内存
    DestroyNode(&stu2);
    // name指向的内存已释放
    Output(&stu1); 
    DestroyNode(&stu1);
    return 0;
}
bool InitNode(StuNode *pNode, int ID, const char *pname)
{
    ...
    // 为成员动态开避内存并赋值
    pNode->name = (char *)malloc((strlen(pname) + 1) * sizeof(char));
    ...
    // 动态内存赋值
    strcpy(pNode->name, pname);
    return true; // 返回真值
}
void DestroyNode(StuNode *pNode)
{
    // 释放内存
    free(pNode->name);
    pNode->name = NULL;
}
