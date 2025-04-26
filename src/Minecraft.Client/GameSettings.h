#include "types.h"

class GameSettings {
public:
    static void SetDefaultActionMapping(uchar, int, uchar);
    static int OldProfileVersionCallback(void*, unsigned char*, unsigned short, int);
};