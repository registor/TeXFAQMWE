#include <stdio.h>

void ShowOneWord(const char *str);
int GetGBKCode(unsigned char* pBuffer,const char * c);
void ShowWords(const char *str);

/**
  * @brief  main function
  * @param  Nove
  * @retval Nove
  */
int main(void){
    ShowWords("测试汉字显示");
    return 0;
}

/**
  * @brief  Show  multiple Chinese Words
  * @param  str       : point to Chinese location code
  * @retval Nove
  */
void ShowWords(const char *str){
    if(NULL == str)    return;
    while(*str != 0){
        ShowOneWord(str);
        str += 2;
    }
}

/**
  * @brief  Show one Chinese Word
  * @param  str       : point to Chinese location code
  * @retval Nove
  */
void ShowOneWord(const char *str){
    unsigned char buffer[32];
    int i,j;
    unsigned char k;

    GetGBKCode(buffer,str);
    for(i=0;i<16;i++){
        for(j=0;j<8;j++){
            k = buffer[2*i] << j;
            if(k & 0x80){
                printf("*");
            }
            else{
                printf(" ");
            }
        }
        for(j=0;j<8;j++){
            k = buffer[2*i+1] << j;
            if(k & 0x80){
                printf("*");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

/**
  * @brief  Get type matrix from HZLIB.bin based on Chinese location code
  * @param  pBuffer: point to 32 bytes type matrix buffer
  *         c       : point to Chinese location code
  * @retval 0(success)  -1(fail)
  */
int GetGBKCode(unsigned char* pBuffer,const char * c){
    unsigned char High8bit,Low8bit;
    unsigned int pos;
    FILE * fp;

    High8bit=*c;
    Low8bit=*(c+1);

    pos = ((High8bit-0xa0-16)*94+Low8bit-0xa0-1)*2*16;
                                        //get type matrix location

    fp =fopen("HZLIB.bin","r");            //open type matrix file

    if (fp != NULL)
    {
        fseek (fp,pos,SEEK_SET);        //set read start point
        fread(pBuffer,1,32,fp);            //read 32 bytes
        fclose(fp);
        return 0;
    }
    else
        return -1;
}
