#pragma once

#include <memory>

#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/sounds/SoundSource.h"

class Player;
class Level;
class BlockPos;
class BlockState;
class SoundEvent;
class Entity;
enum ePARTICLE_TYPE {};  // TODO: Move this

class LevelListener {
public:
    virtual ~LevelListener();
    virtual void blockChanged(Level*, const BlockPos&, const BlockState*, const BlockState*, int, bool);
    virtual void blockLightChanged(const BlockPos&);
    virtual void setBlocksDirty(int, int, int, int, int, int, Level*);
    virtual void allChanged();
    virtual void playStreamingMusic(const SoundEvent*, const BlockPos&, bool);
    virtual void playSoundToAllPlayers(const SoundEvent*, SoundSource::ESoundSource, double, double, double,
                                       float, float, float);
    virtual void playSound(std::shared_ptr<Player>, const SoundEvent*, SoundSource::ESoundSource, double,
                           double, double, float, float, float);
    virtual void addParticle(ePARTICLE_TYPE, bool, double, double, double, double, double, double,
                             arrayWithLength<int>);
    virtual void addParticle(ePARTICLE_TYPE, bool, bool, double, double, double, double, double, double,
                             arrayWithLength<int>);
    virtual void entityAdded(std::shared_ptr<Entity>);
    virtual void entityRemoved(std::shared_ptr<Entity>);
    virtual void playerRemoved(std::shared_ptr<Entity>);
    virtual void globalLevelEvent(int, const BlockPos&, int);
    virtual void levelEvent(std::shared_ptr<Player>, int, const BlockPos&, int);
    virtual void destroyBlockProgress(int, const BlockPos&, int);
};
