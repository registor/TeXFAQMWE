// 功能：洗牌，也就是打乱一副牌的顺序
Card** ShuffleDeck(Card* pDeck, int n)
{
    // 分配保存洗牌结果的指针数组内存空间
    Card** pShuffleDeck = (Card**)malloc(n * sizeof(Card*));
    // 创建一个指向原始的每一张牌的指针数组作为过滤数组
    Card** pDeckItem = (Card**)malloc(n * sizeof(Card*));
    if(pShuffleDeck == NULL || pDeckItem == NULL){
        return NULL; // 分配内存失败，返回NULL指针
    }
    // 让pDeckItem每个元素指向原始的每一张牌
    for (int i = 0; i < n; ++i){
        pDeckItem[i] = &pDeck[i];
    }
    // 置随机种子
    srand(time(NULL));
    // 产生随机序号，并从pDeckItem中取出序号所指的项，
    // 依次加入到pShuffleDeck中
    for (int i = 0; i < n; ++i){
        unsigned int idx = rand() % n; // 生成[0, n)之间的随机数
        if (pDeckItem[idx] != NULL){
            // pDeckItem[idx]为NULL，说明这张牌没有被选过
            pShuffleDeck[i] = pDeckItem[idx]; // 选入到结果数组
            pDeckItem[idx] = NULL; // 置NULL表示已被选过，不可再选
        }
        else{
            --i; // 重新选这一张牌(非常重要的操作)
        }
    }
    free(pDeckItem); // 释放过渡指针数组内存空间
    //返回洗完牌后的数组
    return pShuffleDeck;
}
