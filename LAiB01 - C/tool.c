#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

void runtimeError(const char* errmsg)
{
	fprintf(stderr,"%s\n",errmsg);
	exit(EXIT_FAILURE);
}

void* secAlloc(const size_t s)
{
	void* ptr = malloc(s);
	if (ptr == NULL)
		runtimeError("Errore durante l'allocazione della memoria");
	return ptr;
}

FILE* secFopenRead(const char* filename)
{
    FILE* f = fopen(filename,"r");
    if (f == NULL)
        runtimeError("Errore durante l'apertura del file");
    return f;
}

FILE* secFopenWrite(const char* filename)
{
    FILE* f = fopen(filename,"w");
    if (f == NULL)
        runtimeError("Errore durante l'apertura del file");
    return f;
}