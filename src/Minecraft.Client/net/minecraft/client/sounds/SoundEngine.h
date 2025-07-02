#pragma once

#include "types.h"
#include "net/minecraft/client/sounds/ConsoleSoundEngine.h"

class SoundEngine : public ConsoleSoundEngine {
public:
    SoundEngine();

    virtual ~SoundEngine();
    virtual void tick(std::shared_ptr<Mob>*, float);
    virtual void destroy();
    virtual void shutdown();
    virtual void play(const SoundEvent*, float, float, float, float, float, SoundInstance*);
    virtual void playStreaming(const SoundEvent*, float, float, float, float, float, bool, bool,
                               eAudioDelayType);
    virtual void playUI(const SoundEvent*, float, float);
    virtual void init(Options*);
    virtual void add(const std::wstring&, File*);
    virtual void addMusic(const std::wstring&, File*);
    virtual void addStreaming(const std::wstring&, File*);
    virtual void ConvertSoundPathToName(const std::wstring&, bool);
    virtual void playMusicTick();

private:
    unsigned char size[0x330];
};

ASSERT_SIZEOF(SoundEngine, 0x338)