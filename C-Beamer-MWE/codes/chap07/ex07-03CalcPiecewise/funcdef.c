// 函数定义
int CalcPiece(int x)
{
    int result;

    if(x != 0)
    {
        if(x > 0)
        {
            result = 1;
        }
        else
        {
            result = -1;
        }
    }
    else
    {
        result = 0;
    }

    return result;
}
