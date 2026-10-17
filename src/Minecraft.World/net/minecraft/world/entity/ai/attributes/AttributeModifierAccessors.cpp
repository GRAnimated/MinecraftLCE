#include "net/minecraft/world/entity/ai/attributes/AttributeModifier.h"

double AttributeModifier::getAmount() {
    return m_amount;
}

int AttributeModifier::getOperation() {
    return m_operation;
}
