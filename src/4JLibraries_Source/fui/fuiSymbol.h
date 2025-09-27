#pragma once

class FJ_FuiNodeStage;

struct fuiSymbol {
    char padding[0xf8];
    FJ_FuiNodeStage*
        mStage;  // not sure if this is meant to be stage but fui::dispatchKeyboardEvent likes it sooo
};
