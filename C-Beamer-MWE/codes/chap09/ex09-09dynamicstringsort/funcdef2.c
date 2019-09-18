

// 读入一行字符
int read_line(char str[], int n)
{
    int ch, i = 0;

    // 读入字符，直到遇到换行符
    while ((ch = getchar()) != '\n')
    {
        if(i < n) /* 最大字符数 */
        {
            str[i++] = ch;
        }
    }
    str[i] = '\0'; /* 添加空字符'\0' */

    return i;    /* 返回读入的字符数 */
}

// 交换两个字符串数组
void SwapString(char *s1, char *s2)
{
    char tempStr[STR_LEN + 1];
    strcpy(tempStr, s1);
    strcpy(s1, s2);
    strcpy(s2, tempStr);
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
            if(strcmp(str[j], str[j + 1]) > 0) // 升序
            {
                SwapString(str[j], str[j + 1]);
            }
            counter++; //循环计数
        }
    }
    return counter;
}
