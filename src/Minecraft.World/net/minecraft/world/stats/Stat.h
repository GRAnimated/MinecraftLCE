#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class Stat {
public:
    class Formatter;
    static Formatter* DEFAULT_FORMAT;
    static std::vector<Stat*>* ALL_STATS;
    static std::unordered_map<int, Stat*>* BY_ID;

    Stat(int, const std::wstring&, Formatter*);
    Stat(int, const std::wstring&);
    virtual ~Stat();
    virtual Stat* registerStat(bool);
    virtual bool isAchievement();
    virtual bool getFlag1();
    virtual bool getFlag2();
    virtual bool getFlag0();
    virtual void reservedHook();
    void initializeFlags();
    Stat* setFlag();
    void setIndependent();
    void setFlag2(bool);
    void setFlag1(bool);
    void setFlag0(bool);
    bool isFlagClear();

protected:
    int m_id;
    std::wstring m_name;
    Formatter* m_formatter;
    union {
        unsigned int m_flagWord;
        struct {
            bool m_flag0, m_flag1, m_flag2, m_independent;
        };
    };
    bool m_flag;
};
