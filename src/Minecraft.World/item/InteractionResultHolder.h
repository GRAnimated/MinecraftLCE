#include "types.h"

class ItemInstance;
class InteractionResult {
public:
    enum EInteractionResult { SUCCESS, PASS, FAIL };
};

class InteractionResultHolder {
public:
    InteractionResultHolder(InteractionResult::EInteractionResult result,
                            const not_null_ptr<ItemInstance>& item) {
        this->result = result;
        this->item = item;
    }
    InteractionResult::EInteractionResult result;
    not_null_ptr<ItemInstance> item;
};