#include "net/minecraft/client/renderer/vertex/Tesselator.h"

#include "NX/Platform.h"
#include "net/minecraft/client/renderer/vertex/BufferBuilder.h"

Tesselator* Tesselator::getInstance() {
    return static_cast<Tesselator*>(TlsGetValue(sThreadStorageIndex));
}

void Tesselator::CreateNewThreadStorage(int unk) {
    Tesselator* tesselator = new Tesselator(unk / 4);
    TlsSetValue(sThreadStorageIndex, tesselator);
}

Tesselator::Tesselator(int unk) {
    m_padding = ::operator new(1);  // idk a better way, padding is probably a class/struct with no fields
    m_builder = new BufferBuilder(unk);
}

BufferBuilder* Tesselator::getBuilder() const {
    return m_builder;
}

void Tesselator::end() {
    m_builder->end();
}
