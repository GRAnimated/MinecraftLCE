#pragma once

/*

This file contains all of the Switch implementations of Windows/XBOX functions

*/

#include <nn/os.h>

typedef bool BOOL;
typedef long long LARGE_INTEGER;

BOOL QueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount);

void* XPhysicalAlloc(unsigned long, unsigned long, unsigned long, unsigned int);
void XMemSet128(void*, int, unsigned int);
void XPhysicalFree(void*);

void MemSect(int);

void PIXBeginNamedEvent(float, char const*, ...);
void PIXEndNamedEvent();

// this should be in System.h shouldn't it????
// or should stuff from System.h be moved here
void EnterCriticalSection(nn::os::MutexType* mutex);
void LeaveCriticalSection(nn::os::MutexType* mutex);

// NON_MATCHING
enum _XMEMCODEC_TYPE {
    PLACEHOLDER = 1,
};

int XMemCreateCompressionContext(_XMEMCODEC_TYPE type, const void* param_2, unsigned int param_3,
                                 void** param_4);
int XMemCreateDecompressionContext(_XMEMCODEC_TYPE type, const void* param_2, unsigned int param_3,
                                   void** param_4);
void XMemDestroyCompressionContext(void* ctxt);
void XMemDestroyDecompressionContext(void* ctxt);

unsigned int TlsAlloc();
int TlsFree(unsigned int unk);
void* TlsGetValue(unsigned int index);
int TlsSetValue(unsigned int index, void* value);