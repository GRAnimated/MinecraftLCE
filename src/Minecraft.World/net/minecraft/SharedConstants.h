#pragma once

#include <string>

// todo: where to put this?

class SharedConstants {
public:
    static std::wstring sVersionString;  // yes this actually exists, see the cpp file
    static std::wstring sAcceptableLetters;
    static bool sIsHalloweenDay;
    static bool sIsHalloween;  // https://minecraft.wiki/w/Easter_eggs#Halloween
    static bool sIsXmas;       // guessed
    static bool sIsDec17ToDec23;

    static constexpr short NETWORK_PROTOCOL_VERSION = 1920;

    static void staticCtor();
};
