#pragma once

class BorderStatus {
public:
    BorderStatus(int color);

    int mColor;
};

extern BorderStatus* gBorderStatusGrowing;
extern BorderStatus* gBorderStatusShrinking;
extern BorderStatus* gBorderStatusStationary;
