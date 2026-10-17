// Keep these routines together as in the original sound translation unit.
// Clang 4's interprocedural return analysis affects temporary destruction order.
#include "net/minecraft/sounds/SoundEvent.cpp"
#include "net/minecraft/sounds/SoundEvents.cpp"
#include "net/minecraft/world/level/block/SoundType.cpp"
