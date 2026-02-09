#include "net/minecraft/client/model/Model.h"

class ModelDefinition;

class ElytraModel : public Model {
public:
    ElytraModel(const ModelDefinition&);

    void render(std::shared_ptr<Entity>&, float, float, float, float, float, float, bool) override;
    void setupAnim(float, float, float, float, float, float, std::shared_ptr<Entity>,
                   _SkinAdjustments) override;

    ModelPartSkin* mRightWing;
    ModelPartSkin* mLeftWing;
};