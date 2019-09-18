//------------------------------------------------
// 功能：创建数据文件
// 参数：
//           [const char *filename] --- 数据文件文件名
// 返回：[bool]  --- 成功返回true，失败返回false
//------------------------------------------------
bool CreateDataFile(const char *filename)
{
    StuNode stu[N];
    FILE *fp;
    int count;

    // 打开文件，二进制文件的追加模式
    if((fp = fopen(filename, "wb")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", filename);
        return false; //打开文件失败
    }

    Traversal(stu, N, Input); // 录入各数组成员数据

    count = fwrite(stu, sizeof(stu[0]), N, fp); // 写入文件
    if(count != N) // 写入出错
    {
        fclose(fp);
        return false;
    }
    fclose(fp); // 关闭文件
    return true;
}
