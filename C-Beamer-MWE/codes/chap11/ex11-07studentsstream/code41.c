// 功能：从流中读入数据到结构体变量
bool SaveItem(StuNode *pa, FILE *stream)
{
    int count;
    count = fwrite(pa, sizeof(*pa), 1, stream);

    if(count != 1)
    {
        return false;
    }

    return true;
}
// 名称：bool LoadItem(StuNode *pa, FILE *stream)
bool LoadItem(StuNode *pa, FILE *stream)
{
    int count;
    count = fread(pa, sizeof(*pa), 1, stream);

    if(count != 1)
    {
        return false;
    }

    return true;
}
