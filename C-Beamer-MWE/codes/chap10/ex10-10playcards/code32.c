// 功能：发牌，顺序将洗好的牌发给各个玩家
bool DispatchDeck(Player** pPlayers, int nPlayerCounts, 
                  Card** pShuffledDeck, int n)
{
    // 计算每个玩家手中牌的容量
    // 剩下的底牌不作处理
    int cardNums = n / nPlayerCounts;
    int cardOvers = n % nPlayerCounts; // 底牌数量

    // 为每个玩家持牌数组分配空间
    for (int i = 0; i < nPlayerCounts; i++)
    {
        // 分配指针数组
        Card** pPlayerDeck = (Card**)malloc(cardNums
                              * sizeof(Card*));
        if(pPlayerDeck == NULL)
        {
            return false; // 分配内存失败返回false
        }
        pPlayers[i]->deck = pPlayerDeck;
    }

    // 轮流发牌(不发底牌)
    for (int i = 0; i < n - cardOvers; ++i)
    {
        // 取当前玩家
        Player* pCurPlayer = pPlayers[i % nPlayerCounts];
        // 向玩家发牌
        pCurPlayer->deck[pCurPlayer->counts] = pShuffledDeck[i];
        //玩家手中实际的牌数增加
        pCurPlayer->counts++;
    }

    return true;
}
