#include "types.h"
#include "Minecraft.World/entity/LivingEntity.h"
#include "Minecraft.World/entity/projectile/Arrow.h"
#include "Minecraft.World/item/ItemInstance.h"
#include <memory>

class TippableArrow : public Arrow {
public:
    TippableArrow(Level*, std::shared_ptr<LivingEntity>);

    void setEffectsFromItem(not_null_ptr<ItemInstance> const&);
};