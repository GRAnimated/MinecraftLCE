#pragma once

// NON_MATCHING: Enum values are not known
enum EMiniGameId {
    GLIDE = 3,
    LOBBY = 0xF  // Named SERVER in my xb1 symbols but might be lobby... not sure.
};

class MiniGameDef {
public:
    static void StaticCtor();

    static void* GetCustomGameModeById(EMiniGameId id, bool);

    bool HasFeatureDirectionalFireworks() const;
};