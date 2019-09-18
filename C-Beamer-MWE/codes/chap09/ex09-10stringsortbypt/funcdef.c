// 交换两个字符串数组
void SwapAddr(char **p1, char **p2)
{
    char *pt;
    pt = *p1;
    *p1 = *p2;
    *p2 = pt;
}

// 采用冒泡排序对字符串数组排序
int StringBubbleSort(char **str, int n)
{
    int i = 0, j = 0;
    int counter = 0;

    for(i = 0; i < n - 1; i++ )
    {
        // j<n-1确保数据不越界
        // -i为了减少循环次数
        for(j = 0; j < n - 1 - i; j++)
        {
            if(strcmp(str[j], str[j + 1]) > 0)
            {
                // 交换指向两个字符串的指针
                SwapAddr(&str[j], &str[j + 1]);
            }
            counter++; //循环计数
        }
    }
    return counter;
}
