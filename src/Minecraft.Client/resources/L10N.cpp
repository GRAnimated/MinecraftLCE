#include "L10N.h"
#include "StringTable.h"

const wchar_t* L10N::GetString(int id) {
    if (StringTable::instance) return StringTable::instance->getString(id);
    else return L"";
}