// 输出函数
void stringOutput(const void *pData)
{
    printf("%s\n", (char*)(pData));
}
void intOutput(const void *pData)
{
    printf("%d ", *(int*)(pData));
}
void doubleOutput(const void *pData)
{
    printf("%.4f ", *(double*)(pData));
}
void pointOutput(const void *pData)
{
    printf("(%d, %d) ", ((Point2D*)pData)->x, 
                       ((Point2D*)pData)->y);
}
