#ifndef SAVEDATA_H_INCLUDED
#define SAVEDATA_H_INCLUDED

#include <stdlib.h>
#include "define.h"

size_t saveDataTXT(const char *, Student **, size_t);
size_t saveDataBIN(const char *, Student **, size_t);
size_t checkDataBIN(const char *);

#endif // SAVEDATA_H_INCLUDED
