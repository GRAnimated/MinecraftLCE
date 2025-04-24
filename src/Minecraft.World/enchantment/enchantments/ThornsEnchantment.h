#include "Minecraft.World/enchantment/Enchantment.h"
#include "Minecraft.World/item/ItemInstance.h"
#include <memory>
class ThornsEnchantment : public Enchantment {
public:
    ThornsEnchantment(const Rarity*, arrayWithLength<const EquipmentSlot*>);

    static bool shouldHit(int, Random*);
    static int getDamage(int, Random*);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
    bool canEnchant(not_null_ptr<ItemInstance> const&) override;
    void doPostHurt(const std::shared_ptr<LivingEntity>&, const std::shared_ptr<Entity>&, int) override;
};