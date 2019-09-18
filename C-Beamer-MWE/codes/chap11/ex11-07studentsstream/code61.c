//-----------------------------------------------------------------------------
// 名称：void Traversal(StuNode *pa, int n, FILE *stream, bool (*pf)(StuNode *))
// 功能：遍历结构体数组
// 参数：
//           [StuNode *pa] --- 结构体数组指针
//           [int n] --- 数组长度
//           [FILE *stream] --- 文件流指针
//           [bool (*pf)(StuNode *] --- 处理每个单元的函数指针
// 返回：[void]  --- 无
// 作者：耿楠
// 日期：2017年11月13日
//-----------------------------------------------------------------------------
void Traversal(StuNode *pa, int n, FILE *stream, bool (*pf)(StuNode *, FILE *))
{
    StuNode *p;

    // 遍历数组，使用指针进行操作
    for(p = pa; p < pa + n; p++)
    {
        pf(p, stream); // 调用传入的函数处理每个元素
    }
}
