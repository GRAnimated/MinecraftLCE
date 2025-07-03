#pragma once

class ItemInstance;

class Recipes {
public:
    Recipes();
    void addShapedRecipe(ItemInstance*, ...);
    void addShapelessRecipe(ItemInstance*, ...);
    void buildRecipeIngredientsArray();
};
