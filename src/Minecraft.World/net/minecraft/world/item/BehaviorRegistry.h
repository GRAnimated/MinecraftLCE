#pragma once

class Item;
class DispenseItemBehavior;

class BehaviorRegistry {
public:
    void add(Item*, DispenseItemBehavior*);

    static BehaviorRegistry sInstance;
};