// 函数原型
// 按整个数组的方式创建数据文件
bool CreateDataFile(const char*);
// 从数据文件中1次性读入数据到数组中
bool LoadFromDataFile(StuNode *, int, const char*);
// 数组遍历，注意函数指针的使用
void Traversal(StuNode *, int, void (*)(StuNode *));
// 功能函数
void Input(StuNode *); // 录入一个元素的数据
void Output(StuNode *); //  输出一个元素的数据

int main(int argc, char *argv[])
{
    StuNode stu[N];
    ....
    // 按整个数组的方式创建数据文件
    if(!CreateDataFile(argv[1]))
    {
        fprintf(stderr, "somthing wrong!\n");
        exit(EXIT_FAILURE);
    }

    // 按整个数组的方式读入数据到数组
    if(!LoadFromDataFile(stu, N, argv[1]))
    {
        fprintf(stderr, "somthing wrong!\n");
        exit(EXIT_FAILURE);
    }

    Traversal(stu, N, Output); // 输出数据
    return 0;
}
