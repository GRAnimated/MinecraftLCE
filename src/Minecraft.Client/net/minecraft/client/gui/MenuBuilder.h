#pragma once
class Item;
class Block;

class MenuBuilder {
public:
    void ADD_ITEM(Item*, int);
    void ITEM_BLOCK(Block*);
};