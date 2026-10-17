#include "NX/Render/TextureUtil.h"

StbiFile* StbiFile::fromUser(void* user) {
    return static_cast<StbiFile*>(user);
}
