#ifndef RUN_H_INCLUDED
#define RUN_H_INCLUDED

#include "define.h"

void run(const char *filename, int pixW, int pixH, GETBLOCKFOO pf, const char *lutfile);
char *Image2AsciiArt(BMP_Data *pdata, int pixW, int pixH, const unsigned char *artTab, size_t tabsize, GETBLOCKFOO pf);

#endif // RUN_H_INCLUDED
