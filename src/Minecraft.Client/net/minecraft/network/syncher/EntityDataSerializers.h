#pragma once

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/syncher/EntityDataSerializer.h"

#include "types.h"
#include <string>

class EntityDataSerializers {
public:
    class BYTE_EntityDataSerializer : public EntityDataSerializer<unsigned char> {
    public:
        BYTE_EntityDataSerializer(EntityDataSerializerEnum::EEntityDataSerializer);
        void write(DataOutputStream* outputStream, unsigned char value) const override;
        unsigned char read(DataInputStream* inputStream) const override;
        EntityDataAccessor_Base* createAccessor(int) override;
        unsigned char copy(unsigned char) const override;
        EntityDataAccessor_Base* getOrCreateStoredAccessor(int) override;
    };

    class INT_EntityDataSerializer : public EntityDataSerializer<int> {
    public:
        INT_EntityDataSerializer(EntityDataSerializerEnum::EEntityDataSerializer);
        void write(DataOutputStream* outputStream, int value) const override;
        int read(DataInputStream* inputStream) const override;
        EntityDataAccessor_Base* createAccessor(int) override;
        int copy(int) const override;
        EntityDataAccessor_Base* getOrCreateStoredAccessor(int) override;
    };

    class FLOAT_EntityDataSerializer : public EntityDataSerializer<float> {
    public:
        FLOAT_EntityDataSerializer(EntityDataSerializerEnum::EEntityDataSerializer);
        void write(DataOutputStream* outputStream, float value) const override;
        float read(DataInputStream* inputStream) const override;
        EntityDataAccessor_Base* createAccessor(int) override;
        float copy(float) const override;
        EntityDataAccessor_Base* getOrCreateStoredAccessor(int) override;
    };

    class STRING_EntityDataSerializer : public EntityDataSerializer<std::wstring> {
    public:
        STRING_EntityDataSerializer(EntityDataSerializerEnum::EEntityDataSerializer);
        void write(DataOutputStream* outputStream, std::wstring value) const override;
        std::wstring read(DataInputStream* inputStream) const override;
        EntityDataAccessor_Base* createAccessor(int) override;
        std::wstring copy(std::wstring) const override;
        EntityDataAccessor_Base* getOrCreateStoredAccessor(int) override;
    };

    class ITEM_INSTANCE_EntityDataSerializer : public EntityDataSerializer<not_null_ptr<ItemInstance>> {
    public:
        ITEM_INSTANCE_EntityDataSerializer(EntityDataSerializerEnum::EEntityDataSerializer);
        void write(DataOutputStream* outputStream, not_null_ptr<ItemInstance> value) const override;
        not_null_ptr<ItemInstance> read(DataInputStream* inputStream) const override;
        EntityDataAccessor_Base* createAccessor(int) override;
        not_null_ptr<ItemInstance> copy(not_null_ptr<ItemInstance>) const override;
        EntityDataAccessor_Base* getOrCreateStoredAccessor(int) override;
    };

    class BLOCK_STATE_EntityDataSerializer : public EntityDataSerializer<const BlockState*> {
    public:
        BLOCK_STATE_EntityDataSerializer(EntityDataSerializerEnum::EEntityDataSerializer);
        void write(DataOutputStream* outputStream, const BlockState* value) const override;
        const BlockState* read(DataInputStream* inputStream) const override;
        EntityDataAccessor_Base* createAccessor(int) override;
        const BlockState* copy(const BlockState*) const override;
        EntityDataAccessor_Base* getOrCreateStoredAccessor(int) override;
    };

    class BOOLEAN_EntityDataSerializer : public EntityDataSerializer<bool> {
    public:
        BOOLEAN_EntityDataSerializer(EntityDataSerializerEnum::EEntityDataSerializer);
        void write(DataOutputStream* outputStream, bool value) const override;
        bool read(DataInputStream* inputStream) const override;
        EntityDataAccessor_Base* createAccessor(int) override;
        bool copy(bool) const override;
        EntityDataAccessor_Base* getOrCreateStoredAccessor(int) override;
    };

