#include "listwithfuncpt.h"
#include <malloc.h>

static struct single_list * _add_node(struct single_list *list, struct slist_node *node)
{

    if(list->tail)
    {
        list->tail->next = node;
        node->next = 0;
        list->tail = node;
        list->size++;
    }
    else
    {
        list->head = node;
        list->tail = node;
        node->next = 0;
        list->size = 1;
    }

    return list;
}

static struct single_list * _insert_node(struct single_list * list, int pos, struct slist_node *node)
{
    if(pos < list->size)
    {
        int i = 0;
        struct slist_node * p = list->head;
        struct slist_node * prev = list->head;
        for(; i < pos; i++)
        {
            prev = p;
            p = p->next;
        }
        if(p == list->head)
        {
            /* insert at head */
            node->next = list->head;
            list->head = node;
        }
        else
        {
            prev->next = node;
            node->next = p;
        }

        if(node->next == 0) list->tail = node;
        list->size++;
    }
    else
    {
        list->add(list, node);
    }

    return list;
}

static struct single_list * _replace(struct single_list * list, int pos, struct slist_node *node)
{
    if(pos < list->size)
    {
        int i = 0;
        struct slist_node * p = list->head;
        struct slist_node * prev = list->head;
        for(; i < pos; i++)
        {
            prev = p;
            p = p->next;
        }
        if(p == list->head)
        {
            /* replace at head */
            node->next = list->head->next;
            list->head = node;
        }
        else
        {
            prev->next = node;
            node->next = p->next;
        }

        if(node->next == 0) list->tail = node;

        if(list->free_node) list->free_node(p);
        else free(p);
    }

    return list;
}

static struct slist_node * _find_by_key(struct single_list *list, void * key)
{
    if(list->key_hit_test)
    {
        struct slist_node * p = list->head;
        while(p)
        {
            if(list->key_hit_test(p, key) == 0) return p;
            p = p->next;
        }
    }
    return 0;
}

static struct slist_node *_first_of(struct single_list* list)
{
    return list->head;
}

static struct slist_node *_last_of(struct single_list* list)
{
    return list->tail;
}

static struct slist_node *_node_at(struct single_list * list, int pos)
{
    if(pos < list->size)
    {
        int i = 0;
        struct slist_node * p = list->head;
        for(; i < pos; i++)
        {
            p = p->next;
        }
        return p;
    }

    return 0;
}

static struct slist_node * _take_at(struct single_list * list, int pos)
{
    if(pos < list->size)
    {
        int i = 0;
        struct slist_node * p = list->head;
        struct slist_node * prev = p;
        for(; i < pos ; i++)
        {
            prev = p;
            p = p->next;
        }
        if(p == list->head)
        {
            list->head = p->next;
            if(list->head == 0) list->tail = 0;
        }
        else if(p == list->tail)
        {
            list->tail = prev;
            prev->next = 0;
        }
        else
        {
            prev->next = p->next;
        }

        list->size--;

        p->next = 0;
        return p;
    }

    return 0;
}

static struct slist_node * _take_by_key(struct single_list * list, void *key)
{
    if(list->key_hit_test)
    {
        struct slist_node * p = list->head;
        struct slist_node * prev = p;
        while(p)
        {
            if(list->key_hit_test(p, key) == 0) break;
            prev = p;
            p = p->next;
        }

        if(p)
        {
            if(p == list->head)
            {
                list->head = p->next;
                if(list->head == 0) list->tail = 0;
            }
            else if(p == list->tail)
            {
                list->tail = prev;
                prev->next = 0;
            }
            else
            {
                prev->next = p->next;
            }

            list->size--;

            p->next = 0;
            return p;
        }
    }
    return 0;
}

static struct single_list *_remove_node(struct single_list * list, struct slist_node * node)
{
    struct slist_node * p = list->head;
    struct slist_node * prev = p;
    while(p)
    {
        if(p == node) break;
        prev = p;
        p = p->next;
    }

    if(p)
    {
        if(p == list->head)
        {
            list->head = list->head->next;
            if(list->head == 0) list->tail = 0;
        }
        else if(p == list->tail)
        {
            prev->next = 0;
            list->tail = prev;
        }
        else
        {
            prev->next = p->next;
        }

        if(list->free_node) list->free_node(p);
        else free(p);

        list->size--;
    }
    return list;
}

static struct single_list *_remove_at(struct single_list *list, int pos)
{
    if(pos < list->size)
    {
        int i = 0;
        struct slist_node * p = list->head;
        struct slist_node * prev = p;
        for(; i < pos ; i++)
        {
            prev = p;
            p = p->next;
        }
        if(p == list->head)
        {
            list->head = p->next;
            if(list->head == 0) list->tail = 0;
        }
        else if(p == list->tail)
        {
            list->tail = prev;
            prev->next = 0;
        }
        else
        {
            prev->next = p->next;
        }

        if(list->free_node) list->free_node(p);
        else free(p);

        list->size--;
    }

    return list;
}

static struct single_list *_remove_by_key(struct single_list *list, void *key)
{
    if(list->key_hit_test)
    {
        struct slist_node * p = list->head;
        struct slist_node * prev = p;
        while(p)
        {
            if(list->key_hit_test(p, key) == 0) break;
            prev = p;
            p = p->next;
        }

        if(p)
        {
            if(p == list->head)
            {
                list->head = list->head->next;
                if(list->head == 0) list->tail = 0;
            }
            else if(p == list->tail)
            {
                prev->next = 0;
                list->tail = prev;
            }
            else
            {
                prev->next = p->next;
            }

            if(list->free_node) list->free_node(p);
            else free(p);

            list->size--;
        }
    }

    return list;
}

static int _length_of(struct single_list * list)
{
    return list->size;
}

