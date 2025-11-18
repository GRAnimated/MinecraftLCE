#include "4JLibraries_Source/fui/node/FJ_Base.h"

int FJ_Base::getType() {
    return 0x8000;
}

bool FJ_Base::getLabelTooWide() {
    return this->mLabelTooWide;
}

int FJ_Base::getOldWidth() {
    return this->getWidth();
}

void FJ_Base::HandleCharInput(uint) {}

void* FJ_Base::getObjListParent() {
    return this->mObjListParent;
}

int FJ_Base::getId() {
    return this->mId;
}
