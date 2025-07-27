#include "net/minecraft/world/entity/Entity.h"
#include <memory>
class ExperienceOrb : public Entity {
public:
    ExperienceOrb(Level*, double, double, double, int);

    ~ExperienceOrb() override;
    eINSTANCEOF GetType() override;
    void defineSynchedData() override;
    void tick() override;
    bool makeStepSound() override;
    void burn(int) override;
    void updateInWaterState() override;
    void getLightColor() override;
    void playerTouch(std::shared_ptr<Player>) override;
    void hurt(DamageSource*, float) override;
    void shouldRender(double) override;
    void readAdditionalSaveData(CompoundTag*) override;
    virtual void addAdditonalSaveData(CompoundTag*) override;
    bool isAttackable() override;

    static int getExperienceValue(int);

    int mTickCount;
    int mAge;
    int mThrowTime;
    int mValue;
    std::shared_ptr<Player> mFollowingPlayer;
    int mFollowingTime;
};