// 申请size个字节连续内存，返回该区域的首地址
void *malloc(size_t size);

// 申请nmemb * size个字节连续内存，
// 返回该区域的首地址，并进行清零
void *calloc(size_t nmemb, size_t size);

// 申请size个字节连续内存，返回该区域的首地址，
// 将ptr指向的内存的内容得到到新申请的内存中
void *realloc(void *ptr, size_t size);

// ptr为需要释放内存区域的首地址
void free(void *ptr); 
