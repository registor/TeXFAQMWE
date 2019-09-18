// 功能：比较函数1：先比较点数再比较花色(升序)
int Greater(Card* pCard1, Card* pCard2)
{
    if (pCard1->face > pCard2->face){
        return 1; // 点数大，返回1
    }
    else if (pCard1->face < pCard2->face){
        return 0; // 点数小，返回0
    }
    else{
        if (pCard1->suit > pCard2->suit){
            return 1; //  花色大，返回1
        }
        else{
            return 0; // 花色小，返回0
        }
    }
}
// 功能：比较函数1：先比较点数再比较花色(降序)
int Lesser(Card* pCard1, Card* pCard2)
{
    if (pCard1->face < pCard2->face){
        return 1; // 点数小，返回1
    }
    else if (pCard1->face > pCard2->face){
        return 0; // 点数大，返回0
    }
    else{
        if (pCard1->suit < pCard2->suit){
            return 1; //  花色小，返回1
        }
        else{
            return 0; // 花色大，返回0
        }
    }
}
