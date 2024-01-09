#pragma once

#include <nn/types.h>

namespace nn::nex {

namespace TransportProtocol {
enum class Type {
    unk1,
    unk2,
    unk3,
    unk4,
    unk5,
    unk6,
};
}

namespace SocketDriver {

struct InetAddress {};
enum _SocketFlag {};

}  // namespace SocketDriver

namespace BerkeleySocketDriver {
class BerkeleySocket {
public:
    BerkeleySocket();
    BerkeleySocket(const BerkeleySocket*, int);
    ~BerkeleySocket();

    bool Open(TransportProtocol::Type);
    bool SetAsync(bool);
    bool SetBroadcastMode(bool);
    bool Bind(u16&);
    bool LastSocketErrorToResult(const char*, long);
    s32 GetLastSocketError(long);
    s32 RecvFrom(u8*, ulong, SocketDriver::InetAddress*, u64*, SocketDriver::_SocketFlag);
};
}  // namespace BerkeleySocketDriver
}  // namespace nn::nex
