#pragma once

#include <string>
#include <unordered_map>

class DataFixerUpper;
class InputStream;
class StructureTemplate;

class StructureManager {
public:
    StructureManager(DataFixerUpper*);
    virtual ~StructureManager();
    static void staticCtor();
    StructureTemplate* getOrCreate(int);
    StructureTemplate* get(int);
    bool loadArchive(int);
    std::wstring getArchivePath(int);
    void loadFromStream(int, InputStream*);

    std::unordered_map<int, StructureTemplate*> m_templates;
    DataFixerUpper* m_fixerUpper;
    static constexpr int RESOURCE_COUNT = 114;

private:
    static const wchar_t* const s_resourceNames[RESOURCE_COUNT];
};
static_assert(sizeof(StructureManager) == 0x38, "Original structure manager allocation");
