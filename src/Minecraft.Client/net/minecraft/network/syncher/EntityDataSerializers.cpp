#include "net/minecraft/network/syncher/EntityDataSerializers.h"

#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/core/Rotations.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/state/BlockState.h"

EntityDataSerializers::BYTE_EntityDataSerializer::BYTE_EntityDataSerializer(
    EntityDataSerializerEnum::EEntityDataSerializer id)
    : EntityDataSerializer<unsigned char>(id) {}

void EntityDataSerializers::BYTE_EntityDataSerializer::write(DataOutputStream* outputStream,
                                                             unsigned char value) const {
    outputStream->writeByte(value);
}

unsigned char EntityDataSerializers::BYTE_EntityDataSerializer::read(DataInputStream* inputStream) const {
    return inputStream->readByte();
}

EntityDataAccessor_Base* EntityDataSerializers::BYTE_EntityDataSerializer::createAccessor(int id) {
    return getOrCreateStoredAccessor(id);
}

unsigned char EntityDataSerializers::BYTE_EntityDataSerializer::copy(unsigned char value) const {
    return value;
}

EntityDataAccessor_Base* EntityDataSerializers::BYTE_EntityDataSerializer::getOrCreateStoredAccessor(int id) {
    auto it = m_accessors.find(id);
    if (it != m_accessors.end())
        return it->second;

    auto accessor = new EntityDataAccessor<unsigned char>(id, this);
    m_accessors[id] = accessor;
    return accessor;
}

EntityDataSerializers::INT_EntityDataSerializer::INT_EntityDataSerializer(
    EntityDataSerializerEnum::EEntityDataSerializer id)
    : EntityDataSerializer<int>(id) {}

void EntityDataSerializers::INT_EntityDataSerializer::write(DataOutputStream* outputStream, int value) const {
    outputStream->writeVarInt(value);
}

int EntityDataSerializers::INT_EntityDataSerializer::read(DataInputStream* inputStream) const {
    return inputStream->readVarInt();
}

EntityDataAccessor_Base* EntityDataSerializers::INT_EntityDataSerializer::createAccessor(int id) {
    return getOrCreateStoredAccessor(id);
}

int EntityDataSerializers::INT_EntityDataSerializer::copy(int value) const {
    return value;
}

EntityDataAccessor_Base* EntityDataSerializers::INT_EntityDataSerializer::getOrCreateStoredAccessor(int id) {
    auto it = m_accessors.find(id);
    if (it != m_accessors.end())
        return it->second;

    auto accessor = new EntityDataAccessor<int>(id, this);
    m_accessors[id] = accessor;
    return accessor;
}

EntityDataSerializers::FLOAT_EntityDataSerializer::FLOAT_EntityDataSerializer(
    EntityDataSerializerEnum::EEntityDataSerializer id)
    : EntityDataSerializer<float>(id) {}

void EntityDataSerializers::FLOAT_EntityDataSerializer::write(DataOutputStream* outputStream,
                                                              float value) const {
    outputStream->writeFloat(value);
}

float EntityDataSerializers::FLOAT_EntityDataSerializer::read(DataInputStream* inputStream) const {
    return inputStream->readFloat();
}

EntityDataAccessor_Base* EntityDataSerializers::FLOAT_EntityDataSerializer::createAccessor(int id) {
    return getOrCreateStoredAccessor(id);
}

float EntityDataSerializers::FLOAT_EntityDataSerializer::copy(float value) const {
    return value;
}

EntityDataAccessor_Base*
EntityDataSerializers::FLOAT_EntityDataSerializer::getOrCreateStoredAccessor(int id) {
    auto it = m_accessors.find(id);
    if (it != m_accessors.end())
        return it->second;

    auto accessor = new EntityDataAccessor<float>(id, this);
    m_accessors[id] = accessor;
    return accessor;
}

EntityDataSerializers::STRING_EntityDataSerializer::STRING_EntityDataSerializer(
    EntityDataSerializerEnum::EEntityDataSerializer id)
    : EntityDataSerializer<std::wstring>(id) {}

void EntityDataSerializers::STRING_EntityDataSerializer::write(DataOutputStream* outputStream,
                                                               std::wstring value) const {
    outputStream->writeUTF(value);
}

