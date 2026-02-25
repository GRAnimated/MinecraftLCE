#pragma once

#include "net/minecraft/network/protocol/Packet.h"
#include "net/minecraft/world/InteractionHand.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/phys/Vec3.h"

class ServerboundInteractPacket : public Packet,
                                  public std::enable_shared_from_this<ServerboundInteractPacket> {
public:
    static std::shared_ptr<Packet> create();

    enum eAction {
        Interact = 0,
        Attack = 1,
        InteractAt = 2,
    };

    ServerboundInteractPacket();
    ServerboundInteractPacket(std::shared_ptr<Entity> target);
    ServerboundInteractPacket(std::shared_ptr<Entity> target, InteractionHand::EInteractionHand hand);
    ServerboundInteractPacket(std::shared_ptr<Entity> target, InteractionHand::EInteractionHand hand,
                              Vec3* location);
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    std::shared_ptr<Entity> getTarget(Level* level);
    eAction getAction();
    InteractionHand::EInteractionHand getHand();
    Vec3* getLocation();

private:
    int m_target;
    eAction m_action;
    Vec3* m_location;
    InteractionHand::EInteractionHand m_hand;
};
