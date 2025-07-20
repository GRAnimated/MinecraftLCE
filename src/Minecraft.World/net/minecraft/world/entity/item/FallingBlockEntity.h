#include "net/minecraft/world/entity/Entity.h"
class FallingBlockEntity : public Entity {
public:
    FallingBlockEntity(Level*, double, double, double, const BlockState*);

    eINSTANCEOF GetType() override;
    void defineSynchedData() override;
    void readAdditionalSaveData(CompoundTag*) override;
    void addAdditonalSaveData(CompoundTag*) override;

    char filler[0x20];
};