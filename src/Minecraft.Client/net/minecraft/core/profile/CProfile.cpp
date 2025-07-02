#include "CProfile.h"

void CProfile::SetOnAwardHandler(void (*func)(), void* somePtr) {
    this->mOnAwardHandler = func;
    this->mAwardHandlerVar = somePtr;
}

void CProfile::SetSignInChoicesCallback(int (*func)(int)) {
    this->mSignInChoicesCallback = func;
}