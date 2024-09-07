#pragma once

/*

The game uses many functions defined by the Windows/XBOX API. Anything used should be put here

*/

typedef bool BOOL;
typedef long long LARGE_INTEGER;

BOOL QueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount);

void* XPhysicalAlloc(unsigned long, unsigned long, unsigned long, unsigned int);
void XMemSet128(void*, int, unsigned int);
void XPhysicalFree(void*);
