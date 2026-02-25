#pragma once

class BorderStatus {
public:
    BorderStatus(int color);

    int m_color;
};

extern BorderStatus* gBorderStatusGrowing;
extern BorderStatus* gBorderStatusShrinking;
extern BorderStatus* gBorderStatusStationary;
