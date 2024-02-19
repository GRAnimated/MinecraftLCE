#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.World/level/border/BorderStatus.h"

BlockPos BlockPos::zero = BlockPos(0, 0, 0);

// Java Edition uses an enum here. I'm not sure what the benefit of global variables do in this case.
BorderStatus* gBorderStatusGrowing = new BorderStatus(0x40FF80);
BorderStatus* gBorderStatusShrinking = new BorderStatus(0xFF3030);
BorderStatus* gBorderStatusStationary = new BorderStatus(0x20A0FF);
