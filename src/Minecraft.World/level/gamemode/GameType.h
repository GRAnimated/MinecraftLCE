#pragma once

#include <string>

class Abilities;

class GameType {
public:
    static GameType* NOT_SET;
    static GameType* SURVIVAL;
    static GameType* CREATIVE;
    static GameType* ADVENTURE;
    static GameType* SPECTATOR;
    static GameType* LOBBY;

    static void staticCtor();

    GameType(int, const std::wstring&, const std::wstring&, int, int);

    int getId() const;
    int getLabel() const;
    int getSliderLabel() const;
    bool isBlockPlacingRestricted() const;
    void updatePlayerAbilities(Abilities*) const;
    bool isCreative() const;
    bool isSurvival() const;
    static const GameType* byId(int, const GameType*);
    static const GameType* byId(int);

private:
    int mId;
    std::wstring mLabel;
    std::wstring mSliderLabel;
    int field_38;
    int field_3C;
};
