#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/item/DiggerItem.h"

class ShovelItem : public DiggerItem {
public:
    static arrayWithLength<Block*> DIGGABLES;

    static void staticCtor();

    ShovelItem(const Item::Tier*);

    ~ShovelItem() override;
    ActionResultType useOn(std::shared_ptr<Player>, Level*, const BlockPos&,
                           InteractionHand::EInteractionHand, const Direction*, float, float, float,
                           bool) override;
    bool canDestroySpecial(const BlockState*) override;
};