static void _clear_list(struct single_list * list)
{
    struct slist_node * p = list->head;
    struct slist_node * p2;
    while(p)
    {
        p2 = p;
        p = p->next;

        if(list->free_node) list->free_node(p2);
        else free(p2);
    }

    list->head = 0;
    list->tail = 0;
    list->size = 0;
}

static void _delete_single_list(struct single_list *list)
{
    list->clear(list);
    free(list);
}

struct single_list * new_single_list(list_op_free_node op_free, list_op_key_hit_test op_cmp)
{
    struct single_list *list = (struct single_list *)malloc(sizeof(struct single_list));
    list->head = 0;
    list->tail = 0;
    list->size = 0;
    list->free_node = op_free;
    list->key_hit_test = op_cmp;

    list->add = _add_node;
    list->insert = _insert_node;
    list->replace = _replace;
    list->find_by_key = _find_by_key;
    list->first = _first_of;
    list->last = _last_of;
    list->at = _node_at;
    list->take_at = _take_at;
    list->take_by_key = _take_by_key;
    list->remove = _remove_node;
    list->remove_at = _remove_at;
    list->remove_by_key = _remove_by_key;
    list->length = _length_of;
    list->clear = _clear_list;
    list->deletor = _delete_single_list;

    return list;
}

/* call 1 or N arguments function of struct */
#define ST_CALL(THIS,func,args...) ((THIS)->func(THIS,args))

/* call none-arguments function of struct */
#define ST_CALL_0(THIS,func) ((THIS)->func(THIS))

struct int_node
{
    struct slist_node node;
    int id;
};

struct string_node
{
    struct slist_node node;
    char name[16];
};


static int int_free_flag = 0;
static void _int_child_free(struct slist_node *node)
{
    free(node);
    if(!int_free_flag)
    {
        int_free_flag = 1;
        printf("int node free\n");
    }
}

static int _int_slist_hittest(struct slist_node * node, void *key)
{
    struct int_node * inode = NODE_T(node, struct int_node);
    int ikey = (int)key;
    return (inode->id == ikey ? 0 : 1);
}

static int string_free_flag = 0;
static void _string_child_free(struct slist_node *node)
{
    free(node);
    if(!string_free_flag)
    {
        string_free_flag = 1;
        printf("string node free\n");
    }
}

static int _string_slist_hittest(struct slist_node * node, void *key)
{
    struct string_node * sn = (struct string_node*)node;
    return strcmp(sn->name, (char*)key);
}

void int_slist_test()
{
    struct single_list * list = new_single_list(_int_child_free, _int_slist_hittest);
    struct int_node * node = 0;
    struct slist_node * bn = 0;
    int i = 0;

    printf("create list && nodes:\n");
    for(; i < 100; i++)
    {
        node = (struct int_node*)malloc(sizeof(struct int_node));
        node->id = i;
        if(i % 10)
        {
            list->add(list, node);
        }
        else
        {
            list->insert(list, 1, node);
        }
    }
    printf("create 100 nodes end\n----\n");
    printf("first is : %d, last is: %d\n----\n",
           NODE_T( ST_CALL_0(list, first), struct int_node )->id,
           NODE_T( ST_CALL_0(list, last ), struct int_node )->id);

    assert(list->size == 100);

    printf("list traverse:\n");
    for(i = 0; i < 100; i++)
    {
        if(i % 10 == 0) printf("\n");
        bn = list->at(list, i);
        node = NODE_T(bn, struct int_node);
        printf(" %d", node->id);
    }
    printf("\n-----\n");

    printf("find by key test, key=42:\n");
    bn = list->find_by_key(list, (void*)42);
    assert(bn != 0);
    node = NODE_T(bn, struct int_node);
    printf("find node(key=42), %d\n------\n", node->id);

    printf("remove node test, remove the 10th node:\n");
    bn = list->at(list, 10);
    node = NODE_T(bn, struct int_node);
    printf("  node 10 is: %d\n", node->id);
    printf("  now remove node 10\n");
    list->remove_at(list, 10);
    printf(" node 10 was removed, check node 10 again:\n");
    bn = list->at(list, 10);
    node = NODE_T(bn, struct int_node);
    printf("  now node 10 is: %d\n------\n", node->id);

    printf("replace test, replace node 12 with id 1200:\n");
    bn = list->at(list, 12);
    node = NODE_T(bn, struct int_node);
    printf("  now node 12 is : %d\n", node->id);
    node = (struct int_node*)malloc(sizeof(struct int_node));
    node->id = 1200;
    list->replace(list, 12, node);
    bn = list->at(list, 12);
    node = NODE_T(bn, struct int_node);
    printf("  replaced, now node 12 is : %d\n----\n", node->id);

    printf("test remove:\n");
    ST_CALL(list, remove, bn);
    bn = ST_CALL(list, find_by_key, (void*)1200);
    assert(bn == 0);
    printf("test remove ok\n----\n");
    printf("test remove_by_key(90):\n");
    ST_CALL(list, remove_by_key, (void*)90);
    bn = ST_CALL(list, find_by_key, (void*)90);
    assert(bn == 0);
    printf("test remove_by_key(90) end\n----\n");
    printf("test take_at(80):\n");
    bn = ST_CALL(list, take_at, 80);
    printf("  node 80 is: %d\n", NODE_T(bn, struct int_node)->id);
    free(bn);
    printf("test take_at(80) end\n");

    int_free_flag = 0;
    printf("delete list && nodes:\n");
    list->deletor(list);
    printf("delete list && nodes end\n");
    printf("\n test add/insert/remove/delete/find_by_key/replace...\n");
}

void string_slist_test()
{
    struct single_list * list = new_single_list(_string_child_free, _string_slist_hittest);
}

void slist_test()
{
    int_slist_test();
    string_slist_test();
}
