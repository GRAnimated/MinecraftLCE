/**
 * @file socket.h
 * @brief Functions for opening sockets for wireless communication.
 */

#pragma once

#include <nn/types.h>
#include <nn/util.h>
#include <sys/socket.h>

struct in_addr;

namespace nn {
namespace socket {

#if NN_SDK_VER >= NN_MAKE_VER(7, 0, 0)
struct InAddr {
    u32 addr;
};
#else
using InAddr = ::in_addr;
#endif

Result Initialize(void* pool, ulong poolSize, ulong allocPoolSize, int concurLimit);
Result Finalize();
s32 SetSockOpt(s32 socket, s32 socketLevel, s32 option, const void*, u32 len);
u64 Send(s32 socket, const void* buffer, u64 bufferLength, s32 flags);
s32 Socket(s32 domain, s32 type, s32 protocol);
u16 InetHtons(u16);
u32 InetAton(const char* addressStr, InAddr* addressOut);
u32 Connect(s32 socket, const sockaddr* addr, u32 addrLen);
Result Close(s32 socket);
u32 Bind(s32 socket, const sockaddr* addr, u32 addrLen);
u32 Listen(s32 socket, s32 backlog);
u32 Accept(s32 socket, sockaddr* addrOut, u32* addrLenOut);
s32 Recv(s32 socket, void* out, ulong outLen, s32 flags);
u32 GetLastErrno();

}  // namespace socket
}  // namespace nn
