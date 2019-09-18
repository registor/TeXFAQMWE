// 函数定义
// 遍历数组
void Traversal(struct student *pa, int n, 
            void (*pf)(struct student *))
{
    struct student *p;

    // 遍历数组，使用指针进行操作
    for(p = pa; p < pa + n; p++)
    {
        pf(p); // 调用传入的函数
    }
}

// 输入数据
void Input(struct student * pData)
{
    scanf("%d", &pData->id);
    scanf(" "); /* 清理输入缓冲区 */
    gets(pData->name);
    scanf(" ");
    gets(pData->gender);
    scanf(" ");
    scanf("%d", &pData->age);
}

// 输出数据
void Output(struct student * pData)
{
    // 输出
    printf("%d, %s, %s, %d\n",
           pData->id, pData->name,
           pData->gender, pData->age);
}
