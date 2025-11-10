#include "net/minecraft/client/renderer/vertex/Tesselator.h"
#include "net/minecraft/client/renderer/vertex/BufferBuilder.h"
#include "NX/Platform.h"


Tesselator* Tesselator::getInstance() {
    return static_cast<Tesselator*>(TlsGetValue(sThreadStorageIndex));
}

void Tesselator::CreateNewThreadStorage(int unk) {
    Tesselator* tesselator = new Tesselator(unk / 4);
    TlsSetValue(sThreadStorageIndex, tesselator);
}

Tesselator::Tesselator(int unk) {
    padding = ::operator new(1);  // idk a better way, padding is probably a class/struct with no fields
    builder = new BufferBuilder(unk);
}

BufferBuilder* Tesselator::getBuilder() const {
    return builder;
}

void Tesselator::end() {
    builder->end();
}
