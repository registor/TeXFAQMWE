/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：利用结构体数组及枚举实现洗牌发牌操作。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月05日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月05日
------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// 一副牌的数量
#define CARD_COUNT 54
// 玩家数量
#define PLAYER_COUNT 3

// 扑克花色枚举常量：梅花、方块、红桃、黑桃、小王、大王
enum Suit {CLUBS, DIAMONDS, HEARTS, SPADES, JOKER1, JOKER2};
// 声明1张扑克的结构体类型
typedef struct
{
    unsigned int face; // 1张牌的点数
    enum Suit suit;      // 1张牌的花色
} Card; // 重定义的类型名称

// 定义玩家
typedef struct
{
    char name[64]; // 玩家姓名
    Card** deck;     // 玩家分到的牌，是一个指针数组，
    // 每个指针指向原始一副牌中的一张，以节省空间
    int counts;        // 每个玩家分到的牌的数量
} Player; // 重定义的类型名称

// 比较函数类型重定义
typedef int (*pCmpFun)(Card*, Card*);

// 函数原型
void InitDeck(Card *, int, bool); // 初始化一副牌
Card** ShuffleDeck(Card*, int); // 洗牌
bool DispatchDeck(Player**, int, Card**, int); // 发牌
char* GetCardName(const Card*); // 构造一张牌的名称字符串
Player ** CreatePlayers(int); // 构造玩家数组
void PrintPlayerDeck(Player**, int); // 输出所有完家手里的牌
void DestroyPlayers(Player **, int); // 释放玩家内存空间
int Greater(Card*, Card*); // 升序比较函数
int Lesser(Card*, Card*);  // 降序比较函数

//-----------------------------------------------------------------------------------------------
// 名称：int main(void)
// 功能：主函数，程序入口
// 参数： 无
// 返回：int  --- 成功返回0，其它返回非0
// 作者：耿楠
// 日期：2017年11月03日
//-----------------------------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------------------------
// 名称：void InitDeck(Card *pDeck, int n, bool jokerFlag)
// 功能：初始化一副牌，也就是给各个牌赋值
// 参数：
//       [Card *pDeck] --- 一副牌数组的指针
//       [int n] --- 一副牌的张数(不包括大小王两张)
//       [bool jokerFlag] --- 是否包括两张大小王牌
// 返回：无
// 作者：耿楠
// 日期：2017年11月05日
//-----------------------------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------------------------
// 名称：Card** ShuffleDeck(Card* pDeck, int n)
// 功能：洗牌，也就是打乱一副牌的顺序
// 参数：
//       [Card *pDeck] --- 一副牌数组的指针
//       [int n] --- 一副牌的张数
// 返回：Card** --- 洗好的牌的指针
// 作者：耿楠
// 日期：2017年11月05日
//-----------------------------------------------------------------------------------------------
Card** ShuffleDeck(Card* pDeck, int n)
{
    // 分配保存洗牌结果的指针数组内存空间
    Card** pShuffleDeck = (Card**)malloc(n * sizeof(Card*));
    // 创建一个指向原始的每一张牌的指针数组作为过滤数组
    Card** pDeckItem = (Card**)malloc(n * sizeof(Card*));
    if(pShuffleDeck == NULL || pDeckItem == NULL)
    {
        return NULL; // 分配内存失败，返回NULL指针
    }

    // 让pDeckItem每个元素指向原始的每一张牌
    for (int i = 0; i < n; ++i)
    {
        pDeckItem[i] = &pDeck[i];
    }

    // 置随机种子
    srand(time(NULL));

    // 产生随机序号，并从pDeckItem中取出序号所指的项，
    // 依次加入到pShuffleDeck中
    for (int i = 0; i < n; ++i)
    {
        unsigned int idx = rand() % n; // 生成[0, n)之间的随机数

        if (pDeckItem[idx] != NULL)
        {
            // pDeckItem[idx]为NULL，说明这张牌没有被选过
            pShuffleDeck[i] = pDeckItem[idx]; // 选入到结果数组
            pDeckItem[idx] = NULL; // 置NULL表示已被选过，不可再选
        }
        else
        {
            --i; // 重新选这一张牌(非常重要的操作)
        }
    }
    free(pDeckItem); // 释放过渡指针数组内存空间

    //返回洗完牌后的数组
    return pShuffleDeck;
}

