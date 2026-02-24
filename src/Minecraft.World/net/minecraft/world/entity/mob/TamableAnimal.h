#pragma once

#include "net/minecraft/world/entity/OwnableEntity.h"
#include "net/minecraft/world/entity/mob/Animal.h"
#include "net/minecraft/world/entity/mob/FlyingAnimal.h"

// ENTITY STUB
class TamableAnimal : public Animal, public OwnableEntity {
public:
    static void staticCtor();

    // create proper virtuals later, and possibly move those stubs down to Animal
    virtual void virtual_1();
    virtual void virtual_2();
    virtual void virtual_3();
    virtual void virtual_4();
    virtual void virtual_5();
    virtual void virtual_6();
    virtual void virtual_7();
    virtual bool isSitting();
};
