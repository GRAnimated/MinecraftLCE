#pragma once

#include <deque>
#include "Minecraft.Network/Socket.h"
#include "Minecraft.Network/protocol/game/DisconnectPacket.h"
#include "nn/os/os_MutexTypes.h"

class Socket;
class DataInputStream;
class DataOutputStream;
class OutputStream;
class ByteArrayOutputStream;
class PacketListener;
class C4JThreadImpl;
class C4JEventImpl;
class Packet;

class Connection {
public:
    static int dword_7101786598;  // runRead
    static int dword_710178659C;  // runWrite

    static int dword_71017865A0[256];  // read
    static int dword_71017869A0[256];  // write

    bool getAndSetRunning(bool);
    void _init();
    ~Connection();
    Connection(Socket*, std::wstring const&, PacketListener*);

    static int runRead(void*);
    static int runWrite(void*);
    void setListener(PacketListener*);
    void send(std::shared_ptr<Packet>);
    void queueSend(std::__1::shared_ptr<Packet>);
    bool writeTick();
    void flush();
    bool readTick();
    void close(DisconnectPacket::eDisconnectReason);
    void tick();
    void sendAndQuit();

    Socket* mSocket;
    long mRemoteSocketAddress;
    DataInputStream* mDataInputStream;
    DataOutputStream* mDataOutputStream;
    DataOutputStream* mDataOutputStream2;
    ByteArrayOutputStream* mByteArrayOutputStream;
    Socket::SocketOutputStream* mSocketOutputStream;
    bool mIsRunning;
    nn::os::MutexType mIsRunningMutex;
    std::deque<std::shared_ptr<Packet>> mIncomingQueue;
    nn::os::MutexType mIncomingMutex;
    std::deque<std::shared_ptr<Packet>> mOutgoingQueue;
    std::deque<std::shared_ptr<Packet>> mSlowOutgoingQueue;
    PacketListener* mPacketListener;
    bool mIsDisconnecting;
    bool field_119;
    C4JThreadImpl* mRunReadThread;
    C4JThreadImpl* mRunWriteThread;
    C4JEventImpl* mC4JEventImpl1;
    C4JEventImpl* mC4JEventImpl2;
    void* qword_140;
    bool byte_148;
    int dword_14c;
    void* qword_150;
    int field_158;
    int mEstimatedSize;
    unsigned int field_160;
    unsigned int field_164;
    int mFakeLag;
    int dword_16C;
    nn::os::MutexType mCountMutex;
    nn::os::MutexType mOutgoingMutex;
    int mDelay;
    int dword_1b4;
    long mTimeInMs;
};
