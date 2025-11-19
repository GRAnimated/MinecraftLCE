#pragma once

#include <memory>

#include "net/minecraft/sounds/SoundSource.h"
#include "net/minecraft/world/ArrayWithLength.h"

class Player;
class Level;
class BlockPos;
class BlockState;
class SoundEvent;
class Entity;
enum ePARTICLE_TYPE {
    ePARTICLE_TYPE_TrackingEmitter = 0x80224,
    ePARTICLE_TYPE_Explode = 5,
    ePARTICLE_TYPE_Splash = 9,
    ePARTICLE_TYPE_Spit = 0x33,
    ePARTICLE_TYPE_Wake = 0x22,
    ePARTICLE_TYPE_Droplet = 0x29,
    ePARTICLE_TYPE_Suspended = 16,
    ePARTICLE_TYPE_Depthsuspend = 0x11,
    ePARTICLE_TYPE_Crit = 0x12,
    ePARTICLE_TYPE_MagicCrit = 0x23,
    ePARTICLE_TYPE_Bubble = 0,
    ePARTICLE_TYPE_Smoke = 1,
    ePARTICLE_TYPE_LargeSmoke = 10,
    ePARTICLE_TYPE_Spell = 0x16,
    ePARTICLE_TYPE_InstantSpell = 0x24,
};  // TODO: Move this

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
