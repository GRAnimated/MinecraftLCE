#include "net/minecraft/world/level/saveddata/maps/MapDecoration.h"

#include "net/minecraft/util/Mth.h"

const MapDecoration::Type PLAYER_WHITE = MapDecoration::Type(0, 0, 1, -1);
const MapDecoration::Type PLAYER_GREEN = MapDecoration::Type(1, 0, 1, -1);
const MapDecoration::Type PLAYER_RED = MapDecoration::Type(2, 0, 1, -1);
const MapDecoration::Type PLAYER_BLUE = MapDecoration::Type(3, 0, 1, -1);
const MapDecoration::Type TARGET_X = MapDecoration::Type(4, 0, 0, -1);
const MapDecoration::Type TARGET_POINT = MapDecoration::Type(5, 0, 0, -1);
const MapDecoration::Type PLAYER_OFF_MAP = MapDecoration::Type(6, 0, 0, -1);
const MapDecoration::Type FRAME = MapDecoration::Type(7, 1, 0, -1);
const MapDecoration::Type PLAYER_MAGNETA = MapDecoration::Type(8, 0, 1, -1);
const MapDecoration::Type PLAYER_ORANGE = MapDecoration::Type(9, 0, 1, -1);
const MapDecoration::Type PLAYER_YELLOW = MapDecoration::Type(10, 0, 1, -1);
const MapDecoration::Type PLAYER_CYAN = MapDecoration::Type(11, 0, 1, -1);
const MapDecoration::Type GREEN_TRIANGLE = MapDecoration::Type(12, 0, 0, -1);
const MapDecoration::Type PLAYER_OFF_LIMITS = MapDecoration::Type(13, 0, 0, -1);
const MapDecoration::Type MANSION = MapDecoration::Type(14, 1, 0, 0x524C44);
const MapDecoration::Type MONUMENT = MapDecoration::Type(15, 1, 0, 0x3A7265);
const MapDecoration::Type PLAYER_WHITE_OFF_LIMITS = MapDecoration::Type(16, 0, 1, -1);
const MapDecoration::Type PLAYER_GREEN_OFF_LIMITS = MapDecoration::Type(17, 0, 1, -1);
const MapDecoration::Type PLAYER_RED_OFF_LIMITS = MapDecoration::Type(18, 0, 1, -1);
const MapDecoration::Type PLAYER_BLUE_OFF_LIMITS = MapDecoration::Type(19, 0, 1, -1);
const MapDecoration::Type UNKNOWN_20 = MapDecoration::Type(20, 0, 0, -1);
const MapDecoration::Type UNKNOWN_21 = MapDecoration::Type(21, 0, 0, -1);
const MapDecoration::Type UNKNOWN_22 = MapDecoration::Type(22, 0, 0, -1);
const MapDecoration::Type UNKNOWN_23 = MapDecoration::Type(23, 1, 0, -1);
const MapDecoration::Type PLAYER_MAGNETA_OFF_LIMITS = MapDecoration::Type(24, 0, 1, -1);
const MapDecoration::Type PLAYER_ORANGE_OFF_LIMITS = MapDecoration::Type(25, 0, 1, -1);
const MapDecoration::Type PLAYER_YELLOW_OFF_LIMITS = MapDecoration::Type(26, 0, 1, -1);
const MapDecoration::Type PLAYER_CYAN_OFF_LIMITS = MapDecoration::Type(27, 0, 1, -1);

MapDecoration::Type::Type(int icon, bool renderOnFrame, bool player, int color) {
    this->mIcon = icon;
    this->mRenderOnFrame = renderOnFrame;
    this->mPlayer = player;
    this->mColor = color;
}

// could be that types above are not defined one by one and instead are in array but
// then it wouldn't be clean by a even a little bit
const MapDecoration::Type* MapDecoration::Type::byIcon(unsigned char icon) {
    return &((&PLAYER_WHITE)[Mth::clamp(icon, 0, 27)]);
}

unsigned char MapDecoration::Type::getIcon() const {
    return this->mIcon;
}

bool MapDecoration::Type::isRenderedOnFrame() const {
    return this->mRenderOnFrame;
}

bool MapDecoration::Type::isPlayer() const {
    return this->mPlayer;
}

bool MapDecoration::Type::hasMapColor() const {
    return this->mColor >= 0;
}

int MapDecoration::Type::getMapColor() const {
    return this->mColor;
}

MapDecoration::MapDecoration() {}

MapDecoration::MapDecoration(const MapDecoration::Type* type, char x, char y, char rot, int icon, bool idk) {
    this->mX = x;
    this->mY = y;
    this->mType = type;
    this->mRot = rot;
    this->mIcon = icon;
    this->mIdk = idk;
}

unsigned char MapDecoration::getImg() const {
    return this->mType->getIcon();
}

bool MapDecoration::renderOnFrame() const {
    return this->mType->isRenderedOnFrame();
}

char MapDecoration::getX() const {
    return this->mX;
}

char MapDecoration::getY() const {
    return this->mY;
}

const MapDecoration::Type* MapDecoration::getType() const {
    return this->mType;
}

int MapDecoration::hashCode() const {
    int ret = this->mType->getIcon();
    ret = 31 * ret + this->mX;
    ret = 31 * ret + this->mY;
    ret = 31 * ret + this->mRot;
    return ret;
}

char MapDecoration::getRot() const {
    return this->mRot;
}
