// 该例说明如何在循环中使用sscanf的方法，
// 也就是scanf的%n格式串的作用。
// 详情参见：K.N. King 著, 吕秀锋 黄倩译. C语言程序设计:现代方法(第2版),
//                   北京:人民邮电出版社, 2013, PP: 398-299.
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char line[] = "100 185 400 11 1000"; // 数据字符串
    char *data = line; // 指向字符串的指针
    int offset; // 字符串偏移量
    int n; // 存储结果
    int sum = 0; // 累加和

    // 用sscanf的返回值控制循环
    // 用%n统计到目前为止读入的字符数量
    while (sscanf(data, " %d%n", &n, &offset) == 1)
    {
        sum += n; // 累加
        data += offset; // 字符串偏移
        printf("read: %5d; sum = %5d; offset = %5d\n", n, sum, offset);
    }

    printf("sum = %d\n", sum);
    return 0;
}
