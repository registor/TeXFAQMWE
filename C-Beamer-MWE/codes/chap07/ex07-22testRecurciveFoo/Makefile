# 该 Makefile 用于编译一个多文件结构的C语言程序工程
# 运行环境：Windows、MingW32
# 需要将MingW32的bin路径添加到Windows的环境变量中

# 路径变量
DIR_INC = ./
DIR_SRC = ./
DIR_OBJ = ./obj
DIR_BIN = ./bin


SRC = $(wildcard ${DIR_SRC}/*.c)  
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC})) 

TARGET = main

BIN_TARGET = ${TARGET}

CC = gcc
CFLAGS =  -Wall -I${DIR_INC} -std=c99

${BIN_TARGET}:${OBJ}
	$(CC) $(OBJ)  -o $@
    
${DIR_OBJ}/%.o:${DIR_SRC}/%.c
	$(CC) $(CFLAGS) -c  $< -o $@

clean:
	del obj\\*.o  && del ${BIN_TARGET}


# wildcard : 扩展通配符
#　notdir ： 去除路径
#　patsubst ：替换通配符
#　　$@  表示目标文件
#　　$^  表示所有的依赖文件
#　　$<  表示第一个依赖文件
#　　$?  表示比目标还要新的依赖文件列表
