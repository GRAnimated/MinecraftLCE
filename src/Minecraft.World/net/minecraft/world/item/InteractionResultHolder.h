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
        : m_result(result), m_item(item) {}
    InteractionResult::EInteractionResult m_result;
    not_null_ptr<ItemInstance> m_item;
};
