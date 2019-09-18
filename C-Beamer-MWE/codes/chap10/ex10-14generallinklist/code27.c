// 释放数据区
void stringFree(void *pData)
{
    free((char*)(pData));
}
void intFree(void *pData)
{
    free((int*)(pData));
}
void doubleFree(void *pData)
{
    free((double*)(pData));
}
void pointFree(void *pData)
{
    free((Point2D*)(pData));
}
