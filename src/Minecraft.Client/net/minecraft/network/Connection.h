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

    Socket* m_socket;
    long m_remoteSocketAddress;
    DataInputStream* m_dataInputStream;
    DataOutputStream* m_dataOutputStream;
    DataOutputStream* m_dataOutputStream2;
    ByteArrayOutputStream* m_byteArrayOutputStream;
    Socket::SocketOutputStream* m_socketOutputStream;
    bool m_isRunning;
    nn::os::MutexType m_isRunningMutex;
    std::deque<std::shared_ptr<Packet>> m_incomingQueue;
    nn::os::MutexType m_incomingMutex;
    std::deque<std::shared_ptr<Packet>> m_outgoingQueue;
    std::deque<std::shared_ptr<Packet>> m_slowOutgoingQueue;
    PacketListener* m_packetListener;
    bool m_isDisconnecting;
    bool m_field119;
    C4JThreadImpl* m_runReadThread;
    C4JThreadImpl* m_runWriteThread;
    C4JEventImpl* m_c4JEventImpl1;
    C4JEventImpl* m_c4JEventImpl2;
    void* m_qword140;
    bool m_byte148;
    int m_dword14c;
    void* m_qword150;
    int m_ticksSinceLastPacket;
    int m_estimatedSize;
    unsigned int m_field160;
    unsigned int m_field164;
    int m_fakeLag;
    int m_dword16C;
    nn::os::MutexType m_countMutex;
    nn::os::MutexType m_outgoingMutex;
    int m_delay;
    int m_dword1b4;
    long m_timeInMs;
};