//-----------------------------------------------------------------------------------------------
// 名称：bool DispatchDeck(Player** pPlayers, int nPlayerCounts, Card** pShuffledDeck, int n)
// 功能：发牌，顺序将洗好的牌发给各个玩家
// 参数：
//       [Player** pPlayers] --- 玩家数组
//       [int nPlayerCounts] --- 玩家总数
//       [Card** pShuffledDeck] --- 洗好的一副牌
//       [int n] --- 一副牌的总张数
// 返回：[bool] --- 成功返回true, 失败返回false
// 作者：耿楠
// 日期：2017年11月05日
//-----------------------------------------------------------------------------------------------
bool DispatchDeck(Player** pPlayers, int nPlayerCounts, Card** pShuffledDeck, int n)
{
    // 计算每个玩家手中牌的容量
    // 剩下的底牌不作处理
    int cardNums = n / nPlayerCounts;
    int cardOvers = n % nPlayerCounts; // 底牌数量

    // 为每个玩家持牌数组分配空间
    for (int i = 0; i < nPlayerCounts; i++)
    {
        // 分配指针数组
        Card** pPlayerDeck = (Card**)malloc(cardNums * sizeof(Card*));
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

//-----------------------------------------------------------------------------------------------
// 名称：void SortDeck(Card** pDeck, int nCardCounts, pCmpFun pf)
// 功能：对一手牌进行排序
// 参数：
//       [Card** pDeck] --- 一手牌的指针数组
//       [int nCardCounts] --- 一手牌的张数
//       [pCmpFun pf] --- 比较函数的指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月05日
//-----------------------------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------------------------
// 名称：int Greater(Card* pCard1, Card* pCard2)
// 功能：比较函数1：先比较点数再比较花色(升序)
// 参数：
//       [Card* pCard1] --- 第1张牌的指针
//       [Card* pCard2] --- 每2张牌的指针
// 返回：[int] --- 大于返回1, 小于返回0
// 作者：耿楠
// 日期：2017年11月05日
//-----------------------------------------------------------------------------------------------
int Greater(Card* pCard1, Card* pCard2)
{
    if (pCard1->face > pCard2->face)
    {
        return 1; // 点数大，返回1
    }
    else if (pCard1->face < pCard2->face)
    {
        return 0; // 点数小，返回0
    }
    else
    {
        if (pCard1->suit > pCard2->suit)
        {
            return 1; //  花色大，返回1
        }
        else
        {
            return 0; // 花色小，返回0
        }
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：int Lesser(Card* pCard1, Card* pCard2)
// 功能：比较函数1：先比较点数再比较花色(降序)
// 参数：
//       [Card* pCard1] --- 第1张牌的指针
//       [Card* pCard2] --- 每2张牌的指针
// 返回：[int] --- 大于返回1, 小于返回0
// 作者：耿楠
// 日期：2017年11月05日
//-----------------------------------------------------------------------------------------------
int Lesser(Card* pCard1, Card* pCard2)
{
    if (pCard1->face < pCard2->face)
    {
        return 1; // 点数小，返回1
    }
    else if (pCard1->face > pCard2->face)
    {
        return 0; // 点数大，返回0
    }
    else
    {
        if (pCard1->suit < pCard2->suit)
        {
            return 1; //  花色小，返回1
        }
        else
        {
            return 0; // 花色大，返回0
        }
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：char* GetCardName(const Card* pCard)
// 功能：生成1张牌名称的字符串
// 参数：
//       [const Card* pCard] --- 1张牌的指针
// 返回：[char*] --- 1张牌的名称字符串指针
// 作者：耿楠
// 日期：2017年11月05日
//-----------------------------------------------------------------------------------------------
char* GetCardName(const Card* pCard)
{
    // 花色名称
    char SuitStr[2] = "";
    switch (pCard->suit)
    {
    case CLUBS:
        strcpy(SuitStr, "C");
        break;
    case DIAMONDS:
        strcpy(SuitStr, "D");
        break;
    case HEARTS:
        strcpy(SuitStr, "H");
        break;
    case SPADES:
        strcpy(SuitStr, "S");
        break;
    default:
        break;
    }

    // 点数名称
    char FaceStr[4] = "";
    switch (pCard->face)
    {
    case 1:
        strcpy(FaceStr, "A");
        break;
    case 11:
        strcpy(FaceStr, "J");
        break;
    case 12:
        strcpy(FaceStr, "Q");
        break;
    case 13:
        strcpy(FaceStr, "K");
        break;
    case 14:
        strcpy(FaceStr, "JK1");
        break;
    case 15:
        strcpy(FaceStr, "JK2");
        break;
    default:
        sprintf(FaceStr, "%d", pCard->face);
        break;
    }
    // 动态分配足够的空间
    char* retStr = (char*)malloc(sizeof(char) * 6);
    // 将两个字符串合并到ret中
    sprintf(retStr, "%s %s", FaceStr, SuitStr);
    return retStr;
}

//-----------------------------------------------------------------------------------------------
// 名称：void PrintPlayerDeck(Player** pPlayers, int n)
// 功能：输出玩家的一手牌
// 参数：
//       [Player** pPlayers] --- 玩家指针数组的指针
//       [int n] --- 玩家个数
// 返回：无
// 作者：耿楠
// 日期：2017年11月05日
//-----------------------------------------------------------------------------------------------
void PrintPlayerDeck(Player** pPlayers, int n)
{
    // 输出每个玩家手中的牌
    for (int i = 0; i < n; ++i)
    {
        // 玩家姓名
        printf("%s:\n", pPlayers[i]->name);
        // 对一手牌排序(升序)
        SortDeck(pPlayers[i]->deck, pPlayers[i]->counts, Greater);

        // 输出
        int nNewLineCnts = 0;
        for (int j = 0; j < pPlayers[i]->counts; j++)
        {
            // 得到牌的名称
            char* name = GetCardName(pPlayers[i]->deck[j]);
            // 打印牌的名称
            printf("%s\t", name);
            nNewLineCnts++;
            if (nNewLineCnts % 5 == 0)
                printf("\n");

            // 释放牌的名称数组占用的内存空间
            free(name);
            name = NULL; // 防止野指针
        }
        printf("\n");
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：Player ** CreatePlayers(int n)
// 功能：创建玩家数组
// 参数：
//       [int n] --- 玩家个数
// 返回：[Player **] --- 玩家指针数组
// 作者：耿楠
// 日期：2017年11月05日
//-----------------------------------------------------------------------------------------------
Player ** CreatePlayers(int n)
{
    char name[16] = "";

    // 分配n个玩家的动态内存
    Player* pPlayers = (Player*)malloc(n * sizeof(Player));
    if(pPlayers == NULL)
    {
        return NULL; // 分配内存失败，返回NULL
    }

    // 构造每个玩家的基本信息
    for (int i = 0; i < n; i++)
    {
        scanf("%s", name);
        strcpy(pPlayers[i].name, name); // 姓名
        pPlayers[i].deck = NULL; // 发到的牌的指针，初始化为NULL防止野指针
        pPlayers[i].counts = 0; // 发到的牌的张数，初始化为0
    }

    // 创建玩家指针数组
    Player** pPlayer = (Player**)malloc(n * sizeof(Player*));
    if(pPlayer == NULL)
    {
        return NULL; // 分配内存失败，返回NULL
    }

    for (int i = 0; i < n; i++)
    {
        pPlayer[i] = &pPlayers[i]; // 为指针数组赋值
    }

    return pPlayer;
}

//-----------------------------------------------------------------------------------------------
// 名称：void DestroyPlayers(Player **pPlayers, int n)
// 功能：释放玩家内存空间
// 参数：
//       [Player **pPlayers] --- 玩家指针数组指针
//       [int n] --- 玩家个数
// 返回：无
// 作者：耿楠
// 日期：2017年11月05日
//-----------------------------------------------------------------------------------------------
void DestroyPlayers(Player **pPlayers, int n)
{
    // 释放玩家手中的一手牌的数组
    for (int i = 0; i < n; i++)
    {
        free(pPlayers[i]->deck);
        pPlayers[i]->deck = NULL; // 防止野指针
    }

    // 释放玩家数组
    free(*pPlayers);
    *pPlayers = NULL; // 防止野指针
}
