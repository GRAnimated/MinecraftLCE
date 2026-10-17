// These two legacy Windows adapters really are constant-return stubs in the
// Switch executable (0x71006081f0 and 0x7100608514). Do not use them on PC.
#include "java/io/File.h"

int DeleteFileA(const char*) {
    return 0;
}

bool WriteFile(nn::fs::FileHandle*, const void*, unsigned int, unsigned int*, _OVERLAPPED*) {
    return true;
}
