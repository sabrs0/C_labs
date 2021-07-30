#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
int *mem_alloc(int n)
{
	return malloc(sizeof(int) * n);
}
