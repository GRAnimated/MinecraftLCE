#include "Minecraft.World/entity/Entity.h"
#include <memory>
class DamageSource {
public:
    static DamageSource* BYPASS_ARMOUR;
    static DamageSource* IN_FIRE;
    static DamageSource* WITHER;

    static DamageSource* CreateThorns(std::shared_ptr<Entity>);

    bool isBypassInvul() const;
    bool isFire() const;
    bool isProjectile() const;
    bool isExplosion() const;
};