//---------------------------------------------------
// 名称：void SplitOnWords(const char* s, const char* e, 
//const char *pdeli, void (*pf)(const char*, const char*))
// 功能：在字符串的指定位置范围内按指定的字符分割字符串
// 参数：
//       [const char* s] --- 起始位置指针
//       [const char* e] --- 结束位置指针
//       [const char *pdeli] --- 指向分割字符串的指针
//       [void (*pf)(const char*, const char*)] -函数指针
// 返回：void  --- 无
// 作者：耿楠
// 日期：2017年10月29日
//-----------------------------------------------------
void SplitOnWords(const char* s, const char* e, 
   const char *pdeli,void (*pf)(const char*, const char*))
{
    const char* p = s;

    while( s != e )
    {
        //不可以想当然认为第1个字符不是分割符
        s = Find(s, e, pdeli, IsNotDelimiter);
        p = s;
        s = Find(s, e, pdeli, IsDelimiter);
        pf(p, s);
    }
}

//------------------------------------------------------
// 名称：const char* Find(const char* s, const char* e, 
//                 const char *pdeli, int (*pred)(char))
// 功能：在字符串的指定位置范围内查找是否存在指定的字符
// 参数：
//       [const char* s] --- 起始位置指针
//       [const char* e] --- 结束位置指针
//       [const char *pdeli] --- 指向分割字符串的指针
//       [int (*pred)(char)] --- 判断函数(返回0或非0)
// 返回：const char*  --- 返回找到字符的位置指针
// 作者：耿楠
// 日期：2017年10月29日
//--------------------------------------------------
const char* Find(const char* s, const char* e, 
    const char *pdeli, int (*pred)(char, const char *))
{
    // 在指定范围内找是不是有指定的字符
    while( s != e && !pred(*s, pdeli) )
    {
        ++s;
    }
    // 返回位置指针
    return s;
}
