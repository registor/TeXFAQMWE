...
#include <string.h>
...
char str1[10] = "abcd";
char str2[10] = "efgh";

size_t len1 = strlen(str1);
size_t len2 = strlen(str2);

char *p = (char*) malloc(len1 + len2 + 1);

memcpy(p, str1, len1);
memcpy(p + len1, str2, len2 + 1);
...
free(p);
p = NULL;
...


