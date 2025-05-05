#include "Minecraft.World/entity/Entity.h"
#include "Minecraft.Core/Direction.h"
#include <memory>
class DamageSource {
public:
    static const DamageSource* BYPASS_ARMOUR;
    static DamageSource* IN_FIRE;

    static DamageSource* CreateThorns(std::shared_ptr<Entity>);

    virtual ~DamageSource();
    virtual Direction* getDirectionEntity();
    virtual Entity* getEntity();
    virtual void scalesWithDifficulty();
    virtual void getDeathMessagePacket(std::shared_ptr<LivingEntity>);
    virtual void getSourcePosition();
    virtual void copy();
    virtual void GetBaseDamageSource();

    bool isBypassInvul() const;
    bool isFire() const;
    bool isProjectile() const;
    bool isExplosion() const;
};