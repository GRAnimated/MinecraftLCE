#include "net/minecraft/core/profile/CProfile.h"

#include "net/minecraft/client/resources/L10N.h"

// NON_MATCHING | Score: 10 (Lower is better)
// Randomly unmatched, also I think the method was broken to begin with...
void CProfile::SetOnAwardHandler(void (*func)(), void* somePtr) {
    this->mOnAwardHandler = func;
    this->mAwardHandlerVar = somePtr;
}

void CProfile::RichPresenceRegisterPresenceString(int i, int i1) {
    this->map9B8[i] = i1;
}

void CProfile::RichPresenceRegisterContext(int k, int v) {
    this->map990[k] = v;
    this->mapAF8[k] = -1;
    this->mapB20[k] = -1;
    this->mapB48[k] = -1;
    this->mapB70[k] = -1;
}

void CProfile::RichPresenceRegisterContextString(int i, int i1, int i2) {
    std::unordered_map<int, int> m = this->map9E0[i];
    m[i1] = i2;
}

void CProfile::SetSignInChoicesCallback(int (*func)(int)) {
    this->mSignInChoicesCallback = func;
}

wchar_t* GetRichPresenceStringFromId(int id) {
    return L10N::GetString(id);
}
