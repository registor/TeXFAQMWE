//-----------------------------------------------------------------------
// 功能：从数据文件读入数据到数组中
// 参数：
//           [StuNode *pstu] --- 数组指针
//           [int n] --- 数组长度
//           [const char *filename] --- 数据文件文件名
// 返回：[bool]  --- 成功返回true，失败返回false
//------------------------------------------------------------------------
bool LoadFromDataFile(StuNode *pstu, int n, const char *filename)
{
    int count;
    FILE *fp;

    // 打开文件，二进制文件的追加模式
    if((fp = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", filename);
        return false; //打开文件失败
    }

    // 一次读入所有数据
    count = fread(pstu, sizeof(pstu[0]), n, fp);
    if(count != n) // 读入数据出错
    {
        fclose(fp);
        return false;
    }
    fclose(fp); // 关闭文件
    return true;
}
