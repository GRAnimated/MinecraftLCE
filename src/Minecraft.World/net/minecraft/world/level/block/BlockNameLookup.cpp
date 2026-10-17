#include "net/minecraft/resources/ResourceLocation.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include <cwchar>

class Integer {
public:
    static int parseInt(const std::wstring&, int base);
};

int Integer::parseInt(const std::wstring& value, int base) {
    return static_cast<int>(std::wcstol(value.c_str(), nullptr, base));
}

Block* Blocks::byString(const std::wstring& name) {
    ResourceLocation location(name);
    if (Registry->containsKey(location))
        return Registry->get(location);
    return Registry->byId(Integer::parseInt(name, 10));
}
