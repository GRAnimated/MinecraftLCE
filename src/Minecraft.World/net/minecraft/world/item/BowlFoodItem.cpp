#include "net/minecraft/world/item/ItemBootstrapTypes.h"
#include "net/minecraft/world/item/LeadItem.h"

// name guessed
BowlFoodItem::BowlFoodItem(int nutrition) : FoodItem(nutrition, false) {
    setMaxStackSize(1);
}
