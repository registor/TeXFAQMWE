...
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
