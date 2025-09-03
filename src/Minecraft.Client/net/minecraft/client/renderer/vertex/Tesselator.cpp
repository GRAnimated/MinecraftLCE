#include "net/minecraft/client/renderer/vertex/Tesselator.h"

#include "NX/Platform.h"

void Tesselator::CreateNewThreadStorage(int unk) {
    Tesselator* tesselator = new Tesselator(unk / 4);
    TlsSetValue(sThreadStorageIndex, tesselator);
}
