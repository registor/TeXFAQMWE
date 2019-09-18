bool CopyStu(StuNodePt const pTarget, const StuNodePt pSource)
{
    if(pSource == NULL || pSource->name == NULL || 
       pSource->gender == NULL || pTarget == NULL)
    {
        return false; // 确保指针正确，否则返回假
    }

    if(pTarget->name != NULL)
    {
        free(pTarget->name); // 若指针不为NULL，释放内存
    }

    if(pTarget->gender != NULL)
    {
        free(pTarget->gender); // 若指针不为NULL，释放内存
    }

    // 分配内存
    pTarget->name = (char *)malloc((strlen(pSource->name)+1) 
                                           * sizeof(char));
    pTarget->gender = (char *)malloc((strlen(pSource->gender)+1) 
                                             * sizeof(char));
    if(pTarget->name == NULL || pTarget->gender == NULL)
    {
        pTarget->ID = -1;
        return false;  // 分配内存出错，返回假值
    }
    // 复制
    pTarget->ID = pSource->ID;
    strcpy(pTarget->name, pSource->name);
    strcpy(pTarget->gender, pSource->gender);
    pTarget->birthday.year = pSource->birthday.year;
    pTarget->birthday.month = pSource->birthday.month;
    pTarget->birthday.day = pSource->birthday.day;

    return true; // 一切正常返回真值
}
...
