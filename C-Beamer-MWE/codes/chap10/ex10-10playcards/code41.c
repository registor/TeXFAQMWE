// 功能：对一手牌进行排序
// 参数：
//       [Card** pDeck] --- 一手牌的指针数组
//       [int nCardCounts] --- 一手牌的张数
//       [pCmpFun pf] --- 比较函数的指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月05日
void SortDeck(Card** pDeck, int nCardCounts, pCmpFun pf)
{
    // 优化冒泡排序
    bool nFlag = true; // 交换标志

    for (int i = 0; i < nCardCounts - 1; ++i)
    {
        nFlag = true; // 每趟循环将标志置为真

        for (int j = 0; j < nCardCounts - 1 - i; ++j)
        {
            if (pf(pDeck[j], pDeck[j + 1]))
            {
                // 交换两个指针
                Card* pTemp = pDeck[j];
                pDeck[j] = pDeck[j + 1];
                pDeck[j + 1] = pTemp;
                nFlag = false; // 发生了交换，置假
            }
        }

        if (nFlag)
        {
            break; // 未发生交换，退出循环
        }
    }
}
