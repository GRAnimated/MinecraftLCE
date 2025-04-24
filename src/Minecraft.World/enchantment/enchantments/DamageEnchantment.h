#include "Minecraft.World/enchantment/Enchantment.h"

class DamageEnchantment : public Enchantment {
public:
    DamageEnchantment(const Rarity*, int, arrayWithLength<const EquipmentSlot*>);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
    float getDamageBonus(int, MobType) override;
    bool checkCompatibility(Enchantment const*) override;
    int getDescriptionId() override;
    bool canEnchant(const not_null_ptr<ItemInstance>&) override;
    void doPostAttack(const std::shared_ptr<LivingEntity>&, const std::shared_ptr<Entity>&, int) override;

    int mDamageType;

private:
    static constexpr int MIN_COST[3] = {1, 5, 5};
    static constexpr int LEVEL_COST[3] = {11, 8, 8};
    static constexpr int LEVEL_COST_2[3] = {20, 20, 20};
    static constexpr unsigned int NAME_IDS[3] = {0xCA0651FF, 0xBD9225A1, 0xC99DAC4};
};