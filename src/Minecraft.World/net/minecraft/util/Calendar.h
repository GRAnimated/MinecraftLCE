#pragma once

#include "nn/time.h"

class Calendar {
public:
    static int GetMonth();
    static int GetDayOfMonth();
    static nn::time::CalendarTime GetCalenderTime();  // Misspelling by 4J
};