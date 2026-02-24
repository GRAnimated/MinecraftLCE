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
    this->m_icon = icon;
    this->m_renderOnFrame = renderOnFrame;
    this->m_player = player;
    this->m_color = color;
}

// could be that types above are not defined one by one and instead are in array but
// then it wouldn't be clean by a even a little bit
const MapDecoration::Type* MapDecoration::Type::byIcon(unsigned char icon) {
    return &((&PLAYER_WHITE)[Mth::clamp(icon, 0, 27)]);
}

unsigned char MapDecoration::Type::getIcon() const {
    return this->m_icon;
}

bool MapDecoration::Type::isRenderedOnFrame() const {
    return this->m_renderOnFrame;
}

bool MapDecoration::Type::isPlayer() const {
    return this->m_player;
}

bool MapDecoration::Type::hasMapColor() const {
    return this->m_color >= 0;
}

int MapDecoration::Type::getMapColor() const {
    return this->m_color;
}

MapDecoration::MapDecoration() {}

MapDecoration::MapDecoration(const MapDecoration::Type* type, char x, char y, char rot, int icon, bool idk) {
    this->m_x = x;
    this->m_y = y;
    this->m_type = type;
    this->m_rot = rot;
    this->m_icon = icon;
    this->m_idk = idk;
}

unsigned char MapDecoration::getImg() const {
    return this->m_type->getIcon();
}

bool MapDecoration::renderOnFrame() const {
    return this->m_type->isRenderedOnFrame();
}

char MapDecoration::getX() const {
    return this->m_x;
}

char MapDecoration::getY() const {
    return this->m_y;
}

const MapDecoration::Type* MapDecoration::getType() const {
    return this->m_type;
}

int MapDecoration::hashCode() const {
    int ret = this->m_type->getIcon();
    ret = 31 * ret + this->m_x;
    ret = 31 * ret + this->m_y;
    ret = 31 * ret + this->m_rot;
    return ret;
}

char MapDecoration::getRot() const {
    return this->m_rot;
}
