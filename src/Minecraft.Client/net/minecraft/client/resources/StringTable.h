#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "types.h"
#include <string>
#include <unordered_map>
#include <utility>

class Random;
class DataInputStream;
class DataOutputStream;

class StringTable {
public:
    // unknown what's in here, but it might be what's stored in the file.
    class _LanguageData {};

    void copyStringToTable(const std::wstring& string, StringTable* table);
    // unsure if returns void
    void FindLanguage(bool& param_1, long long& param_2);
    void getData(unsigned char** dst, unsigned int* dstSize);

    int getRandomStringId(Random* random);
    // not sure if int is count or not
    int getRandomStringIds(int count, Random* random);

    const wchar_t* getString(const std::wstring& str);
    wchar_t* getString(int id);

    void ProcessStringTableData();

    // unsure what the return type is
    void ReadAllFromStream(DataInputStream* stream);
    void ReadLanguageFromStream(DataInputStream* stream);

    void ReloadStringTable();

    void SelectLanguage(const std::wstring& language);

    StringTable();
    StringTable(arrayWithLength<unsigned char>, bool, bool);

    void write(DataOutputStream* stream);

    ~StringTable();

    static StringTable* instance;
    bool m_bool0;
    bool m_bool1;
    char m_char2;
    char m_gap3[5];
    std::unordered_map<std::wstring, StringTable::_LanguageData> m_ap;
    std::vector<int> m_vector1;
    std::vector<std::wstring> m_vector2;
    std::vector<std::pair<std::wstring, int>> m_vector3;  // this is kinda guessed but should be correct
    void* m_qword78;
    void* m_qword80;
    arrayWithLength<uchar> m_languagesLocArchiveFile;
};
