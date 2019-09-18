//--------------------------------------------------------------------
// 名称：bool CreateDataFile(StuNode *pa, int n, const char *filename)
// 功能：创建数据文件
// 参数：
//           [StuNode *pa] --- 结构体数组指针
//           [int n] --- 数组长度
//           [const char *filename] --- 数据文件文件名
// 返回：[bool]  --- 成功返回true，失败返回false
//--------------------------------------------------------------------
bool CreateDataFile(StuNode *pa, int n, const char *filename)
{
    FILE *fp; // 声明文件指针

    // 打开文件，二进制文件模式
    if((fp = fopen(filename, "wb")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", filename);
        return false; //打开文件失败
    }

    Traversal(pa, n, fp, SaveItem);

    fclose(fp); // 关闭文件
    return true;
}