std::wstring EntityDataSerializers::STRING_EntityDataSerializer::read(DataInputStream* inputStream) const {
    return inputStream->readUTF();
}

EntityDataAccessor_Base* EntityDataSerializers::STRING_EntityDataSerializer::createAccessor(int id) {
    return getOrCreateStoredAccessor(id);
}

std::wstring EntityDataSerializers::STRING_EntityDataSerializer::copy(std::wstring value) const {
    return value;
}

EntityDataAccessor_Base*
EntityDataSerializers::STRING_EntityDataSerializer::getOrCreateStoredAccessor(int id) {
    auto it = m_accessors.find(id);
    if (it != m_accessors.end())
        return it->second;

    auto accessor = new EntityDataAccessor<std::wstring>(id, this);
    m_accessors[id] = accessor;
    return accessor;
}

EntityDataSerializers::ITEM_INSTANCE_EntityDataSerializer::ITEM_INSTANCE_EntityDataSerializer(
    EntityDataSerializerEnum::EEntityDataSerializer id)
    : EntityDataSerializer<not_null_ptr<ItemInstance>>(id) {}

void EntityDataSerializers::ITEM_INSTANCE_EntityDataSerializer::write(
    DataOutputStream* outputStream, not_null_ptr<ItemInstance> value) const {
    outputStream->writeItem(value);
}

not_null_ptr<ItemInstance>
EntityDataSerializers::ITEM_INSTANCE_EntityDataSerializer::read(DataInputStream* inputStream) const {
    return inputStream->readItem();
}

EntityDataAccessor_Base* EntityDataSerializers::ITEM_INSTANCE_EntityDataSerializer::createAccessor(int id) {
    return getOrCreateStoredAccessor(id);
}

not_null_ptr<ItemInstance>
EntityDataSerializers::ITEM_INSTANCE_EntityDataSerializer::copy(not_null_ptr<ItemInstance> value) const {
    return value->copy();
}

EntityDataAccessor_Base*
EntityDataSerializers::ITEM_INSTANCE_EntityDataSerializer::getOrCreateStoredAccessor(int id) {
    auto it = m_accessors.find(id);
    if (it != m_accessors.end())
        return it->second;

    auto accessor = new EntityDataAccessor<not_null_ptr<ItemInstance>>(id, this);
    m_accessors[id] = accessor;
    return accessor;
}

EntityDataSerializers::BLOCK_STATE_EntityDataSerializer::BLOCK_STATE_EntityDataSerializer(
    EntityDataSerializerEnum::EEntityDataSerializer id)
    : EntityDataSerializer<const BlockState*>(id) {}

void EntityDataSerializers::BLOCK_STATE_EntityDataSerializer::write(DataOutputStream* outputStream,
                                                                    const BlockState* value) const {
    if (value)
        outputStream->writeVarInt(Block::getIdWithData(value));
    else
        outputStream->writeVarInt(0);
}

const BlockState*
EntityDataSerializers::BLOCK_STATE_EntityDataSerializer::read(DataInputStream* inputStream) const {
    int id = inputStream->readVarInt();
    if (id == 0)
        return nullptr;
    return Block::stateByIdWithData(id);
}

EntityDataAccessor_Base* EntityDataSerializers::BLOCK_STATE_EntityDataSerializer::createAccessor(int id) {
    return getOrCreateStoredAccessor(id);
}

const BlockState*
EntityDataSerializers::BLOCK_STATE_EntityDataSerializer::copy(const BlockState* value) const {
    return value;
}

EntityDataAccessor_Base*
EntityDataSerializers::BLOCK_STATE_EntityDataSerializer::getOrCreateStoredAccessor(int id) {
    auto it = m_accessors.find(id);
    if (it != m_accessors.end())
        return it->second;

    auto accessor = new EntityDataAccessor<const BlockState*>(id, this);
    m_accessors[id] = accessor;
    return accessor;
}

EntityDataSerializers::BOOLEAN_EntityDataSerializer::BOOLEAN_EntityDataSerializer(
    EntityDataSerializerEnum::EEntityDataSerializer id)
    : EntityDataSerializer<bool>(id) {}

