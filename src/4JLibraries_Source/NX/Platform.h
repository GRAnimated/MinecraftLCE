#pragma once

/*

This file contains all of the Switch implementations of Windows/XBOX functions

*/

#include <cstdlib>
#include <nn/os.h>

typedef bool BOOL;
typedef long long LARGE_INTEGER;

BOOL QueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount);

void* XPhysicalAlloc(unsigned long, unsigned long, unsigned long, unsigned int);
void XMemSet128(void*, int, size_t);
void XPhysicalFree(void*);

void MemSect(int);

void PIXBeginNamedEvent(float, const char*, ...);
void PIXEndNamedEvent();
void PIXSetMarkerDeprecated(float, const char*, ...);

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

// the last argument is 32 bit on Wii U Edition, but 64 bit on Switch, so I bet it's a size_t
void XMemCpy(void* buf, const void* data, size_t size);

unsigned int TlsAlloc();
int TlsFree(unsigned int unk);
void* TlsGetValue(unsigned int index);
int TlsSetValue(unsigned int index, void* value);

int OpenDir(const char*, int*);
int ReadDir(int*, struct FSDirEntry*);  // TODO: what is FSDirEntry?
int CloseDir(int*);

void* gfx_aligned_alloc(ulong a1, ulong a2, void*);
void gfx_free(void* ptr, void*);
void* gfx_realloc(void* ptr, ulong, void*);
