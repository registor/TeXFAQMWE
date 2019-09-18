// 遍历数组
void Traversal(StuNodePt pa, int n, void (*pf)(StuNodePt))
{
    StuNodePt p;

    // 遍历数组，使用指针进行操作
    for(p = pa; p < pa + n; p++)
    {
        pf(p); // 调用传入的函数
    }
}

// 输入数据
void Input(StuNodePt pData)
{
    // 输入一个节点的数据
    int id;
    char name[81], gender[15];
    int year, month, day;

    // 读入学号
    scanf("%d", &id);

    // 跳过剩下的其它字符及'\n'
    while(getchar() != '\n')
        ;

    // 读入字符串
    read_line(name, 80);
    read_line(gender, 15);

    // 读入日期数组
    scanf("%d%d%d", &year, &month, &day);

    // 给一个节点各成员赋值(字符串需要动态分配)
    InitNode(pData, id, name, gender, year, month, day);
}
// 输出数据
void Output(StuNodePt pData)
{
    // 输出一个节点的数据
    printf("%d\t%s\t%s\t%d/%d/%d\n", pData->ID, 
      pData->name, pData->gender, pData->birthday.year,
      pData->birthday.month, pData->birthday.day);
}
