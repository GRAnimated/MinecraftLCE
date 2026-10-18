#include "net/minecraft/world/level/storage/light/SparseLightStorage.h"

#include "NX/Platform.h"
#include "java/io/DataInputStream.h"
#include <cstdlib>
#include <cstring>

// Inferred name for the original allocation accounting word at 0x71017a44c0.
int gSparseLightAllocatedBytes;

// Separate original memset trampoline at 0x71006910fc (inferred name).
void sparseLightMemSet(void* buffer, int value, std::size_t bytes) {
    std::memset(buffer, value, bytes);
}

namespace {
const unsigned long long PointerMask = 0x0000ffffffffffffULL;
}

unsigned char* SparseLightStorage::allocate(unsigned int bytes) {
    unsigned char* buffer = static_cast<unsigned char*>(std::malloc(bytes));
    gSparseLightAllocatedBytes += bytes;
    return buffer;
}

void SparseLightStorage::freeBuffer(unsigned char* buffer, int bytes) {
    std::free(buffer);
    gSparseLightAllocatedBytes -= bytes;
}

SparseLightStorage::SparseLightStorage(bool bright) {
    unsigned char* buffer = allocate(0x4000);
    buffer[127] = bright ? 0x81 : 0x80;
    for (int i = 0; i < 127; ++i)
        buffer[i] = i;
    // Even the bright variant starts its explicit slabs with zero light.
    // Original 0x71006910fc is a separate memset trampoline with this ABI.
    sparseLightMemSet(buffer + 128, 0, 0x3f80);
    __atomic_store_n(&m_packed, (reinterpret_cast<unsigned long long>(buffer) & PointerMask) | (127ULL << 48),
                     __ATOMIC_SEQ_CST);
}

SparseLightStorage::SparseLightStorage(bool bright, bool) {
    unsigned char* buffer = allocate(128);
    for (int i = 0; i != 128; i += 4) {
        unsigned char value = bright ? 0x81 : 0x80;
        buffer[i] = value;
        buffer[i + 1] = value;
        buffer[i + 2] = value;
        buffer[i + 3] = value;
    }
    __atomic_store_n(&m_packed, reinterpret_cast<unsigned long long>(buffer) & PointerMask, __ATOMIC_SEQ_CST);
}

int SparseLightStorage::bufferSize(unsigned long long packed) {
    return ((packed >> 41) & 0x7fff80) + 128;
}

SparseLightStorage::SparseLightStorage(const SparseLightStorage& other) {
    unsigned long long packed = __atomic_load_n(&other.m_packed, __ATOMIC_SEQ_CST);
    unsigned char* source = reinterpret_cast<unsigned char*>(packed & PointerMask);
    unsigned int bytes = bufferSize(packed);
    unsigned char* buffer = allocate(bytes);
    __atomic_store_n(&m_packed,
                     (packed & ~PointerMask) | (reinterpret_cast<unsigned long long>(buffer) & PointerMask),
                     __ATOMIC_SEQ_CST);
    XMemCpy(buffer, source, static_cast<int>(bytes));
}

SparseLightStorage::~SparseLightStorage() {
    unsigned char* buffer
        = reinterpret_cast<unsigned char*>(__atomic_load_n(&m_packed, __ATOMIC_SEQ_CST) & PointerMask);
    int bytes = bufferSize(__atomic_load_n(&m_packed, __ATOMIC_SEQ_CST));
    __atomic_store_n(&m_packed, 0ULL, __ATOMIC_SEQ_CST);
    freeBuffer(buffer, bytes);
}

void SparseLightStorage::getBuffers(unsigned char** indices, unsigned char** data) {
    unsigned long long packed = __atomic_load_n(&m_packed, __ATOMIC_SEQ_CST);
    *indices = reinterpret_cast<unsigned char*>(packed & PointerMask);
    *data = *indices + 128;
}

void SparseLightStorage::replace(unsigned long long packed) {
    unsigned long long old;
    do {
        old = __atomic_load_n(&m_packed, __ATOMIC_SEQ_CST);
    } while (!__atomic_compare_exchange_n(&m_packed, &old, packed, true, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));
    retire(reinterpret_cast<unsigned char*>(old & PointerMask));
}

void SparseLightStorage::fromNibbles(arrayWithLength<unsigned char> source, int offset) {
    unsigned char indices[128];
    unsigned int slabs = 0;
    for (int y = 0; y != 128; ++y) {
        unsigned int zero = 1;
        unsigned int full = 1;
        for (unsigned int xz = 0; xz != 0x8000; xz += 128) {
            unsigned char value = (source[offset + ((xz | y) >> 1)] >> ((y & 1) << 2)) & 15;
            zero &= value == 0;
            full &= value == 15;
        }
        unsigned int uniform = zero | full;
        indices[y] = uniform ? (zero ? 0x80 : 0x81) : slabs;
        slabs += uniform ^ 1;
    }
    unsigned char* buffer = allocate(slabs * 128 + 128);
    unsigned char* slab = buffer + 128;
    XMemCpy(buffer, indices, 128);
    for (int y = 0; y != 128; ++y) {
        if (static_cast<signed char>(buffer[y]) >= 0) {
            unsigned char* input = &source[offset + (y >> 1)];
            int shift = (y & 1) << 2;
            for (int i = 0; i != 128; i += 2) {
                slab[i] = (input[0] >> shift) & 15;
                slab[i] |= (input[0x40] >> shift) << 4;
                slab[i + 1] = (input[0x80] >> shift) & 15;
                slab[i + 1] |= (input[0xc0] >> shift) << 4;
                input += 0x100;
            }
            slab += 128;
        }
    }
    replace((reinterpret_cast<unsigned long long>(buffer) & PointerMask)
            | (static_cast<unsigned long long>(slabs) << 48));
}

