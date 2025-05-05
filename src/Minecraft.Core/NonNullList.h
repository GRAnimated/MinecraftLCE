#include "types.h"
#include "Minecraft.World/ArrayWithLength.h"
template <typename T>
class NonNullList : arrayWithLength<T> {
    T baseListItem;  // idk
};