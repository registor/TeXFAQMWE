#include "bmp.h"
#include "run.h"
#include "define.h"
#include "configINI.h"

//convert����ʹ�õĸ�������
//�ҶȻ�
void graylevel(BMP_Data *data);
//ȡ��ͼ��
void subimg(BMP_Data *data);
//����
void draw(BMP_Data *data);
//ͼ�����
void addimg(BMP_Data *data, const char *configName);

//--------------------------------------------------------------
// ���ƣ�void run(const char *configName)
// ���ܣ�����ͼ��
// ������[const char *configName] --- �����ļ���
// ���أ���
// ���ߣ����
// ���ڣ�2013��12��13��
//--------------------------------------------------------------
void run(const char *configName)
{
    char file_name[NAME_LEN + 1];
    char *pstrTemp;

    BMP_Data bmp_data;

    int op_code = 1;

    // ���������ļ����ƣ��������·����Ϣ��
    creat_inputFilePathName(file_name, configName, "in_1");

    puts("����ͼ��...");
    // ����ͼ��
    if( !Load_BMP(file_name, &bmp_data) )
    {
        fprintf(stderr, "����ԭͼ�����!\n");
        exit(EXIT_FAILURE);
    }

    pstrTemp = getKeyValue(configName, "[op_code]", "code");

    op_code = atoi(pstrTemp);

    // ͼ�����
    puts("ͼ����...");
    Convert(op_code, &bmp_data, configName);

    //����INI�����ļ�����Ӧ�����ݣ�����������ļ����ƣ��������·����Ϣ��
    creat_outputFilePathName(file_name, configName, "_ps.bmp");

    puts("�洢������ͼ��...");
    // ����ͼ��
    if( !Save_BMP(file_name, &bmp_data) )
    {
        fprintf(stderr, "�洢������ͼ�����!\n");
        exit(EXIT_FAILURE);
    }

    free( bmp_data.data );
}

//--------------------------------------------------------------
// ���ƣ�void Convert(int type, BMP_Data *data)
// ���ܣ�����24λ���ɫͼ��
// ������[int type] --- ����ʽ
//       [BMP_Data *bmp_data] --- ͼ������ָ��
// ���أ���
// ���ߣ����
// ���ڣ�2010��12��30��
//--------------------------------------------------------------
void Convert(int type, BMP_Data *data, const char *configName)
{
    switch(type)
    {
    case 1: // �ҶȻ�
        graylevel(data);
        break;
    case 2: // ȡ��ͼ��
        subimg(data);
        break;
    case 3: // ����
        draw(data);
        break;
    case 4: // ͼ�����
        addimg(data, configName);
        break;
    default:
        ;
    }
}

//�ҶȻ�
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
            // ��R��G��Bƽ��ֵ
            gray = (temp.r + temp.g + temp.b) / 3;
            temp.r = gray;
            temp.g = gray;
            temp.b = gray;
            SetPixel(x, y, temp, data);
        }
    }

}
//ȡ��ͼ��
void subimg(BMP_Data *data)
{
    int x, y;
    RGB temp;

    BMP_Data tempimg;
    tempimg.width = 256;
    tempimg.height = 256;

    //ʵ��ÿ�д洢�ֽ���
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
//����
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
//ͼ�����
void addimg(BMP_Data *data, const char *configName)
{
    int x, y;
    RGB temp, temp2;

    BMP_Data bmp_name;

    char file_name[NAME_LEN + 1];

    //�����������ļ����ƣ��������·����Ϣ��
    creat_inputFilePathName(file_name, configName, "in_2");

    if( !Load_BMP(file_name, &bmp_name) )
    {
        fprintf(stderr, "����MASKͼ�����!\n");
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
