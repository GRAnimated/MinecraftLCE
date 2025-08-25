#pragma once

class MapDecoration {
public:
    class Type {
    public:
        static const Type PLAYER_WHITE;
        static const Type PLAYER_GREEN;
        static const Type PLAYER_RED;
        static const Type PLAYER_BLUE;
        static const Type TARGET_X;
        static const Type TARGET_POINT;
        static const Type PLAYER_OFF_MAP;
        static const Type FRAME;
        static const Type PLAYER_MAGNETA;
        static const Type PLAYER_ORANGE;
        static const Type PLAYER_YELLOW;
        static const Type PLAYER_CYAN;
        static const Type GREEN_TRIANGLE;
        static const Type PLAYER_OFF_LIMITS;
        static const Type MANSION;
        static const Type MONUMENT;
        static const Type PLAYER_WHITE_OFF_LIMITS;
        static const Type PLAYER_GREEN_OFF_LIMITS;
        static const Type PLAYER_RED_OFF_LIMITS;
        static const Type PLAYER_BLUE_OFF_LIMITS;
        static const Type UNKNOWN_20;
        static const Type UNKNOWN_21;
        static const Type UNKNOWN_22;
        static const Type UNKNOWN_23;
        static const Type PLAYER_MAGNETA_OFF_LIMITS;
        static const Type PLAYER_ORANGE_OFF_LIMITS;
        static const Type PLAYER_YELLOW_OFF_LIMITS;
        static const Type PLAYER_CYAN_OFF_LIMITS;

        Type(int icon, bool renderOnFrame, bool player, int color);

        static const Type* byIcon(unsigned char);

        unsigned char getIcon() const;
        bool isRenderedOnFrame() const;
        bool isPlayer() const;
        bool hasMapColor() const;
        int getMapColor() const;

        unsigned char mIcon;
        bool mRenderOnFrame;
        bool mPlayer;
        int mColor;
    };

    MapDecoration();
    MapDecoration(const MapDecoration::Type* type, char x, char y, char rot, int icon, bool idk);

    unsigned char getImg() const;
    bool renderOnFrame() const;
    char getX() const;
    char getY() const;
    const Type* getType() const;
    int hashCode() const;
    char getRot() const;
    bool isIdk() const { return this->mIdk; }  // const prob ?

    const MapDecoration::Type* mType = nullptr;
    int mX = 0;
    int mY = 0;
    char mRot = 0;
    int mIcon = 0;
    bool mIdk = 0;
};
