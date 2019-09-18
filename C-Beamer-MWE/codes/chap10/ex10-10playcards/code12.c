int main(void)
{
    // 声明一副牌
    Card deck[CARD_COUNT];
    // 初始化一副牌
    InitDeck(deck, CARD_COUNT - 2, true);

    // 洗牌，pShuffledDeck是洗过的牌的指针数组的首地址
    Card ** pShuffledDeck = ShuffleDeck(deck, CARD_COUNT);

    // 创建玩家指针数组
    Player ** pPlayers = CreatePlayers(PLAYER_COUNT);
    // 发牌
    DispatchDeck(pPlayers, PLAYER_COUNT, pShuffledDeck, CARD_COUNT);
    // 发牌后，洗牌用的指针数组可以释放
    free(pShuffledDeck);
    pShuffledDeck = NULL; // 防止野指针

    // 打印玩家手中的牌
    PrintPlayerDeck(pPlayers, PLAYER_COUNT);

    // 释放空间
    DestroyPlayers(pPlayers, PLAYER_COUNT);
    free(pPlayers);
    pPlayers = NULL;

    return 0;
}
