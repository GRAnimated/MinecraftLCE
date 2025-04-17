#pragma once
#include "Minecraft.World/ArrayWithLength.h"
#include <string>
#include <unordered_map>

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
    const wchar_t* getString(int id);

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
    bool unk;
    bool unk2;  // used in ReloadStringTable
    unsigned char unk3[102];
    // guessed, might actually be their weird _LanguageData class as second param
    std::unordered_map<int, std::wstring> table;
};