    class ROTATIONS_EntitySerializer : public EntityDataSerializer<const Rotations*> {
    public:
        ROTATIONS_EntitySerializer(EntityDataSerializerEnum::EEntityDataSerializer);

        void write(DataOutputStream* outputStream, const Rotations* value) const override;
        const Rotations* read(DataInputStream* inputStream) const override;
        EntityDataAccessor_Base* createAccessor(int) override;
        const Rotations* copy(const Rotations*) const override;
        EntityDataAccessor_Base* getOrCreateStoredAccessor(int) override;
    };

    class BLOCK_POS_EntityDataSerializer : public EntityDataSerializer<BlockPos> {
    public:
        BLOCK_POS_EntityDataSerializer(EntityDataSerializerEnum::EEntityDataSerializer);

        void write(DataOutputStream* outputStream, BlockPos value) const override;
        BlockPos read(DataInputStream* inputStream) const override;
        EntityDataAccessor_Base* createAccessor(int) override;
        BlockPos copy(BlockPos) const override;
        EntityDataAccessor_Base* getOrCreateStoredAccessor(int) override;
    };

    class OPTIONAL_BLOCK_POS_EntityDataSerializer : public EntityDataSerializer<BlockPos*> {
    public:
        OPTIONAL_BLOCK_POS_EntityDataSerializer(EntityDataSerializerEnum::EEntityDataSerializer);

        void write(DataOutputStream* outputStream, BlockPos* value) const override;
        BlockPos* read(DataInputStream* inputStream) const override;
        EntityDataAccessor_Base* createAccessor(int) override;
        BlockPos* copy(BlockPos*) const override;
        EntityDataAccessor_Base* getOrCreateStoredAccessor(int) override;
    };

    class DIRECTION_EntityDataSerializer : public EntityDataSerializer<const Direction*> {
    public:
        DIRECTION_EntityDataSerializer(EntityDataSerializerEnum::EEntityDataSerializer);

        void write(DataOutputStream* outputStream, const Direction* value) const override;
        const Direction* read(DataInputStream* inputStream) const override;
        EntityDataAccessor_Base* createAccessor(int) override;
        const Direction* copy(const Direction*) const override;
        EntityDataAccessor_Base* getOrCreateStoredAccessor(int) override;
    };

    class COMPOUND_TAG_EntityDataSerializer : public EntityDataSerializer<CompoundTag*> {
    public:
        COMPOUND_TAG_EntityDataSerializer(EntityDataSerializerEnum::EEntityDataSerializer);

        void write(DataOutputStream* outputStream, CompoundTag* value) const override;
        CompoundTag* read(DataInputStream* inputStream) const override;
        EntityDataAccessor_Base* createAccessor(int) override;
        CompoundTag* copy(CompoundTag*) const override;
        EntityDataAccessor_Base* getOrCreateStoredAccessor(int) override;
    };

    static BYTE_EntityDataSerializer* sBYTE_EntityDataSerializer;
    static INT_EntityDataSerializer* sINT_EntityDataSerializer;
    static FLOAT_EntityDataSerializer* sFLOAT_EntityDataSerializer;
    static STRING_EntityDataSerializer* sSTRING_EntityDataSerializer;
    static ITEM_INSTANCE_EntityDataSerializer* sITEM_INSTANCE_EntityDataSerializer;
    static BLOCK_STATE_EntityDataSerializer* sBLOCK_STATE_EntityDataSerializer;
    static BOOLEAN_EntityDataSerializer* sBOOLEAN_EntityDataSerializer;
    static ROTATIONS_EntitySerializer* sROTATIONS_EntitySerializer;
    static BLOCK_POS_EntityDataSerializer* sBLOCK_POS_EntityDataSerializer;
    static OPTIONAL_BLOCK_POS_EntityDataSerializer* sOPTIONAL_BLOCK_POS_EntityDataSerializer;
    static DIRECTION_EntityDataSerializer* sDIRECTION_EntityDataSerializer;
    static COMPOUND_TAG_EntityDataSerializer* sCOMPOUND_TAG_EntityDataSerializer;
};
