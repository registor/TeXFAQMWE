// 节点数据类型的枚举常量
typedef enum datatype
{
    INT,
    DOUBLE,
    STRING,
    PT2D
} DataType;

// 链表节点结构体类型
typedef struct node
{
    // 万能指针，指向该节点的数据区
    void *data;
    // 数据域数据类型的枚举值
    DataType dataType;
    // 指向下一个链表节点
    struct node *next;
    // 输出节点的数据函数指针
    void (*pPrintFun)(const void *);
    // 销毁节点占有的内存的函数指针
    void (*pFreeFun)(void *);
} ListNode;
