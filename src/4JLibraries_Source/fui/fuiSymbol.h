#pragma once

class FJ_FuiNodeStage;

class fuiSymbol {
public:
    char padding[0xf8];
    FJ_FuiNodeStage*
        mStage;  // not sure if this is meant to be stage but fui::dispatchKeyboardEvent likes it sooo
};
