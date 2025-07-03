#include "L10N.h"
#include "StringTable.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include <string>

const wchar_t* L10N::GetString(int id) {
    if (StringTable::instance)
        return StringTable::instance->getString(id);
    else
        return L"";
}

void L10N::loadStringTable() {
    if (StringTable::instance)
        delete StringTable::instance;

    std::wstring languages_loc = L"languages.loc";
    if (CConsoleMinecraftApp::sInstance.hasArchiveFile(languages_loc, true)) {
        arrayWithLength<uchar> archive = CConsoleMinecraftApp::sInstance.getArchiveFile(languages_loc, true);
        StringTable::instance = new StringTable(archive, false, false);

        // it seems that they didn't have destructor for arrayWithLength for some reason and just handled it
        //                                                                                          manually
        delete archive.data;
    } else {
        StringTable::instance = nullptr;
    }
}
