#pragma once

class ItemInstance;
class LivingEntity;
class ItemTransform;

class ItemTransforms {
public:
    enum TransformType {
        THIRDPERSON_LEFTHAND = 1,
        THIRDPERSON_RIGHTHAND = 2,
        FIRSTPERSON_LEFTHAND = 3,
        FIRSTPERSON_RIGHTHAND = 4,
        HEAD = 5,
        GUI = 6,
        GROUND = 7,
        FIXED = 8
    };

    ItemTransforms();

    static ItemTransforms* getTransforms(const ItemInstance* item, LivingEntity* entity);
    static ItemTransforms* getArmourStandTransforms(const ItemInstance* item, LivingEntity* entity);
    static ItemTransforms GetDefaultTransforms();
    static void apply(ItemTransform*, bool);

    ItemTransform* getTransform(ItemTransforms::TransformType) const;
    ItemTransforms* set_thirdperson_lefthand(float rotationX, float rotationY, float rotationZ,
                                             float translationX, float translationY, float translationZ,
                                             float scaleX, float scaleY, float scaleZ);
    ItemTransforms* set_thirdperson_righthand(float rotationX, float rotationY, float rotationZ,
                                              float translationX, float translationY, float translationZ,
                                              float scaleX, float scaleY, float scaleZ);
    ItemTransforms* set_firstperson_lefthand(float rotationX, float rotationY, float rotationZ,
                                             float translationX, float translationY, float translationZ,
                                             float scaleX, float scaleY, float scaleZ);
    ItemTransforms* set_firstperson_righthand(float rotationX, float rotationY, float rotationZ,
                                              float translationX, float translationY, float translationZ,
                                              float scaleX, float scaleY, float scaleZ);
    ItemTransforms* set_head(float rotationX, float rotationY, float rotationZ, float translationX,
                             float translationY, float translationZ, float scaleX, float scaleY,
                             float scaleZ);
    ItemTransforms* set_gui(float rotationX, float rotationY, float rotationZ, float translationX,
                            float translationY, float translationZ, float scaleX, float scaleY, float scaleZ);
    ItemTransforms* set_ground(float rotationX, float rotationY, float rotationZ, float translationX,
                               float translationY, float translationZ, float scaleX, float scaleY,
                               float scaleZ);
    ItemTransforms* set_fixed(float rotationX, float rotationY, float rotationZ, float translationX,
                              float translationY, float translationZ, float scaleX, float scaleY,
                              float scaleZ);

private:
    ItemTransform* thirdperson_lefthand;
    ItemTransform* thirdperson_righthand;
    ItemTransform* firstperson_lefthand;
    ItemTransform* firstperson_righthand;
    ItemTransform* head;
    ItemTransform* gui;
    ItemTransform* ground;
    ItemTransform* fixed;
};
