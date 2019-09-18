// 功能：在流上输出一个结构体变量的数据
bool Output(StuNode * pData, FILE *stream)
{
    // 输出一个结构体变量的数据
    fprintf(stream, "%d\t%s\t%s\t%d/%d/%d\n", pData->ID, pData->name,
            pData->gender, pData->birthday.year,
            pData->birthday.month, pData->birthday.day);

    return true;
}
// 功能：从流中读入数据到结构体变量
bool Input(StuNode *pData, FILE *stream)
{
    memset(pData, 0, sizeof(*pData));  // 数据清0

    fscanf(stream, "%d", &pData->ID);
    fscanf(stream, "%*[^\n]"); // 清空前一次scanf留下的内容，不处理'\n'
    fscanf(stream, "%*c"); // 清空前一次scanf留下的'\n'
    fscanf(stream, "%[^\n]\n", pData->name); // 读入字符串(可读入除\n外的字符)
    fscanf(stream, "%[^\n]\n", pData->gender); // 读入字符串(可读入除\n外的字符)
    fscanf(stream, "%d", &pData->birthday.year);
    fscanf(stream, "%d", &pData->birthday.month);
    fscanf(stream, "%d", &pData->birthday.day);

    return true;
}
