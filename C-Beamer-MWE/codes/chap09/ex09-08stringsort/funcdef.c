// 交换两个字符串数组
void SwapString(char *s1, char *s2)
{
    char tempStr[8];
    strcpy(tempStr, s1);
    strcpy(s1, s2);
    strcpy(s2, tempStr);
}

// 采用冒泡排序对字符串数组排序
int StringBubbleSort(char str[][8], int n)
{
    int i = 0, j = 0;
    int counter = 0;

    for(i = 0; i < n - 1; i++ )
    {
        // j<n-1确保数据不越界
        // -i为了减少循环次数
        for(j = 0; j < n - 1 - i; j++)
        {
            if(strcmp(str[j], str[j + 1]) > 0) // 升序
            {
                SwapString(str[j], str[j + 1]);
            }
            counter++; //循环计数
        }
    }
    return counter;
}