void EntityDataSerializers::BOOLEAN_EntityDataSerializer::write(DataOutputStream* outputStream,
                                                                bool value) const {
    outputStream->writeBoolean(value);
}

bool EntityDataSerializers::BOOLEAN_EntityDataSerializer::read(DataInputStream* inputStream) const {
    return inputStream->readBoolean();
}

EntityDataAccessor_Base* EntityDataSerializers::BOOLEAN_EntityDataSerializer::createAccessor(int id) {
    return getOrCreateStoredAccessor(id);
}

bool EntityDataSerializers::BOOLEAN_EntityDataSerializer::copy(bool value) const {
    return value;
}

EntityDataAccessor_Base*
EntityDataSerializers::BOOLEAN_EntityDataSerializer::getOrCreateStoredAccessor(int id) {
    auto it = m_accessors.find(id);
    if (it != m_accessors.end())
        return it->second;

    auto accessor = new EntityDataAccessor<bool>(id, this);
    m_accessors[id] = accessor;
    return accessor;
}

EntityDataSerializers::ROTATIONS_EntitySerializer::ROTATIONS_EntitySerializer(
    EntityDataSerializerEnum::EEntityDataSerializer id)
    : EntityDataSerializer<const Rotations*>(id) {}

void EntityDataSerializers::ROTATIONS_EntitySerializer::write(DataOutputStream* outputStream,
                                                              const Rotations* value) const {
    outputStream->writeFloat(value->getX());
    outputStream->writeFloat(value->getY());
    outputStream->writeFloat(value->getZ());
}

const Rotations* EntityDataSerializers::ROTATIONS_EntitySerializer::read(DataInputStream* inputStream) const {
    float x = inputStream->readFloat();
    float y = inputStream->readFloat();
    float z = inputStream->readFloat();
    return new Rotations(x, y, z);
}

EntityDataAccessor_Base* EntityDataSerializers::ROTATIONS_EntitySerializer::createAccessor(int id) {
    return getOrCreateStoredAccessor(id);
}

const Rotations* EntityDataSerializers::ROTATIONS_EntitySerializer::copy(const Rotations* value) const {
    return Rotations::copy(value);
}

EntityDataAccessor_Base*
EntityDataSerializers::ROTATIONS_EntitySerializer::getOrCreateStoredAccessor(int id) {
    auto it = m_accessors.find(id);
    if (it != m_accessors.end())
        return it->second;

    auto accessor = new EntityDataAccessor<const Rotations*>(id, this);
    m_accessors[id] = accessor;
    return accessor;
}

EntityDataSerializers::BLOCK_POS_EntityDataSerializer::BLOCK_POS_EntityDataSerializer(
    EntityDataSerializerEnum::EEntityDataSerializer id)
    : EntityDataSerializer<BlockPos>(id) {}

void EntityDataSerializers::BLOCK_POS_EntityDataSerializer::write(DataOutputStream* outputStream,
                                                                  BlockPos value) const {
    outputStream->writeBlockPos(value);
}

BlockPos EntityDataSerializers::BLOCK_POS_EntityDataSerializer::read(DataInputStream* inputStream) const {
    return inputStream->readBlockPos();
}

EntityDataAccessor_Base* EntityDataSerializers::BLOCK_POS_EntityDataSerializer::createAccessor(int id) {
    return getOrCreateStoredAccessor(id);
}

BlockPos EntityDataSerializers::BLOCK_POS_EntityDataSerializer::copy(BlockPos value) const {
    return value;
}

EntityDataAccessor_Base*
EntityDataSerializers::BLOCK_POS_EntityDataSerializer::getOrCreateStoredAccessor(int id) {
    auto it = m_accessors.find(id);
    if (it != m_accessors.end())
        return it->second;

    auto accessor = new EntityDataAccessor<BlockPos>(id, this);
    m_accessors[id] = accessor;
    return accessor;
}

EntityDataSerializers::OPTIONAL_BLOCK_POS_EntityDataSerializer::OPTIONAL_BLOCK_POS_EntityDataSerializer(
    EntityDataSerializerEnum::EEntityDataSerializer id)
    : EntityDataSerializer<BlockPos*>(id) {}

