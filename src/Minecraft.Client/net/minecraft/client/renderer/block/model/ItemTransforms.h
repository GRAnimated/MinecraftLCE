#pragma once

class ItemInstance;
class LivingEntity;
class ItemTransform;

class ItemTransforms {
public:
    ItemTransforms();

    static ItemTransforms* getTransforms(const ItemInstance* item, LivingEntity* entity);
    static void apply(ItemTransform*, bool);

    void set_thirdperson_lefthand(float rotationX, float rotationY, float rotationZ, float translationX,
                                  float translationY, float translationZ, float scaleX, float scaleY,
                                  float scaleZ);
    void set_thirdperson_righthand(float rotationX, float rotationY, float rotationZ, float translationX,
                                   float translationY, float translationZ, float scaleX, float scaleY,
                                   float scaleZ);
    void set_firstperson_lefthand(float rotationX, float rotationY, float rotationZ, float translationX,
                                  float translationY, float translationZ, float scaleX, float scaleY,
                                  float scaleZ);
    void set_firstperson_righthand(float rotationX, float rotationY, float rotationZ, float translationX,
                                   float translationY, float translationZ, float scaleX, float scaleY,
                                   float scaleZ);
    void set_head(float rotationX, float rotationY, float rotationZ, float translationX, float translationY,
                  float translationZ, float scaleX, float scaleY, float scaleZ);
    void set_gui(float rotationX, float rotationY, float rotationZ, float translationX, float translationY,
                 float translationZ, float scaleX, float scaleY, float scaleZ);
    void set_ground(float rotationX, float rotationY, float rotationZ, float translationX, float translationY,
                    float translationZ, float scaleX, float scaleY, float scaleZ);
    void set_fixed(float rotationX, float rotationY, float rotationZ, float translationX, float translationY,
                   float translationZ, float scaleX, float scaleY, float scaleZ);

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
