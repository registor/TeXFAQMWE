//--------------------------------------
// 名称：long GetFileSize(FILE *stream)
// 功能：获得文件的大小(以字节为单位)
// 参数：
//           [FILE *stream] --- 文件指针
// 返回：[long]  --- 文件的大小(字节单位)
// 作者：耿楠
// 日期：2017年11月13日
//--------------------------------------
long GetFileSize(FILE *stream)
{
    long curpos, length; // long int类型

    curpos = ftell(stream); // 获取文件当前位置

    fseek(stream, 0L, SEEK_END); // 移动到文件尾

    length = ftell(stream); // 获取当前位置(长度)

    fseek(stream, curpos, SEEK_SET); // 恢复文件位置

    return length;
}
