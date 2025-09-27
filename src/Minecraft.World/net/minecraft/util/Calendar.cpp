#include "net/minecraft/util/Calendar.h"

unsigned int Calendar::GetMonth() {
    return Calendar::GetCalenderTime().month;
}

unsigned int Calendar::GetDayOfMonth() {
    return Calendar::GetCalenderTime().day;
}