void SparseLightStorage::toNibbles(arrayWithLength<unsigned char> output, unsigned int offset) {
    sparseLightMemSet(output.m_data + offset, 0, 0x4000);
    unsigned char* indices;
    unsigned char* data;
    getBuffers(&indices, &data);
    for (int y = 0; y != 128; ++y) {
        unsigned char index = indices[y];
        if (index == 0x80)
            continue;
        unsigned char* target = output.m_data + (offset + (y >> 1));
        int shift = (y & 1) << 2;
        if (index == 0x81) {
            unsigned char value = 15 << shift;
            for (int i = 0; i != 0x4000; i += 0x100) {
                target[i] |= value;
                target[i + 0x40] |= value;
                target[i + 0x80] |= value;
                target[i + 0xc0] |= value;
            }
        } else {
            const unsigned char* slab = data + index * 128;
            for (int i = 0; i != 128; ++i) {
                target[0] |= (slab[i] & 15) << shift;
                target[0x40] |= (slab[i] >> 4) << shift;
                target += 0x80;
            }
        }
    }
}

unsigned char SparseLightStorage::getLight(int x, int y, int z) {
    unsigned char* indices;
    unsigned char* data;
    getBuffers(&indices, &data);
    unsigned char index = indices[y];
    if (index == 0x80)
        return 0;
    if (index == 0x81)
        return 15;
    int xz = x * 16 + z;
    int offset = xz / 2;
    return (data[(static_cast<unsigned long long>(index) << 7) + offset] >> ((xz & 1) << 2)) & 15;
}

unsigned int SparseLightStorage::compress() {
    unsigned long long packed = __atomic_load_n(&m_packed, __ATOMIC_SEQ_CST);
    unsigned char* old = reinterpret_cast<unsigned char*>(packed & PointerMask);
    unsigned char indices[128];
    unsigned int changed = 0;
    unsigned int slabs = 0;
    for (int y = 0; y != 128; ++y) {
        unsigned char index = old[y];
        if (static_cast<signed char>(index) >= -126) {
            unsigned int zero = 1;
            unsigned int full = 1;
            unsigned char* slab = old + 128 + index * 128;
            for (int i = 0; i != 128; i += 4) {
                zero &= (slab[i] == 0) & (slab[i + 1] == 0) & (slab[i + 2] == 0) & (slab[i + 3] == 0);
                full &= ((slab[i] & slab[i + 1]) == 255) & ((slab[i + 2] & slab[i + 3]) == 255);
            }
            unsigned int uniform = zero | full;
            index = uniform ? (zero ? 0x80 : 0x81) : slabs;
            slabs += uniform ^ 1;
            changed |= uniform;
        }
        indices[y] = index;
    }
    if (!changed)
        return packed >> 48;
    unsigned char* buffer = allocate(slabs * 128 + 128);
    unsigned char* target = buffer + 128;
    XMemCpy(buffer, indices, 128);
    for (int y = 0; y != 128; ++y) {
        if (static_cast<signed char>(buffer[y]) >= 0) {
            XMemCpy(target, old + 128 + old[y] * 128, 128);
            target += 128;
        }
    }
    unsigned long long replacement = (reinterpret_cast<unsigned long long>(buffer) & PointerMask)
                                     | (static_cast<unsigned long long>(slabs) << 48);
    bool success = __atomic_compare_exchange_n(&m_packed, &packed, replacement, true, __ATOMIC_SEQ_CST,
                                               __ATOMIC_SEQ_CST);
    retire(success ? old : buffer);
    // The computed count is returned even when another writer wins the exchange.
    return slabs;
}

bool SparseLightStorage::isCompressed() {
    return static_cast<unsigned short>(__atomic_load_n(&m_packed, __ATOMIC_SEQ_CST) >> 48) < 127;
}

void SparseLightStorage::write(DataOutputStream* out) {
    unsigned long long packed = __atomic_load_n(&m_packed, __ATOMIC_SEQ_CST);
    unsigned int slabs = packed >> 48;
    out->writeInt(slabs);
    unsigned long long current = __atomic_load_n(&m_packed, __ATOMIC_SEQ_CST);
    arrayWithLength<unsigned char> bytes(reinterpret_cast<unsigned char*>(current & PointerMask),
                                         static_cast<unsigned short>(slabs) * 128 + 128);
    out->write(bytes);
}

void SparseLightStorage::read(DataInputStream* in) {
    unsigned long long slabs = static_cast<unsigned long long>(in->readInt());
    unsigned int bytes = static_cast<int>(slabs) * 128 + 128;
    unsigned char* buffer = allocate(bytes);
    arrayWithLength<unsigned char> data(buffer, bytes);
    in->readBytes(data);
    replace((reinterpret_cast<unsigned long long>(buffer) & PointerMask) | (slabs << 48));
}
