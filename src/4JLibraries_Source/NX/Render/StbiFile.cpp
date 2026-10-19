#include "NX/Render/TextureUtil.h"

// name guessed
StbiFile* StbiFile::fromUser(void* user) {
    return static_cast<StbiFile*>(user);
}
