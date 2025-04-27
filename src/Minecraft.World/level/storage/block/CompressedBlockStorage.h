#pragma once
#include "Minecraft.Core/io/DataOutputStream.h"

class CompressedBlockStorage {
public:
  void write(DataOutputStream *out);
};
