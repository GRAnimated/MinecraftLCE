#pragma once

class L10N {
public:
    static void loadStringTable();
    static wchar_t* GetString(int id);
};
