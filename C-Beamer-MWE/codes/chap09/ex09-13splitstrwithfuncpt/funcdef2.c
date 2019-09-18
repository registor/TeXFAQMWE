//---------------------------------------------
// 名称：int IsDelimiter(char ch, char * deli)
// 功能：判断一个字符是否为分割字符
// 参数：
//       [char ch] --- 需要判断的字符
//       [char * deli] --- 分割字符构成的字符串
// 返回：int  --- 是返回1，否返回0
// 作者：耿楠
// 日期：2017年10月29日
//---------------------------------------------
int IsDelimiter(char ch, const char * deli)
{
    int result = 0;

    while(*deli)
    {
        if(ch == *deli)
        {
            result = 1;
            break;
        }
        deli++;
    }
    return result;
}
//-----------------------------------------------
// 名称：int IsNotDelimiter(char ch, char * deli)
// 功能：判断一个字符是否为分割字符
// 参数：
//       [char ch] --- 需要判断的字符
//       [char * deli] --- 分割字符构成的字符串
// 返回：int  --- 是返回0，否返回1
// 作者：耿楠
// 日期：2017年10月29日
//-----------------------------------------------
int IsNotDelimiter(char ch, const char * deli)
{
    return (!IsDelimiter(ch, deli));
}
//-----------------------------------------------------
// 名称：void HandleWord(const char* s, const char* e)
// 功能：对字符串中指定位置范围内的字符的处理函数
// 参数：
//       [const char* s] --- 起始位置指针
//       [const char* e] --- 结束位置指针
// 返回：void  --- 无
// 作者：耿楠
// 日期：2017年10月29日
//------------------------------------------------------
void HandleWord(const char* s, const char* e)
{
    int len = e - s; //字符串长度
    // 分配内存
    char *pstr = (char*)malloc(sizeof(char) * (len + 1));
    memcpy(pstr, s, len); // 复制字符串
    pstr[len] = '\0'; // 添加空字符
    puts(pstr); // 输出字符串
    free(pstr); // 释放空间
    pstr = NULL;
}
