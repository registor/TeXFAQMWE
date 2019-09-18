// 功能：创建玩家数组
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
        pPlayers[i].deck = NULL; // 发到的牌的指针
        pPlayers[i].counts = 0; // 发到的牌的张数
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
