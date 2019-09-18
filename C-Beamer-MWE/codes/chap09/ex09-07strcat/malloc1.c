...
#include <string.h>
...
char *p1;
char *p2= "abcd";

// strlen(p2) + 1确保复制空字符'\0'
size_t len = strlen(p2) + 1;
p1 = (char *)malloc(sizeof(char) * len);
strcpy(p1, p2);
...
free(p1);
p1 = NULL;
...
