#include <stdio.h>
#include <stdlib.h>
...
int main()
{
    ...
    // 把输入重定向到文件"data.txt"
    freopen("data.txt", "r", stdin);
    Traversal(iArray, N, Input);
    // 把输入重定向回键盘
    freopen("CON", "r", stdin);
    ...
    // 把输出重定向到文件"out.txt"
    freopen("out.txt","w",stdout);
    Traversal(iArray, N, Output);
    printf("\n");
    // 把输出重定向到控制台
    freopen("CON","w",stdout);
    ...
}
