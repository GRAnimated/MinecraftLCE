#pragma once

/*

This file contains all of the Switch implementations of Windows/XBOX functions

*/

typedef bool BOOL;
typedef long long LARGE_INTEGER;

BOOL QueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount);

void* XPhysicalAlloc(unsigned long, unsigned long, unsigned long, unsigned int);
void XMemSet128(void*, int, unsigned int);
void XPhysicalFree(void*);

void MemSect(int);

void PIXBeginNamedEvent(float, char const*, ...);
void PIXEndNamedEvent();
