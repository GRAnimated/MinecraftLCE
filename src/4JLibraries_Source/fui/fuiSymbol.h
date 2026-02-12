#pragma once

class FJ_FuiNodeStage;

struct fuiSymbol {
    char m_padding[0xf8];
    FJ_FuiNodeStage*
        m_stage;  // not sure if this is meant to be stage but fui::dispatchKeyboardEvent likes it sooo
};
