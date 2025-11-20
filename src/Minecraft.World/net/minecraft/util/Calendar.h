#pragma once

#include "nn/time.h"

class Calendar {
public:
    static unsigned int GetMonth();
    static unsigned int GetDayOfMonth();
    static nn::time::CalendarTime GetCalenderTime();  // Misspelling by 4J
};
