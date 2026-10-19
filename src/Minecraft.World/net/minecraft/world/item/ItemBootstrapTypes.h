#pragma once

/** Constructor declarations and storage recovered from Item::staticCtor.
 * Opaque fields do not supply the still-unreconstructed item behavior.
 * Out-of-line destructor declarations retain original external vtable dependencies
 * for reconstructed constructors while subclass virtual behavior remains missing.
 */
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/entity/mob/MinecartType.h"
#include "net/minecraft/world/item/ArrowItem.h"
#include "net/minecraft/world/item/BlockItem.h"
#include "net/minecraft/world/item/FoodItem.h"
#include "net/minecraft/world/level/block/HalfSlabBlock.h"

class SoundEvent;

class SlabBlockItem : public BlockItem {
public:
    SlabBlockItem(Block*, HalfSlabBlock*, HalfSlabBlock*);
    ~SlabBlockItem() override;
    HalfSlabBlock* m_halfSlab;
    HalfSlabBlock* m_fullSlab;
};

class MultiBlockItem : public BlockItem {
public:
    MultiBlockItem(Block*, Block*, unsigned int (*)(not_null_ptr<ItemInstance>),
                   unsigned int (*)(not_null_ptr<ItemInstance>));
    ~MultiBlockItem() override;
    Block* m_secondaryBlock;
    unsigned int (*m_nameResolver)(not_null_ptr<ItemInstance>);
    unsigned int (*m_descriptionResolver)(not_null_ptr<ItemInstance>);
};

class TintedBlockItem : public BlockItem {
public:
    TintedBlockItem(Block*, bool);
    ~TintedBlockItem() override;
    arrayWithLength<int> m_descriptionIds;
    TintedBlockItem* setDescriptionIds(arrayWithLength<int>);
};

class LeafBlockItem : public BlockItem {
public:
    LeafBlockItem(Block*);
    ~LeafBlockItem() override;
    Block* m_leavesBlock;
};

class PistonBlockItem : public BlockItem {
public:
    PistonBlockItem(Block*);
    ~PistonBlockItem() override;
};

class SnowItem : public BlockItem {
public:
    SnowItem(Block*);
    ~SnowItem() override;
};

class WaterLilyBlockItem : public TintedBlockItem {
public:
    WaterLilyBlockItem(Block*);
    ~WaterLilyBlockItem() override;
};

class AnvilBlockItem : public MultiBlockItem {
public:
    AnvilBlockItem(Block*);
};

class ShulkerBoxBlockItem : public BlockItem {
public:
    ShulkerBoxBlockItem(Block*);
    ~ShulkerBoxBlockItem() override;
};

class FlintAndSteelItem : public Item {
public:
    FlintAndSteelItem();
    ~FlintAndSteelItem() override;
};

class BowlFoodItem : public FoodItem {
public:
    BowlFoodItem(int);
    ~BowlFoodItem() override;
};

class BlockPlanterItem : public Item {
public:
    BlockPlanterItem(Block*);
    ~BlockPlanterItem() override;
    Block* m_block;
};

class HoeItem : public Item {
public:
    HoeItem(const Item::Tier*);
    void* m_unknown[1];
};

class SeedItem : public Item {
public:
    SeedItem(Block*, Block*);
    ~SeedItem() override;
    Block* m_crop;
    Block* m_farmland;
};

class HangingEntityItem : public Item {
public:
    HangingEntityItem(eINSTANCEOF);
    ~HangingEntityItem() override;
    eINSTANCEOF m_type;
};

class GoldenAppleItem : public FoodItem {
public:
    GoldenAppleItem(int, float, bool);
};

class SignItem : public Item {
public:
    SignItem();
    ~SignItem() override;
};

class DoorItem : public Item {
public:
    DoorItem(Block*);
    ~DoorItem() override;
    Block* m_block;
};

class BucketItem : public Item {
public:
    BucketItem(Block*);
    ~BucketItem() override;
    Block* m_block;
};

class MinecartItem : public Item {
public:
    MinecartItem(const MinecartType*);
    void* m_unknown[1];
};

