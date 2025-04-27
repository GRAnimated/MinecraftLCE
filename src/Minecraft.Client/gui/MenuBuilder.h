#pragma once

class Block;
class Item;

class MenuBuilder {
public:
    void ADD_ITEM(Item*, int);
    void ITEM_BLOCK(Block*);
};