void EntityDataSerializers::OPTIONAL_BLOCK_POS_EntityDataSerializer::write(DataOutputStream* outputStream,
                                                                           BlockPos* value) const {
    outputStream->writeBoolean(value != nullptr);
    if (value)
        outputStream->writeBlockPos(*value);
}

BlockPos*
EntityDataSerializers::OPTIONAL_BLOCK_POS_EntityDataSerializer::read(DataInputStream* inputStream) const {
    if (inputStream->readBoolean())
        return inputStream->readBlockPosPointer();
    return nullptr;
}

EntityDataAccessor_Base*
EntityDataSerializers::OPTIONAL_BLOCK_POS_EntityDataSerializer::createAccessor(int id) {
    return getOrCreateStoredAccessor(id);
}

BlockPos* EntityDataSerializers::OPTIONAL_BLOCK_POS_EntityDataSerializer::copy(BlockPos* value) const {
    if (!value)
        return nullptr;
    return new BlockPos(*value);
}

EntityDataAccessor_Base*
EntityDataSerializers::OPTIONAL_BLOCK_POS_EntityDataSerializer::getOrCreateStoredAccessor(int id) {
    auto it = m_accessors.find(id);
    if (it != m_accessors.end())
        return it->second;

    auto accessor = new EntityDataAccessor<BlockPos*>(id, this);
    m_accessors[id] = accessor;
    return accessor;
}

EntityDataSerializers::DIRECTION_EntityDataSerializer::DIRECTION_EntityDataSerializer(
    EntityDataSerializerEnum::EEntityDataSerializer id)
    : EntityDataSerializer<const Direction*>(id) {}

void EntityDataSerializers::DIRECTION_EntityDataSerializer::write(DataOutputStream* outputStream,
                                                                  const Direction* value) const {
    outputStream->write(value->get3DDataValue());
}

const Direction*
EntityDataSerializers::DIRECTION_EntityDataSerializer::read(DataInputStream* inputStream) const {
    return Direction::from3DDataValue(inputStream->read());
}

EntityDataAccessor_Base* EntityDataSerializers::DIRECTION_EntityDataSerializer::createAccessor(int id) {
    return getOrCreateStoredAccessor(id);
}

const Direction* EntityDataSerializers::DIRECTION_EntityDataSerializer::copy(const Direction* value) const {
    return value;
}

EntityDataAccessor_Base*
EntityDataSerializers::DIRECTION_EntityDataSerializer::getOrCreateStoredAccessor(int id) {
    auto it = m_accessors.find(id);
    if (it != m_accessors.end())
        return it->second;

    auto accessor = new EntityDataAccessor<const Direction*>(id, this);
    m_accessors[id] = accessor;
    return accessor;
}

EntityDataSerializers::COMPOUND_TAG_EntityDataSerializer::COMPOUND_TAG_EntityDataSerializer(
    EntityDataSerializerEnum::EEntityDataSerializer id)
    : EntityDataSerializer<CompoundTag*>(id) {}

void EntityDataSerializers::COMPOUND_TAG_EntityDataSerializer::write(DataOutputStream* outputStream,
                                                                     CompoundTag* value) const {
    outputStream->writeNbt(value);
}

CompoundTag*
EntityDataSerializers::COMPOUND_TAG_EntityDataSerializer::read(DataInputStream* inputStream) const {
    return inputStream->readNbt();
}

EntityDataAccessor_Base* EntityDataSerializers::COMPOUND_TAG_EntityDataSerializer::createAccessor(int id) {
    return getOrCreateStoredAccessor(id);
}

CompoundTag* EntityDataSerializers::COMPOUND_TAG_EntityDataSerializer::copy(CompoundTag* value) const {
    return value->copy();
}

EntityDataAccessor_Base*
EntityDataSerializers::COMPOUND_TAG_EntityDataSerializer::getOrCreateStoredAccessor(int id) {
    auto it = m_accessors.find(id);
    if (it != m_accessors.end())
        return it->second;

    auto accessor = new EntityDataAccessor<CompoundTag*>(id, this);
    m_accessors[id] = accessor;
    return accessor;
}
