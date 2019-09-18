#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int AtoI(char []); // 字符串转整型
void ItoA (int , char []); // 整型数转字符串
int Str2Int(const char *); // 字符串转整型
void Int2Str(int , char *); // 字符串转整型

int main()
{
    printf("Hello world!\n");
    return 0;
}

int AtoI(char s[])
{
    int i, n, sign;
    for(i = 0; isspace(s[i]); i++) //跳过空白符;
    {
        sign = (s[i] == '-') ? -1 : 1;
    }
    if(s[i] == '+' || s[i] == '-') //跳过符号
    {
        i++;
    }

    for(n = 0; isdigit(s[i]); i++)
    {
        n = 10 * n + (s[i] - '0');   //将数字字符转换成整形数字
    }

    return sign * n;
}

void ItoA (int n, char s[])
{
    int i, j, sign;
    if((sign = n) < 0) //记录符号
    {
        n = -n;   //使n成为正数
    }
    i = 0;
    do
    {
        s[i++] = n % 10 + '0'; //取下一个数字
    }while ((n /= 10) > 0);  //删除该数字

    if(sign < 0)
    {
        s[i++] = '-';
    }
    s[i] = '\0';
    for(j = i; j >= 0; j--) //生成的数字是逆序的，所以要逆序输出
    {
        printf("%c", s[j]);
    }
}

int Str2Int(const char *str)
{
    int temp = 0;
    const char *ptr = str;  //ptr保存str字符串开头

    if (*str == '-' || *str == '+')  //如果第一个字符是正负号，
    {
        //则移到下一个字符
        str++;
    }
    while(*str != '\0')
    {
        if ((*str < '0') || (*str > '9'))  //如果当前字符不是数字
        {
            //则退出循环
            break;
        }
        temp = temp * 10 + (*str - '0'); //如果当前字符是数字则计算数值
        str++;      //移到下一个字符
    }
    if (*ptr == '-')     //如果字符串是以“-”开头，则转换成其相反数
    {
        temp = -temp;
    }

    return temp;
}

void Int2Str(int n, char *str)
{
    char buf[10] = "";
    int i = 0;
    int len = 0;
    int temp = n < 0 ? -n : n; // temp为n的绝对值

    if (str == NULL)
    {
        return;
    }
    while(temp)
    {
        buf[i++] = (temp % 10) + '0';  //把temp的每一位上的数存入buf
        temp = temp / 10;
    }

    len = n < 0 ? ++i : i; //如果n是负数，则多需要一位来存储负号
    str[i] = '\0';            //末尾是结束符0
    while(1)
    {
        i--;
        if (buf[len - i - 1] == 0)
        {
            break;
        }
        str[i] = buf[len - i - 1]; //把buf数组里的字符拷到字符串
    }
    if (i == 0 )
    {
        str[i] = '-';          //如果是负数，添加一个负号
    }
}
