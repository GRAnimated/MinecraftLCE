#include "net/minecraft/world/level/levelgen/synth/Synth.h"

Synth::Synth() {}

/** Keep the deleting destructor's call to the empty base body. Weak linkage
 * prevents Clang from discarding that call based on this body's known effects.
 */
__attribute__((weak)) Synth::~Synth() = default;
