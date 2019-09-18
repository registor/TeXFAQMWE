// 输出
    Traversal(Stu, N, Output);
    printf("\n");
    // 修改ID
    Traversal(Stu, N, ModifyID);
    // 输出
    Traversal(Stu, N, Output);

    return 0;
}

// 函数定义
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

// 输出数据
void Output(StuNodePt pData)
{
    // 输出一个节点的数据
    printf("%d\t%s\t%s\t%d/%d/%d\n", pData->ID, pData->name,
           pData->gender, pData->birthday.year,
           pData->birthday.month, pData->birthday.day);
}

// 修改ID数据
void ModifyID(StuNodePt pData)
{
    pData->ID += 2017000;
}
