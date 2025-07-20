#include "com/mojang/blaze3d/vertex/Tesselator.h"

#include "NX/Platform.h"

void Tesselator::CreateNewThreadStorage(int unk) {
    Tesselator* tesselator = new Tesselator(unk / 4);
    TlsSetValue(sThreadStorageIndex, tesselator);
}
