#include "XZPacket.h"

// TODO: Defining the default values anywhere seem to result in the order being swapped in the
// resulting code.
XZPacket::XZPacket() : Packet() {}

XZPacket::XZPacket(char field_28, int x, int z) : Packet(), field_28(field_28), x(x), z(z) {}

int XZPacket::getEstimatedSize() {
    return 10;
}