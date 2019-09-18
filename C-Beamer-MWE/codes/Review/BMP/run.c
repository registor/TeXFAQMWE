#include "bmp.h"
#include "run.h"
#include "define.h"
#include "configINI.h"

//convert函数使用的辅助函数
//灰度化
void graylevel(BMP_Data *data);
//取子图像
void subimg(BMP_Data *data);
//画线
void draw(BMP_Data *data);
//图像叠加
void addimg(BMP_Data *data, const char *configName);

//--------------------------------------------------------------
// 名称：void run(const char *configName)
// 功能：处理图像
// 参数：[const char *configName] --- 配置文件名
// 返回：无
// 作者：耿楠
// 日期：2013年12月13日
//--------------------------------------------------------------
void run(const char *configName)
{
    char file_name[NAME_LEN + 1];
    char *pstrTemp;

    BMP_Data bmp_data;

    int op_code = 1;

    // 构成输入文件名称（包括相对路径信息）
    creat_inputFilePathName(file_name, configName, "in_1");

    puts("读入图像...");
    // 读入图像
    if( !Load_BMP(file_name, &bmp_data) )
    {
        fprintf(stderr, "读入原图像出错!\n");
        exit(EXIT_FAILURE);
    }

    pstrTemp = getKeyValue(configName, "[op_code]", "code");

    op_code = atoi(pstrTemp);

    // 图像叠加
    puts("图像处理...");
    Convert(op_code, &bmp_data, configName);

    //读入INI配置文件中相应的数据，并构成输出文件名称（包括相对路径信息）
    creat_outputFilePathName(file_name, configName, "_ps.bmp");

    puts("存储处理后的图像...");
    // 读入图像
    if( !Save_BMP(file_name, &bmp_data) )
    {
        fprintf(stderr, "存储处理后的图像出错!\n");
        exit(EXIT_FAILURE);
    }

    free( bmp_data.data );
}

//--------------------------------------------------------------
// 名称：void Convert(int type, BMP_Data *data)
// 功能：读入24位真彩色图像
// 参数：[int type] --- 处理方式
//       [BMP_Data *bmp_data] --- 图像数据指针
// 返回：无
// 作者：耿楠
// 日期：2010年12月30日
//--------------------------------------------------------------
void Convert(int type, BMP_Data *data, const char *configName)
{
    switch(type)
    {
    case 1: // 灰度化
        graylevel(data);
        break;
    case 2: // 取子图像
        subimg(data);
        break;
    case 3: // 画线
        draw(data);
        break;
    case 4: // 图像叠加
        addimg(data, configName);
        break;
    default:
        ;
    }
}

//灰度化
void graylevel(BMP_Data *data)
{
    int x, y;
    RGB temp;
    int gray;

    for(y = 0; y < data->height; y++)
    {
        for(x = 0; x < data->width; x++)
        {
            temp = GetPixel(x, y, data);
            // 求R、G、B平均值
            gray = (temp.r + temp.g + temp.b) / 3;
            temp.r = gray;
            temp.g = gray;
            temp.b = gray;
            SetPixel(x, y, temp, data);
        }
    }

}
//取子图像
void subimg(BMP_Data *data)
{
    int x, y;
    RGB temp;

    BMP_Data tempimg;
    tempimg.width = 256;
    tempimg.height = 256;

    //实际每行存储字节数
    tempimg.widthbytes = ((tempimg.width * 3) % 4 == 0) ?
                         (tempimg.width * 3) : ((tempimg.width * 3) / 4 * 4 + 4);
    tempimg.data = (unsigned char *)malloc(tempimg.widthbytes * tempimg.height);

    for(y = 50; y < 50 + tempimg.height; y++)
    {
        for(x = 50; x < 50 + tempimg.width; x++)
        {
            temp = GetPixel(x, y, data);
            SetPixel(x - 50, y - 50, temp, &tempimg);
        }
    }
    data->height = tempimg.height;
    data->width = tempimg.width;
    data->widthbytes = tempimg.widthbytes;
    free(data->data);
    data->data = tempimg.data;
}
//画线
void draw(BMP_Data *data)
{
    int x;
    RGB temp;

    temp.r = 255;
    temp.g = 0;
    temp.b = 0;

    for(x = 0; x < data->width; x++)
    {
        SetPixel(x, x, temp, data);
        SetPixel(x, data->width - x, temp, data);
    }

}
//图像叠加
void addimg(BMP_Data *data, const char *configName)
{
    int x, y;
    RGB temp, temp2;

    BMP_Data bmp_name;

    char file_name[NAME_LEN + 1];

    //并构成输入文件名称（包括相对路径信息）
    creat_inputFilePathName(file_name, configName, "in_2");

    if( !Load_BMP(file_name, &bmp_name) )
    {
        fprintf(stderr, "读入MASK图像出错!\n");
        exit(EXIT_FAILURE);
    }

    for(y = 0; y < data->height; y++)
    {
        for(x = 0; x < data->width; x++)
        {
            temp = GetPixel(x, y, data);
            temp2 = GetPixel(x, y, &bmp_name);

            if(temp2.r == 0)
            {
                temp.r *= 0.5;
                temp.g *= 0.5;
                temp.b *= 0.5;
            }

            SetPixel(x, y, temp, data);
        }
    }
    free(bmp_name.data);
}
