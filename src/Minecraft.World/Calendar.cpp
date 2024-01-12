#include "Calendar.h"

int Calendar::GetMonth() {
    return Calendar::GetCalenderTime().month;
}

int Calendar::GetDayOfMonth() {
    return Calendar::GetCalenderTime().day;
}
