#include "net/minecraft/util/Calendar.h"
#include "nn/diag.h"

unsigned int Calendar::GetMonth() {
    return Calendar::GetCalenderTime().month;
}

unsigned int Calendar::GetDayOfMonth() {
    return Calendar::GetCalenderTime().day;
}

// NON_MATCHING
// nn::time::CalendarTime Calendar::GetCalenderTime() {
//     nn::time::PosixTime t;
//
//     nn::time::CalendarTime c;
//     nn::time::CalendarAdditionalInfo i;
//
//     nn::time::StandardUserSystemClock::GetCurrentTime(&t);
//     nn::time::ToCalendarTime(&c, &i, t);
//
//     // TODO there is no logging shit mapped out, so we don't know what the fields are.
//     // however we do know that __LINE__, __FILE__, and __FUNCTION__ are used.
//     // The call to __LINE__ should be placed at line 22 in this file.
// }
