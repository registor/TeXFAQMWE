#include "bmp.h"
#include "run.h"
#include "define.h"

//---------------------------------------------------------------------
// 名称：void run(const char *filename, int pixW, int pixH,
//                           GETBLOCKFOO pf, const char *lutfile)
// 功能：处理图像
// 参数：
//           [const char *filename] --- 图像文件名
//           [int pixW] --- 需要处理成单个字符的区块宽度
//           [int pixH] --- 需要处理成单个字符的区块高度
//           [GETBLOCKFOO pf] --- 处理区块数据的函数指针
//           [const char *lutfile] --- 转换字符查找表文件名称
// 返回：无
// 作者：耿楠
// 日期：2019年1月15日
//---------------------------------------------------------------------
void run(const char *filename, int pixW, int pixH,
         GETBLOCKFOO pf, const char *lutfile)
{
    // 声明图像对象
    BMP_Data bmp_data;

    // 读入图像
    if(!Load_BMP(filename, &bmp_data))
    {
        fprintf(stderr, "读入原图像出错!\n");
        exit(EXIT_FAILURE);
    }

    // 图像数据垂直翻转(BMP数据是上下颠倒的)
    FlipUpDown(&bmp_data);

    // 开始转换
    char *p_art;
    if(lutfile == NULL)
    {
        // 未指定查找表文件，用默认查找表(1维数组)
        p_art = Image2AsciiArt(&bmp_data, pixW, pixH,
                               ascii_char_table2, sizeof(ascii_char_table2), pf);
    }
    else
    {
        // 打开转换字符查找表文件
        FILE *lutfp = fopen(lutfile, "r");
        if(!lutfp)
        {
            fprintf(stderr, "转换字符查找表出错!\n");
            exit(EXIT_FAILURE);
        }

        // 获取转换查找表长度
        int cnt = 0;
        int ch = fgetc(lutfp);
        while(ch != '\n' && ch != EOF)
        {
            cnt++;
            ch = fgetc(lutfp);
        }

        if(cnt == 0)
        {
            // 查找表文件中无数据，用默认查找表(1维数组)
            p_art = Image2AsciiArt(&bmp_data, pixW, pixH,
                                   ascii_char_table2, sizeof(ascii_char_table2), pf);
        }
        else
        {
            // 文件回退到开始位置
            rewind(lutfp);
            unsigned char *plut = malloc(cnt * sizeof(char));
            if(plut == NULL)
            {
                fprintf(stderr, "内存不足!\n");
                exit(EXIT_FAILURE);
            }
            // 读入转换字符查找表
            for(int i = 0; i < cnt; i++)
            {
                plut[i] = fgetc(lutfp);
            }
            p_art = Image2AsciiArt(&bmp_data, pixW, pixH, plut, cnt, pf);
            free(plut);
        }
    }

    // 提取出主文件名
    char *pstr = malloc((strlen(filename) + 1) * sizeof(char));
    if(pstr == NULL)
    {
        fprintf(stderr, "内存不足!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(pstr, filename);

    // 根据'.'找到分割主文件名和扩展名
    char *ptok = strtok(pstr, ".");
    if(ptok == NULL)
    {
        fprintf(stderr, "构造输出文件名称出错!\n");
        exit(EXIT_FAILURE);
    }

    // 构造输出文件名
    int len = strlen(ptok);
    char ext[] = "_art.txt";
    len += strlen(ext);
    char *outfile = malloc((len + 1) * sizeof(char));
    if(outfile == NULL)
    {
        fprintf(stderr, "内存不足\n");
        exit(EXIT_FAILURE);
    }
    memset(outfile, 0, (len + 1) * sizeof(char));

    strcat(outfile, ptok);
    strcat(outfile, ext);

    FILE *fp = fopen(outfile, "w");
    if(fp == NULL)
    {
        fprintf(stderr, "无法创建输出结果文件!\n");
        exit(EXIT_FAILURE);
    }

    // AsciiArt结果尺寸
    int artW = bmp_data.width / pixW;
    int artH = bmp_data.height / pixH;

    // 输出结果
    for(int i = 0; i < artH; i ++)
    {
        for(int j = 0; j < artW; j++)
        {
            putchar(p_art[j + i * artW]); // 屏幕输出
            putc(p_art[j + i * artW], fp); // 文件输出
        }
        printf("\n"); // 屏幕输出
        putc('\n', fp); // 文件输出
    }

    // 释放内存
    fclose(fp);
    free(pstr);
    free(outfile);
    free(p_art);
    free(bmp_data.data);
}

//---------------------------------------------------------------------------------------------
// 名称：char *Image2AsciiArt(BMP_Data *pdata, int pixW, int pixH,
//                                                const unsigned  char *artTab, size_t tabsize,
//                                                GETBLOCKFOO pf)
// 功能：将24位真彩色图像转换为ASCII字符艺术图像
// 算法：取出指定区块的像素，然后由pf指定的函数计算后确定要转换成的字符。
// 参数：
//           [BMP_Data *bmp_data] --- 图像数据指针
//           [int pixW] --- 需要处理成单个字符的区块宽度
//           [int pixH] --- 需要处理成单个字符的区块高度
//           [const unsigned  char *artTab] --- 转换字符查找表
//           [size_t tabsize] --- 转换字符查找表长度
//           [GETBLOCKFOO pf] --- 处理区块数据的函数指针
// 返回：[char*] --- 结果字符数组的首地址
// 作者：耿楠
// 日期：2019年1月15日
// 备注：该函数动态申请了结果字符数组，注意使用后用free()进行释放。
//---------------------------------------------------------------------------------------------
char *Image2AsciiArt(BMP_Data *pdata, int pixW, int pixH,
                     const unsigned char *artTab, size_t tabsize, GETBLOCKFOO pf)
{
    // 区块总像素个数
    int pixsize = pixW * pixH;

    // AsciiArt结果尺寸
    int artW = pdata->width / pixW;
    int artH = pdata->height / pixH;
    size_t artsize = artW * artH;

    // 申请保存AsciiArt结果的内存空间
    char *p_art = malloc(artsize * sizeof(char));
    if(p_art == NULL)
    {
        fprintf(stderr, "内存不足!\n");
        exit(EXIT_FAILURE);
    }
    // 初始化
    memset(p_art, 0, artsize * sizeof(char));

    // 申请保存图像区块数据的内存空间
    unsigned char *p_block = malloc(pixsize * 3 * sizeof(unsigned char));
    if(p_block == NULL)
    {
        fprintf(stderr, "内存不足!\n");
        exit(EXIT_FAILURE);
    }
    // 初始化
    memset(p_block, 0, pixsize * 3 * sizeof(unsigned char));

    // 图像数据处理
    for(int h = 0; h < artH; h++)
    {
        // 区块起始行
        int startY = h * pixH;
        // 区块起始行地址
        unsigned char *ptemp = pdata->data + startY * pdata->widthbytes;
        for(int w = 0; w < artW; w++)
        {
            // 区块起始列
            int startX = w * pixW;
            // 定位到行首
            unsigned char *q = ptemp;
            // 定位到区块起始列
            q += startX * 3;

            // 读取区块数据
            unsigned char *pb = p_block;
            for(int y = 0; y < pixH; y++)
            {
                // 区块当前行首地址
                q += y * pdata->widthbytes;
                // 复制一行数据
                memcpy(pb, q, pixW * 3);
                // 区块数据定位
                pb += (pixW * 3);
            }
            // 计算区块灰度平均值作为字符查找表下标
            double level = pf(p_block, pixW, pixH);
            int idx = (int)((tabsize - 1) * level + 0.5);
            char *p = p_art + w + h * artW;
            // 为结果字符串数组赋值
            *p = artTab[idx];
        }
    }

    // 释放内存
    free(p_block);

    return p_art;
}
