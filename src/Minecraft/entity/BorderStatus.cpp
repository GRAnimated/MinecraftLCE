#include "BorderStatus.h"

// Why the fuck did 4j create global constants for this instead of using an enum?
BorderStatus* gBorderStatusGrowing = new BorderStatus(0x40FF80);
BorderStatus* gBorderStatusShrinking = new BorderStatus(0xFF3030);
BorderStatus* gBorderStatusStationary = new BorderStatus(0x20A0FF);

BorderStatus::BorderStatus(int color) : mColor(color) {}