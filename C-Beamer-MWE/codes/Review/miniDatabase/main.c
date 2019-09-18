/*--------------------------------------------------------------------------------
* Copyright (c) 2019,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：一个用于地址薄小型数据库的演示代码。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2019年XX月XX日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// 宏定义
#define MAX_DATA 512
#define MAX_ROWS 100

// 结构体类型定义
struct Address
{
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};
struct Database
{
    struct Address rows[MAX_ROWS];
};
struct Connection
{
    FILE *file;
    struct Database *db;
};

// 函数原型
void Die(const char *); // 处理错误，输出错误信息
void PrintAddress(struct Address *); // 输出数据
void LoadDatabase(struct Connection *); // 从数据库读入数据
struct Connection *OpenDatabase(const char *, char ); // 打开数据库
void CloseDatabase(struct Connection *); // 关闭数据库
void WriteDatabase(struct Connection *); // 写入数据库
void CreateDatabase(struct Connection *); // 创建数据库
void SetDatabase(struct Connection *, int, const char *, const char *);  // 为数据库中的数据赋值
void GetDatabase(struct Connection *, int ); // 读取数据库中的数据
void DelDatabase(struct Connection *, int ); // 删除数据库中的数据
void ListDatabase(struct Connection *); // 输出数据库中的数据

void run(const char *, char); // 测试函数

// 测试
int main(int argc, char *argv[])
{
    // 处理命令行参数
    if(argc < 3)
    {
        Die("USAGE: miniDatabase <dbfile> <action>");
    }
    char *filename = argv[1];
    char action = argv[2][0];

    run(filename, action); // 启动各项功能

    return 0;
}

// 函数定义
//------------------------------------------------------
// 名称: void run(const char *filename, char action)
// 功能: 启动测试
// 参数:
//       [const char *filename] --- 数据库文件名指针
//       [char action] --- 操作方式标识符
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月19日
//------------------------------------------------------
void run(const char *filename, char action)
{
    // 声明变量
    int id;
    char name[MAX_DATA] = {'\0'};
    char email[MAX_DATA] = {'\0'};

    // 打开数据数
    struct Connection *conn = OpenDatabase(filename, action);

    // 执行操作
    switch(action)
    {
    case 'c':
        CreateDatabase(conn);
        WriteDatabase(conn);
        break;
    case 'g':
        printf("Please input id: ");
        scanf("%d", &id);
        GetDatabase(conn, id);
        break;
    case 's':
        printf("Please input id: ");
        scanf("%d", &id);
        printf("Please input name: ");
        scanf("%s", name);
        printf("Please input email: ");
        scanf("%s", email);
        SetDatabase(conn, id, name, email);
        WriteDatabase(conn);
        break;
    case 'd':
        printf("Please input id: ");
        scanf("%d", &id);
        DelDatabase(conn, id);
        WriteDatabase(conn);
        break;
    case 'l':
        ListDatabase(conn);
        break;
    default:
        Die("Invalid action, only: c=create, g=get, s=set, d = del, l = list");
    }
    CloseDatabase(conn);
}

//---------------------------------------------------
// 名称: void Die(const char *message)
// 功能: 输出错误信息，然后结束程序
// 参数:
//       [const char *message] --- 字符串指针
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月19日
// 备注: 程序先处理<errno.h>定义的错误码
//---------------------------------------------------
void Die(const char *message)
{
    if(errno)
    {
        perror(message);
    }
    else
    {
        printf("ERROR: %s\n", message);
    }

    // 异常，结束程序
    exit(1);
}

//---------------------------------------------------
// 名称: void PrintAddress(struct Address *addr)
// 功能: 输出数据
// 参数:
//       [struct Address *addr] --- 数据结构体指针
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月19日
//---------------------------------------------------
void PrintAddress(struct Address *addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

//---------------------------------------------------------
// 名称: void LoadDatabase(struct Connection *conn)
// 功能: 读入1个数据
// 参数:
//       [struct Connection *conn] --- 数据库连接指针
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月19日
//---------------------------------------------------------
void LoadDatabase(struct Connection *conn)
{
    // 从数据库中读入1个数据
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);

    // 读入失败
    if(rc != 1)
    {
        Die("Failed to load database.");
    }
}

//----------------------------------------------------------------------------------
// 名称: struct Connection *OpenDatabase(const char *filename, char mode)
// 功能: 打开数据库
// 参数:
//       [const char *filename] --- 数据库文件名指针
//       [char mode] --- 打开方式标识符
// 返回: [struct Connection *]  --- 返回数据库连接指针
// 作者: 耿楠
// 日期: 2019年01月19日
//----------------------------------------------------------------------------------
struct Connection *OpenDatabase(const char *filename, char mode)
{
    // 动态申请数据库连接内存
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn)
    {
        Die("Memory error");
    }

    // 动态申请数据库内存
    conn->db = malloc(sizeof(struct Database));
    if(!conn->db)
    {
        Die("Memory error");
    }

    // 打开方式
    if(mode == 'c')
    {
        conn->file = fopen(filename, "w"); // 创建数据库
    }
    else
    {
        conn->file = fopen(filename, "r+"); // 读取数据库
        if(conn->file)
        {
            LoadDatabase(conn);
        }
    }

    // 数据库文件打开失败
    if(!conn->file)
    {
        Die("Failed to open the file");
    }

    return conn; // 返回连接指针
}

//---------------------------------------------------------
// 名称: void CloseDatabase(struct Connection *conn)
// 功能: 关闭数据库
// 参数:
//       [struct Connection *conn] --- 数据库连接指针
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月19日
//---------------------------------------------------------
void CloseDatabase(struct Connection *conn)
{
    if(conn)
    {
        if(conn->file)
        {
            fclose(conn->file); // 关闭链接文件
        }
        if(conn->db)
        {
            free(conn->db); // 释放数据库内存
        }
        free(conn); // 释放连接内存
    }
}

//---------------------------------------------------------
// 名称: void WriteDatabase(struct Connection *conn)
// 功能: 写入数据库
// 参数:
//       [struct Connection *conn] --- 数据库连接指针
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月19日
//---------------------------------------------------------
void WriteDatabase(struct Connection *conn)
{
    rewind(conn->file); // 文件指针回退到开始位置

    // 写入数据
    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1)
    {
        Die("Failed to write database.");
    }

    rc = fflush(conn->file);
    if(rc == -1)
    {
        Die("Cannot flush database.");
    }
}

//-----------------------------------------------------------
// 名称: void CreateDatabase(struct Connection *conn)
// 功能: 创建数据库
// 参数:
//       [struct Connection *conn] --- 数据库连接指针
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月19日
//-----------------------------------------------------------
void CreateDatabase(struct Connection *conn)
{
    int i = 0;
    for(i = 0; i < MAX_ROWS; i++)
    {
        // 创建1个数据
        struct Address addr = {.id = i, .set = 0};
        // 为数据库各数据赋值
        conn->db->rows[i] = addr;
    }
}

//-------------------------------------------------------------
// 名称: void SetDatabase(struct Connection *conn, int id,
//                 const char *name, const char *email)
// 功能: 设置数据库中由id指定的数据的值
// 参数:
//       [struct Connection *conn] --- 数据库连接指针
//       [int id] --- 数据id
//       [const char *name] --- 姓名字符串指针
//       [const char *email] --- 邮件字符串指针
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月19日
//-------------------------------------------------------------
void SetDatabase(struct Connection *conn, int id,
                 const char *name, const char *email)
{
    // 指向数据库中id数据
    struct Address *addr = &conn->db->rows[id];
    if(addr->set)
    {
        Die("Already set, delete it first");
    }

    addr->set = 1;

    // 用strncpy函数实现赋值
    char *res = strncpy(addr->name, name, MAX_DATA);
    if(!res)
    {
        Die("Name copy failed");
    }

    res = strncpy(addr->email, email, MAX_DATA);
    if(!res)
    {
        Die("Email copy failed");
    }
}

//--------------------------------------------------------------
// 名称: void GetDatabase(struct Connection *conn, int id)
// 功能: 读取据库中由id指定的数据的值
// 参数:
//       [struct Connection *conn] --- 数据库连接指针
//       [int id] --- 数据id
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月19日
//--------------------------------------------------------------
void GetDatabase(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];
    if(addr->set)
    {
        PrintAddress(addr); // 输出
    }
    else
    {
        Die("ID is not set");
    }
}

//--------------------------------------------------------------
// 名称: void GetDatabase(struct Connection *conn, int id)
// 功能: 删除数据库中由id指定的数据的值
// 参数:
//       [struct Connection *conn] --- 数据库连接指针
//       [int id] --- 数据id
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月19日
// 备注: 仅仅将数据的set字段设置为0
//--------------------------------------------------------------
void DelDatabase(struct Connection *conn, int id)
{
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

//--------------------------------------------------------------
// 名称: void ListDatabase(struct Connection *conn)
// 功能: 输出数据库中所有数据
// 参数:
//       [struct Connection *conn] --- 数据库连接指针
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2019年01月19日
//--------------------------------------------------------------
void ListDatabase(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;
    for(i = 0; i < MAX_ROWS; i++)
    {
        struct Address *cur = &db->rows[i];
        if(cur->set)
        {
            PrintAddress(cur);
        }
    }
}


