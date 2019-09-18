#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

// 全局变量
int glMax, glMin;

// 数组遍历函数原型
void Traversal(int *, int, void (*pf)(int *));
void RandArray(int *, int);
// 数组遍历功能函数
void Input(int *);
void Output(int *);

// 求最大值函数原型
int GetMax(int, int);

int PreRecursiveMaxWithSize(int *, int); // 前向递归，传入数组长度
int PreRecursiveMaxCom(int *, int); // 前向递归，传入数组长度，采用复合语句
int PreRecursiveMaxContIf(int *, int); // 前向递归，传入数组长度，递归结束在else分支
int PreRecursiveMaxByPt(int *, int); // 前向递归，传入数组长度，通过指针操作数组元素
int PreRecursiveMaxWithIndex(int *, int); // 前向递归，传入最后一个元素下标索引
int PreRecursiveMaxWithInit(int *, int, int); // 前向递归，传入数组最后一个元素下标索引，并用数组的某个元素做为最大值初值
int PreRecursiveMaxByIdx0(int *, int); // 前向递归，传入数组长度，用pa[0]记录最大值
int PreRecursiveMaxDynamicIdx0(int *, int); // 前向递归，传入数组长度，根据情况舍弃pa[0]以缩短数组长度
int PreRecursiveMaxWithNothing(int *, int); // 前向递归，传入数组长度，不改变数组内容，且不使用额外变量
void PreRecursiveMaxWithGlobal(int *, int); // 前向递归，传入数组长度，使用全局变量
int BiRecursiveMax(int *, int); // 二分法递归，传入数组长度
int PostRecursiveMax(int *, int, int); // 后向递归，传入数组长度和起始元素下标索引，
void BiRecursiveMaxMinWithPt(int *, int, int, int*, int*); // 二分法递归求最大最小值
