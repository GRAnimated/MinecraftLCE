#pragma once

class L10N {
public:
    static void loadStringTable();
    static const wchar_t *GetString(int id);
};