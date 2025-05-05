#include "Minecraft.World/ArrayWithLength.h"
template <typename T>
class NonNullList : arrayWithLength<T> {
    T baseListItem;  // idk if this should be not_null_ptr by default or specified in template
};