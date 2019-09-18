/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示INI文件的读写问题。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月13日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月13日
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct tag_value_list;

struct ini_parser
{
    struct tag_value_list * keyvalues;
    int (*parse_file)(struct ini_parser *, const char * file);
    int (*parse_string)(struct ini_parser *, const char *text);
    char * (*value)(struct ini_parser *, const char * key);
    void (*set_value)(struct ini_parser *, const char * key, const char * value);
    void (*remove)(struct ini_parser *, const char *key);
    int (*save_to_file)(struct ini_parser *, const char * file);
};

struct ini_parser * new_ini_parser();
void delete_ini_parser(struct ini_parser *);

struct tag_value_pair
{
    struct slist_node node;
    char * szTag;
    char * szValue;
};
typedef struct tag_value_pair tag_value;

//-----------------------------------------------------------------------------------------------
// 名称：int main(void)
// 功能：主函数，程序入口
// 参数：
//           [void] --- 无
// 返回：[int]  --- 成功返回0，其它返回非0
// 作者：耿楠
// 日期：2017年11月13日
//-----------------------------------------------------------------------------------------------
int main(void)
{


    return 0;
}

static struct tag_value_pair * parse_line(char *line, int len)
{
    struct tag_value_pair * pair = 0;
    int count = 0;
    char * p = line;
    char * end = 0;
    char * start = line;

    if(!p)
    {
        return 0;
    }
    while(*p == ' ')
    {
        p++;
    }


    /*blank line*/
    if(p - line == len ||
            *p == '\r' ||
            *p == '\n' ||
            *p == '\0')
    {
        return 0;
    }

    /*do not support group*/
    if(*p == '[')
    {
        return 0;
    }
    /*comments*/
    if(*p == '#')
    {
        return 0;
    }

    /* extract key */
    start = p;
    end = line + len;
    while(*p != '=' && p != end)
    {
        p++;
    }
    if(p == end)
    {
        /* none '=' , invalid line */
        return 0;
    }
    end = p - 1;
    while(*end == ' ') /* skip blank at the end */
    {
        end--;
    }
    count = end - start + 1;

    pair = new_tag_value_pair();
    pair->szTag = malloc(count + 1);
    strncpy(pair->szTag, start, count);
    pair->szTag[count] = 0;

    /* extract value */
    p++;
    end = line + len; /* next pos of the last char */
    while( *p == ' ' && p != end)
    {
        p++;
    }
    if(p == end)
    {
        delete_tag_value_pair(pair);
        return 0;
    }
    start = p;
    end--; /* to the last char */
    if(*end == '\n')
    {
        *end = 0;
        end--;
    }
    if(*end == '\r')
    {
        *end = 0;
        end--;
    }
    count = end - start + 1;
    if(count > 0)
    {
        pair->szValue = malloc(count + 1);
        strncpy(pair->szValue, start, count);
        pair->szValue[count] = 0;
    }

    /* release empty key-value pair */
    if(!pair->szValue)
    {
        delete_tag_value_pair(pair);
        return 0;
    }

    return pair;
}

static int _parse_file(struct ini_parser * ini, const char *file)
{
    FILE * fp = fopen(file, "r");
    if(fp)
    {
        struct tag_value_pair * pair = 0;
        char buf[1024] = {0};
        while(fgets(buf, 1024, fp))
        {
            pair = parse_line(buf, strlen(buf));
            if(pair)
            {
                ini->keyvalues->add(ini->keyvalues, pair);
            }
        }
        fclose(fp);
        return ini->keyvalues->size;
    }
    return -1;
}

static int _parse_text(struct ini_parser * ini, const char * text)
{
    char *p = text;
    char * start = 0;
    struct tag_value_pair * pair = 0;
    if(!text) return -1;

    while(1)
    {
        start = p;
        while(*p != '\n' && *p != '\0' )
        {
            p++;
        }
        if(*p == '\0')
        {
            break;
        }

        pair = parse_line(start, p - start);
        if(pair)
        {
            ini->keyvalues->add(ini->keyvalues, pair);
        }

        p++;
    }

    return ini->keyvalues->size;
}

