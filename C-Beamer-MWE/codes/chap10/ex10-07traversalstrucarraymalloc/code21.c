// 创建一个节点的数据
bool InitNode(StuNodePt pNode, int ID, const char *pname, 
  const char *pgender, int year, int month, int day)
{
    if(pNode == NULL || pname == NULL || pgender == NULL)
    {
        return false; // 空指针，无法后续操作，返回假值
    }

    // ID赋值
    pNode->ID = ID;

    // 为姓名和性别成员动态开避内存并赋值
    pNode->name = (char *)malloc((strlen(pname) + 1)
                                  * sizeof(char));
    pNode->gender = (char *)malloc((strlen(pgender) + 1)
                                    * sizeof(char));
    if(pNode->name == NULL || pNode->gender == NULL)
    {
        pNode->ID = -1;
        return false;  // 内存分配出错，返回假值
    }
    // 动态内存赋值
    strcpy(pNode->name, pname);
    strcpy(pNode->gender, pgender);

    // 其它成员赋值
    pNode->birthday.year = year;
    pNode->birthday.month = month;
    pNode->birthday.day = day;

    return true; // 一切正常，返回真值
}

void DestroyNode(StuNode *pNode)
{
    // 释放节点中动态分配的内存
    free(pNode->name);
    pNode->name = NULL;
    free(pNode->gender);
    pNode->name = NULL;
}
