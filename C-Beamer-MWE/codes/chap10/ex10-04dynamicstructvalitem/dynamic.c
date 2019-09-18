...
int main(void)
{
    StuNodePt pst = NULL;
    // 创建对象
    CreateNode(&pst);
    ...
    // 释放内存
    DestroyNode(&pst);
    return 0;
}
...
void CreateNode(StuNodePt *pNode)
{
    // 动态分配内存
    (*pNode) = (StuNodePt)malloc(1 * sizeof(StuNode));
    // 成员赋值
    (*pNode)->ID = 101;
    // 为成员开避内存并赋值
    (*pNode)->name = (char *)malloc(
                (strlen("Alise") + 1) * sizeof(char));
    strcpy((*pNode)->name, "Alise");
    (*pNode)->gender = (char *)malloc(
                (strlen("female") + 1) * sizeof(char));
    strcpy((*pNode)->gender, "female");
    // 结构体成员赋值
    (*pNode)->birthday.year = 1998;
    (*pNode)->birthday.month = 10;
    (*pNode)->birthday.day = 23;
}

void DestroyNode(StuNodePt *pNode)
{
    // 释放内存
    free((*pNode)->name);
    (*pNode)->name = NULL;
    free((*pNode)->gender);
    (*pNode)->gender = NULL;
    free((*pNode));
    (*pNode) = NULL;
}
