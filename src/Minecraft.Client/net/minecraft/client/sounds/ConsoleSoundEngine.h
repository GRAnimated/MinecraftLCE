#pragma once

#include <memory>

class File;
class Mob;
class Options;
class SoundEvent;
class SoundInstance;

class ConsoleSoundEngine {
public:
    enum eAudioDelayType {};

    virtual ~ConsoleSoundEngine();
    virtual void tick(std::shared_ptr<Mob>*, float) = 0;
    virtual void destroy() = 0;
    virtual void shutdown() = 0;
    virtual void play(const SoundEvent*, float, float, float, float, float, SoundInstance*) = 0;
    virtual void playStreaming(const SoundEvent*, float, float, float, float, float, bool, bool,
                               eAudioDelayType)
        = 0;
    virtual void playUI(const SoundEvent*, float, float) = 0;
    virtual void init(Options*) = 0;
    virtual void add(const std::wstring&, File*) = 0;
    virtual void addMusic(const std::wstring&, File*) = 0;
    virtual void addStreaming(const std::wstring&, File*) = 0;
    virtual void ConvertSoundPathToName(const std::wstring&, bool) = 0;
    virtual void playMusicTick() = 0;
    virtual void GetIsPlayingStreamingCDMusic();
    virtual void GetIsPlayingStreamingGameMusic();
    virtual void SetIsPlayingStreamingCDMusic(bool);
    virtual void SetIsPlayingStreamingGameMusic(bool);
    virtual void GetIsPlayingEndMusic();
    virtual void GetIsPlayingNetherMusic();
    virtual void SetIsPlayingEndMusic(bool);
    virtual void SetIsPlayingNetherMusic(bool);
};
