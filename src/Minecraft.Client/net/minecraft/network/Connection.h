#pragma once

#include "net/minecraft/network/Socket.h"
#include "net/minecraft/network/protocol/game/DisconnectPacket.h"
#include "nn/os/os_MutexTypes.h"
#include <deque>

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
    static int sReadConnections;   // runRead
    static int sWriteConnections;  // runWrite

    static int dword_71017865A0[256];  // read
    static int dword_71017869A0[256];  // write

    bool getAndSetRunning(bool);
    void _init();
    ~Connection();
    Connection(Socket*, const std::wstring&, PacketListener*);

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
    int mTicksSinceLastPacket;
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