class SaddleItem : public Item {
public:
    SaddleItem();
    ~SaddleItem() override;
};

class RedStoneDustItem : public Item {
public:
    RedStoneDustItem();
    ~RedStoneDustItem() override;
};

class SnowballItem : public Item {
public:
    SnowballItem();
    ~SnowballItem() override;
};

class BoatItem : public Item {
public:
    BoatItem(int);
    ~BoatItem() override;
    int m_type;
};

class MilkBucketItem : public Item {
public:
    MilkBucketItem();
    ~MilkBucketItem() override;
};

class BookItem : public Item {
public:
    BookItem();
    ~BookItem() override;
};

class EggItem : public Item {
public:
    EggItem();
    ~EggItem() override;
};

class CompassItem : public Item {
public:
    CompassItem();
    void* m_unknown[4];
};

class ClockItem : public Item {
public:
    ClockItem();
    void* m_unknown[4];
};

class FishFoodItem : public FoodItem {
public:
    FishFoodItem(bool);
};

class DyeItem : public Item {
public:
    DyeItem();
    void* m_unknown[16];
};

class BedItem : public Item {
public:
    BedItem();
    void* m_unknown[1];
};

class ShearsItem : public Item {
public:
    ShearsItem();
};

class EnderpearlItem : public Item {
public:
    EnderpearlItem();
    ~EnderpearlItem() override;
};

class PotionItem : public Item {
public:
    PotionItem();
    void* m_unknown[2];
};

class BottleItem : public Item {
public:
    BottleItem();
    ~BottleItem() override;
};

class EnderEyeItem : public Item {
public:
    EnderEyeItem();
    ~EnderEyeItem() override;
};

class SpawnEggItem : public Item {
public:
    SpawnEggItem();
    void* m_unknown[1];
};

class ExperienceBottleItem : public Item {
public:
    ExperienceBottleItem();
    ~ExperienceBottleItem() override;
};

class FireChargeItem : public Item {
public:
    FireChargeItem();
    void* m_unknown[1];
};

class WritableBookItem : public Item {
public:
    WritableBookItem();
    ~WritableBookItem() override;
};

class WrittenBookItem : public Item {
public:
    WrittenBookItem();
    ~WrittenBookItem() override;
};

class SeedFoodItem : public FoodItem {
public:
    SeedFoodItem(int, float, Block*, Block*);
    void* m_unknown[2];
};

class CarrotOnAStickItem : public Item {
public:
    CarrotOnAStickItem();
    ~CarrotOnAStickItem() override;
};

class SimpleFoiledItem : public Item {
public:
    SimpleFoiledItem();
    ~SimpleFoiledItem() override;
};

class FireworksItem : public Item {
public:
    FireworksItem();
    ~FireworksItem() override;
};

class FireworkChargeItem : public Item {
public:
    FireworkChargeItem();
    void* m_unknown[1];
};

class EnchantedBookItem : public Item {
public:
    EnchantedBookItem();
    ~EnchantedBookItem() override;
};

class NameTagItem : public Item {
public:
    NameTagItem();
    ~NameTagItem() override;
};

class BannerItem : public BlockItem {
public:
    BannerItem();
};

class EndCrystalItem : public Item {
public:
    EndCrystalItem();
};

class ChorusFruitItem : public FoodItem {
public:
    ChorusFruitItem(int, float);
};

class SplashPotionItem : public PotionItem {
public:
    SplashPotionItem();
};

class SpectralArrowItem : public ArrowItem {
public:
    SpectralArrowItem();
};

class TippedArrowItem : public ArrowItem {
public:
    TippedArrowItem();
    void* m_unknown[1];
};

class LingeringPotionItem : public PotionItem {
public:
    LingeringPotionItem();
};

class RecordItem : public Item {
public:
    RecordItem(const std::wstring&, unsigned int, SoundEvent*);
    void* m_unknown[5];
};

namespace ItemBootstrap {
extern const int LEATHER_ARMOR_TEXTURES[2];
}
