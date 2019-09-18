// 节点数据类型的枚举常量
typedef enum datatype
{
    STRING,
    INT,
    DOUBLE,
    PT2D
} DataType;

// 链表结点
typedef struct node
{
    // 数据域指针，可指向任意类型
    void *data;
    // 指向下一个链表节点
    struct node *next;   
} ListNode;
