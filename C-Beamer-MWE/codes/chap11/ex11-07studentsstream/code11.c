// 函数原型
bool CreateDataFile(StuNode *, int, const char*);
bool LoadFromDataFile(StuNode *, int, const char*);
void Traversal(StuNode *, int, FILE *, bool (*)(StuNode *, FILE *));
bool Input(StuNode *, FILE *); // 录入一个元素的数据
bool Output(StuNode *, FILE *); //  输出一个元素的数据
bool SaveItem(StuNode *, FILE *); // 写入一个数组元素到文件流
bool LoadItem(StuNode *, FILE *); // 从文件流读入一个数组元素数据

int main(int argc, char *argv[])
{
    StuNode stu[N];
    ...    
    Traversal(stu, N, stdin, Input);// 为数组读入数据

    // 按单个元素的方式读入数据到数组
    if(!CreateDataFile(stu, N, argv[1]))
    {
        fprintf(stderr, "somthing wrong!\n");
        exit(EXIT_FAILURE);
    }
    // 按单个元素的方式读入数据到数组
    if(!LoadFromDataFile(stu, N, argv[1]))
    {
        fprintf(stderr, "somthing wrong!\n");
        exit(EXIT_FAILURE);
    }

    Traversal(stu, N, stdout, Output); // 输出数据到stdout流
    return 0;
}
