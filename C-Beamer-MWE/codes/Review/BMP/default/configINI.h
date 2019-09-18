/**-------------------------------------------------------
* Copyright (c) 2010,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：configINI.h
* 文件标识：见配置管理计划书
* 摘要：读入.INI配置文件中指定节、指定键的键值的getKeyValue的函数原型声明。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2013年12月13日
*
* 取代版本：无
* 原作者：无
* 完成日期：无
-------------------------------------------------**/
#ifndef CONFIGINI_H_INCLUDED
#define CONFIGINI_H_INCLUDED

void creat_outputFilePathName(char *strFilePathName, const char *configfilename, const char *extName);

void creat_inputFilePathName(char *strFilePathName, const char *configfilename, const char *key);

char* getKeyValue(const char *filename, const char *section, const char *key);

#endif // CONFIGINI_H_INCLUDED
