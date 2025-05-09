#pragma once

#include "types.h"

class ItemInstance;
class InteractionResult {
public:
    enum EInteractionResult { SUCCESS, PASS, FAIL };
};

class InteractionResultHolder {
public:
    InteractionResultHolder(InteractionResult::EInteractionResult result,
                            const not_null_ptr<ItemInstance>& item)
        : result(result), item(item) {}
    InteractionResult::EInteractionResult result;
    not_null_ptr<ItemInstance> item;
};