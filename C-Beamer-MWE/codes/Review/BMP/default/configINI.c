/**
INI文件名：配置文件.ini
    请注意项目中的配置文件是整个项目共用的。
    其后缀是.ini，例如：端口配置.ini。
格式：
    INI文件由节、键、值组成。
节：
    [section]
参数：（键=值）
    name=value
注解：
    注解使用#号表示，在#号后面的文字，直到该行结尾都全部为注解。
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "define.h"
#include "configINI.h"

//--------------------------------------------------------------
// 名称：void creat_inputFilePathName(char *strFilePathName,
//                                    const char *configfilename,
//                                    const char *key)
// 功能：构建一个包含路径信息的读入图像文件名称
// 参数：[char *strFilePathName] --- 文件名称指针
//       [char *configfilename] --- .ini配置文件文件名
//       [const char *key] --- .ini配置文件键值
// 返回：无
// 作者：耿楠
// 日期：2013年12月13日
//--------------------------------------------------------------
void creat_inputFilePathName(char *strFilePathName, const char *configfilename, const char *key)
{
    char *pstrTemp;

    //读入INI配置文件中相应的数据，并构成输入文件名称（包括相对路径信息）
    pstrTemp = getKeyValue(configfilename, "[img_path]", "in");
    strcpy(strFilePathName, pstrTemp);
    pstrTemp = getKeyValue(configfilename, "[img_name]", key);
    strcat(strFilePathName, pstrTemp);
    strcat(strFilePathName, ".bmp");
}

//--------------------------------------------------------------
// 名称：void creat_outputFilePathName(char *strFilePathName,
//                                     const char *configfilename,
//                                     const char *extName)
// 功能：构建一个包含路径信息的输出文件名称
// 参数：[char *strFilePathName] --- 文件名称指针
//       [char *configfilename] --- .ini配置文件文件名
//       [const char *extName] --- 重命名后缀
// 返回：无
// 作者：耿楠
// 日期：2013年12月13日
//--------------------------------------------------------------
void creat_outputFilePathName(char *strFilePathName, const char *configfilename, const char *extName)
{
    char *pstrTemp;

    //读入INI配置文件中相应的数据，并构成输出文件名称（包括相对路径信息）
    pstrTemp = getKeyValue(configfilename, "[img_path]", "out");
    strcpy(strFilePathName, pstrTemp);
    pstrTemp = getKeyValue(configfilename, "[img_name]", "in_1");
    strcat(strFilePathName, pstrTemp);
    strcat(strFilePathName, extName);
}


//--------------------------------------------------------------
// 名称：char* getKeyValue(const char *filename, const char *section, const char *key)
// 功能：读入.ini配置文件指定节、指定键的键值
// 参数：[char *filename] --- .ini配置文件文件名
//       [char *section] --- 节名称
//       [char *key] --- 键名称
// 返回：char * --- 键值字符串的指针
// 作者：耿楠
// 日期：2010年12月30日
//--------------------------------------------------------------
char* getKeyValue(const char *filename, const char *section, const char *key)
{
    char line[NAME_LEN + 1];
    char sectname[NAME_LEN + 1];

    char *skey, *valu;
    char seps[] = "=";
    bool flag = false;

    //打开配置文件
    FILE *fp = fopen(filename, "r");
    assert(fp != NULL);

    //字符串清0
    memset(line, 0, NAME_LEN + 1);

    //参数处理，节名称左右未加[和]时，为其添加[和]
    if (!strchr(section, '['))
    {
        strcpy(sectname,"[");
        strcat(sectname,section);
        strcat(sectname,"]");
    }
    else
    {
        strcpy(sectname,section);
    }

    while (fgets(line, NAME_LEN, fp) != NULL)
    {
        //查找并返回指向字符在字符串中第1次出现位置的指针。
        valu = strchr(line, '\n');
        //将'\n'替换为'\0'
        *valu = 0;

        if (flag)
        {
            /**
            char *strtok(char s[], const char *delim);
            分解字符串为一组字符串。s为要分解的字符串，delim为分隔符字符串。
            strtok()用来将字符串分割成一个个片段。参数s指向欲分割的 字符串，
            参数delim则为分割字符串中包含的所有字符。
            当strtok()在参数s的字符串中发现参数delim中包涵的分割字符时,
            则会将该字符改为\0 字符。
            在第一次调用时，strtok()必需给予参数s字符串，往后的调用则将参数s设置成NULL。
            每次调用成功则返回指向被分割出片段的指针。
            **/
            //分割出键名称
            skey = strtok(line, seps);
            if (strcmp(skey , key) == 0)
            {
                //返回键值字符串
                return strtok(NULL, seps);
            }
        }
        else
        {
            //找到指定的节
            if (strcmp(sectname,line) == 0)
            {
                //设定读入键值标志
                flag = true;  //find the section
            }

        }
    }

    return NULL;
}
