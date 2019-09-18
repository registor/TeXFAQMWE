//--------------------------------------------------------
// 名称：void InitDeck(Card *pDeck, int n, bool jokerFlag)
// 功能：初始化一副牌，也就是给各个牌赋值
// 参数：
//       [Card *pDeck] --- 一副牌数组的指针
//       [int n] --- 一副牌的张数(不包括大小王两张)
//       [bool jokerFlag] --- 是否包括两张大小王牌
// 返回：无
// 作者：耿楠
// 日期：2017年11月05日
//--------------------------------------------------------
void InitDeck(Card *pDeck, int n, bool jokerFlag)
{
    //前52张
    int i = 0;

    // 按每个点数4张牌的顺序初始化
    for (i = 0; i < n; i++)
    {
        pDeck[i].face = i / 4 + 1; // 点数
        pDeck[i].suit = (enum Suit)(i % 4); // 花色
    }

    if(jokerFlag)
    {
        //剩下的大王和小王
        pDeck[i].face = i / 4 + 1;
        pDeck[i].suit = JOKER1;
        //大王
        pDeck[i + 1].face = i / 4 + 2;
        pDeck[i + 1].suit = JOKER2;
    }
}
