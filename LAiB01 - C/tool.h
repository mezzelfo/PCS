#include <stdio.h>
#include <stdlib.h>

void runtimeError(const char* errmsg);
void* secAlloc(const size_t s);
FILE* secFopenRead(const char* filename);
FILE* secFopenWrite(const char* filename);