static char * _value(struct ini_parser * ini, const char * key)
{
    struct tag_value_pair * pair = ini->keyvalues->find_by_tag(ini->keyvalues, key);
    if(pair)
    {
        return pair->szValue;
    }
    return 0;
}

static void _set_value(struct ini_parser * ini, const char * key, const char *value)
{
    struct tag_value_pair * pair = ini->keyvalues->find_by_tag(ini->keyvalues, key);
    if(pair)
    {
        if(pair->szValue)
        {
            free(pair->szValue);
        }
        pair->szValue = strdup(value);
    }
    else
    {
        ini->keyvalues->add(ini->keyvalues, make_tag_value_pair(key, value));
    }
}

static void _remove(struct ini_parser * ini, const char * key)
{
    struct tag_value_pair * pair = ini->keyvalues->find_by_tag(ini->keyvalues, key);
    if(pair)
    {
        ini->keyvalues->remove(ini->keyvalues, pair);
    }
}

static void write_keyvalue(struct tag_value_pair * pair, FILE *fp)
{
    fputs(pair->szTag, fp);
    fputc('=', fp);
    fputs(pair->szValue, fp);
    fputc('\n', fp);
}

static int _save_to_file(struct ini_parser * ini, const char * file)
{
    if(ini->keyvalues->size > 0)
    {
        FILE * fp = fopen(file, "w");
        if(fp)
        {
            struct tag_value_pair * pair = ini->keyvalues->head;
            while(pair != ini->keyvalues->tail)
            {
                write_keyvalue(pair, fp);
                pair = pair->next;
            }

            if(pair)
            {
                write_keyvalue(pair, fp);
            }

            fclose(fp);
            return 0;
        }
    }
    return -1;
}

struct ini_parser * new_ini_parser()
{
    struct ini_parser * ini = (struct ini_parser*)malloc(sizeof(struct ini_parser));
    ini->keyvalues = new_tag_value_list();
    ini->parse_file = _parse_file;
    ini->parse_string = _parse_text;
    ini->value = _value;
    ini->set_value = _set_value;
    ini->remove = _remove;
    ini->save_to_file = _save_to_file;
    return ini;
}

void delete_ini_parser(struct ini_parser *ini)
{
    if(ini)
    {
        delete_tag_value_list(ini->keyvalues);
        free(ini);
    }
}



static char * g_szIniString = "#abc\nfirst=2\nsecond\nname=charli zhang \n";

static void ini_parser_test_string()
{
    struct ini_parser * ini = new_ini_parser();
    int size = ini->parse_string(ini, g_szIniString);

    assert( size > 0);
    assert( ini->value(ini, "second") == 0 );
    assert( ini->value(ini, "abc") == 0);
    assert( ini->value(ini, "name") != NULL );
    assert( ini->value(ini, "first") != NULL);

    printf("ini string: %s\n", g_szIniString);
    printf("key-value pairs count = %d\n", size);
    printf("key \'name\'', value = %s\n", ini->value(ini, "name"));
    printf("key \'first\'', value = %s\n", ini->value(ini, "first"));

    ini->set_value(ini, "baidu", "hahaha");
    ini->save_to_file(ini, "write.conf");

    ini->remove(ini, "first");
    ini->save_to_file(ini, "write2.conf");

    delete_ini_parser(ini);
}

static void ini_parser_test_file()
{
    struct ini_parser * ini = new_ini_parser();
    int size = ini->parse_file(ini, "test.conf");

    assert( size > 0);
    assert( ini->value(ini, "second") == 0 );
    assert( ini->value(ini, "abc") == 0);
    assert( ini->value(ini, "name") != NULL );
    assert( ini->value(ini, "first") != NULL);

    printf("ini string: %s\n", g_szIniString);
    printf("key-value pairs count = %d\n", size);
    printf("key \'name\'', value = %s\n", ini->value(ini, "name"));
    printf("key \'first\'', value = %s\n", ini->value(ini, "first"));
    printf("key \'baidu\'', value = %s\n", ini->value(ini, "baidu"));

    delete_ini_parser(ini);
}

void ini_parser_test()
{
    ini_parser_test_string();
    ini_parser_test_file();
}
