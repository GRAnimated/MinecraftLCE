#include "Minecraft.World/entity/Entity.h"
#include <memory>
class DamageSource {
public:
    static const DamageSource* BYPASS_ARMOUR;

    static DamageSource* CreateThorns(std::shared_ptr<Entity>);

    bool isBypassInvul() const;
    bool isFire() const;
    bool isProjectile() const;
    bool isExplosion() const;
};