流程：构建一副牌保存到一个数组中–>洗牌–>创建玩家–>向玩家发牌–>输出每个玩家的牌

#include
#include
#include
#include
#include

//一副牌的数量
#define CARD_COUNT 54

//定义扑克的花色, 黑，红，梅，方，小王 ，大王
enum Color{BLACK, RED, CLUB, DIAMOND, JOKER1, JOKER2};
//定义扑克结构体
typedef struct Card
{
int val; //扑克牌点数
enum Color color; //花色
}Card;
//定义玩家
typedef struct Player
{
char name[64]; //玩家名字
Card** cards; //玩家分到的牌,每项是一个指针，指向原始一副牌数组中的一项，这样可以节省空间
int cardsCount; //每个玩家分到的牌的数量
}Player;

//分完牌后调用的函数的类型
typedef int (*pCompare)(Card*, Card*);
//原始一副牌所在的数组
Card pokers[CARD_COUNT];

//初始化一副牌
void InitOnePoker()
{
//前52张
int i=0;
for (i=0; i
{
pokers[i].val = i/4 + 1;
pokers[i].color = (Color)(i%4);
}
//剩下的大王和小王
pokers[i].val = i/4 + 1;
pokers[i].color = JOKER1;
//大王
pokers[i+1].val = i/4 + 2;
pokers[i+1].color = JOKER2;
}

//洗牌，参数是最原始的一副牌，返回洗完后的牌
Card** Shuffle(Card* pokers)
{
//分牌返回牌数组的内存空间
Card** retPokers = (Card**)malloc(sizeof(Card*)*CARD_COUNT);
//为了不改动原始的一副牌，另建一个数组，保存原始牌的指针(注意每项不是牌，而是牌的指针)
Card** pokers2 = (Card**)malloc(sizeof(Card*)*CARD_COUNT);
for (int i=0; i
{
pokers2[i] = &pokers[i];
}

//种下随机种子，种子取当前时间,保证了每次运行程序时，产生的随机数不同
srand(time(NULL));
//取得随机序号，从pokers2取出序号所指的项，依次加入到retPokers中
for (int i=0; i
{
unsigned int index = rand() % CARD_COUNT;
//说明没有选过
if (pokers2[index] != NULL)
{
retPokers[i] = pokers2[index];
pokers2[index] = NULL;
}
else
{
--i;
}
}
free(pokers2);
//返回洗完牌后的数组
return retPokers;
}
//发牌
//players是玩家数组，playerCount是玩家数量，shuffledCard是洗完后的一副牌
void DispatchCards(Player** players, int playerCount, Card** shuffledCard)
{
//计算每个玩家手中牌的数组的容量，如果每个玩家手中的牌不一样
//最多就差一张，加1是为了保证数组分配的空间足够容纳分到的牌
int numberCards = CARD_COUNT/playerCount + 1;

//为每个玩家的牌数组分配空间
for (int i=0; i
{
Card** cards = (Card**)malloc(sizeof(Card*)*numberCards);
players[i]->cards = cards;
}
//轮流向每个玩家发牌
for (int i=0; i
{
//取当前玩家
Player* curPlayer = players[i%playerCount];
//向玩家发牌
curPlayer->cards[curPlayer->cardsCount] = shuffledCard[i];
//玩家手中实际的牌数增加
curPlayer->cardsCount++;
}
}

//排序函数
//cards是要排序的牌，每一项是牌的指针，cardsCount是牌的数量，compare_fun是比较函数
void SortCards(Card** cards, int cardsCount, pCompare compare_fun)
{
//Optimize Bubble Sort
bool flag = true;
for (int i=0; i
{
flag = true;
for (int j=0; j
{
if (compare_fun(cards[j], cards[j+1]))
{
//swap
Card* tmp = cards[j];
cards[j] = cards[j+1];
cards[j+1] = tmp;
flag = false;
}
}
if (flag)
break;
}
}

//比较函数1：先比较点数再比较花色(升序)
int compare1(Card* a, Card* b)
{
if (a->val > b->val)
return 1;
else if (a->val < b->val)
return 0;
else
{
if (a->color > b->color)
return 1;
else
return 0;
}
}
//比较函数2：比较点数再比较花色(降序)
int compare2(Card* a, Card* b)
{
if (a->val < b->val)
return 1;
else if (a->val > b->val)
return 0;
else
{
if (a->color < b->color)
return 1;
else
return 0;
}
}
//获取牌的名字
//返回牌的名字字符串，调用着用完之后要free()之
char* GetCardName(const Card* card)
{
//存放花色名字
char ColorStr[16] = "";
switch (card->color)
{
case BLACK: strcpy(ColorStr, "黑桃"); break;
case RED: strcpy(ColorStr, "红桃"); break;
case CLUB: strcpy(ColorStr, "梅花"); break;
case DIAMOND: strcpy(ColorStr, "方块"); break;
}
//存放点数名字
char valStr[16] = "";
switch (card->val)
{
case 1: strcpy(valStr, "A"); break;
case 11:strcpy(valStr, "J"); break;
case 12:strcpy(valStr, "Q"); break;
case 13:strcpy(valStr, "K"); break;
case 14:strcpy(valStr, "小王"); break;
case 15:strcpy(valStr, "大王"); break;
default:sprintf(valStr, "%d", card->val); break;
}
//动态分配足够的空间
char* ret = (char*)malloc(sizeof(char)*16);
//将两个字符串合并到ret中
sprintf(ret, "%s%s", ColorStr, valStr);
return ret;
}

//打印玩家手中的牌
void PrintCard(Player** players, int n)
{
//打印每个玩家手中的牌
for (int i=0; i
{
//打印玩家名字
printf("%s:\n", players[i]->name);
//对玩家手中的牌排序
SortCards(players[i]->cards, players[i]->cardsCount, compare1);
//打印玩家手中的牌
int fomart = 0;
for (int j=0; jcardsCount; ++j)
{
//得到牌的名字
char* name = GetCardName(players[i]->cards[j]);
//打印牌的名字
printf("%s\t", name);
++fomart;
if (fomart%5 == 0)
printf("\n");

//释放
free(name);
name = NULL;
}
printf("\n");
}
}

int main()
{
//初始化一副牌
InitOnePoker();
//洗牌，shuffledPokers保存洗后的牌
Card** shuffledPokers = Shuffle(pokers);

//构建n个玩家
int n;
printf("please input the number of player: ");
scanf("%d", &n);
Player* playersInfo = (Player*)malloc(sizeof(Player)*n);
char name[16] = "";
printf("please input the name of every player: ");
for (int i=0; i
{
scanf("%s", name);
strcpy(playersInfo[i].name, name);
playersInfo[i].cards = NULL;
playersInfo[i].cardsCount = 0;
}
//把n个放在一个数组中，以便传入发牌函数中
Player** players = (Player**)malloc(sizeof(Player*)*n);
for (int i=0; i
{
players[i] = &playersInfo[i];
}

//发牌
DispatchCards(players, n, shuffledPokers);
//洗后的牌用完了，释放掉
free(shuffledPokers);

//打印玩家手中的牌
PrintCard(players, n);

//释放玩家手中的牌数组
for (int i=0; i
{
free(players[i]->cards);
}
//释放每个玩家所在的数组
free(players);
players = NULL;
//释放每个玩家的信息
free(playersInfo);
playersInfo = NULL;

return 0;
}

