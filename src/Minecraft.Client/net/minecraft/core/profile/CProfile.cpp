#include "net/minecraft/core/profile/CProfile.h"

#include "net/minecraft/client/resources/L10N.h"

void CProfile::SetOnAwardHandler(void (*func)(), void* somePtr) {
    this->m_onAwardHandler = func;
    this->m_awardHandlerVar = somePtr;
}

void CProfile::RichPresenceRegisterPresenceString(int i, int i1) {
    this->m_ap9B8[i] = i1;
}

void CProfile::RichPresenceRegisterContext(int k, int v) {
    this->m_ap990[k] = v;
    this->m_apAF8[k] = -1;
    this->m_apB20[k] = -1;
    this->m_apB48[k] = -1;
    this->m_apB70[k] = -1;
}

void CProfile::RichPresenceRegisterContextString(int i, int i1, int i2) {
    std::unordered_map<int, int> m = this->m_ap9E0[i];
    m[i1] = i2;
}

void CProfile::SetSignInChoicesCallback(int (*func)(int)) {
    this->m_signInChoicesCallback = func;
}

wchar_t* GetRichPresenceStringFromId(int id) {
    return L10N::GetString(id);
}
