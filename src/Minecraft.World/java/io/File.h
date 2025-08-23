#pragma once

#include <string>
#include <vector>

struct _OVERLAPPED;
struct _WIN32_FIND_DATAA;

class FileFilter;

class File {
public:
    File();
    File(const std::wstring& name);
    File(const File& other, const std::wstring& path);
    File(const std::wstring&, const std::wstring&);
    ~File();

    File& operator=(const File& rhs);

    std::wstring getPath() const;
    void _delete();
    bool mkdir() const;
    bool exists() const;
    bool isDirectory() const;
    bool isFile() const;
    bool renameTo(const File& dest);
    std::vector<File> listFiles() const;
    std::vector<File> listFiles(FileFilter* filter) const;  // unused in switch edition
    long length() const;
    std::wstring getName() const;
    std::wstring ext() const;

    static size_t hash_fnct(const File& file);
    static bool eq_test(const File& file1, const File& file2);

    std::wstring name;
};

std::wstring char16towstring(wchar_t*);
const char* wstringtofilename(const std::wstring&, char (&)[256]);
std::string formatstr(const char* format, ...);
std::wstring formatwstr(const wchar_t* format, ...);
bool CreateDirectoryA(const char*, void*);
bool GetFileAttributesA(const char*);
bool MoveFileA(const char*, const char*);
int GetLastError();

bool isDirectory(const std::wstring&);
bool FindFirstFileA(const char*, _WIN32_FIND_DATAA*);
std::wstring filenametowstring(const char*);
bool FindNextFileA(int, _WIN32_FIND_DATAA*);
bool CloseHandle(int);
bool CreateFileA(const char*, unsigned int, unsigned int, void*, unsigned int, unsigned int, int);
bool GetFileSize(int, unsigned int*);
bool ReadFile(int, void*, unsigned int, unsigned int*, _OVERLAPPED*);
