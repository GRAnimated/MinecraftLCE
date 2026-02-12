#include "net/minecraft/network/Connection.h"

#include "4JLibraries_Source/NX/Thread/C4JEventImpl.h"
#include "4JLibraries_Source/NX/Thread/C4JThreadImpl.h"
#include "NX/Platform.h"
#include "java/io/BufferedOutputStream.h"
#include "java/io/ByteArrayOutputStream.h"
#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "java/io/File.h"
#include "net/minecraft/client/CGameNetworkManager.h"
#include "net/minecraft/client/Compression.h"
#include "net/minecraft/client/ShutdownManager.h"
#include "net/minecraft/core/System.h"
#include "net/minecraft/network/PacketListener.h"
#include "net/minecraft/network/PacketType.h"
#include "net/minecraft/network/Socket.h"
#include "net/minecraft/network/protocol/game/ServerboundPlayerActionPacket.h"
#include "nn/os/os_Mutex.h"
#include "protocol/game/ClientboundKeepAlivePacket.h"
#include "protocol/game/ServerboundKeepAlivePacket.h"
#include <cstdio>
#include <memory>

bool Connection::getAndSetRunning(bool running) {
    EnterCriticalSection(&m_isRunningMutex);
    bool prevIsRunning = m_isRunning;
    m_isRunning = running;
    LeaveCriticalSection(&m_isRunningMutex);
    return prevIsRunning;
}

void Connection::_init() {
    InitializeCriticalSection(&m_outgoingMutex);
    InitializeCriticalSection(&m_countMutex);
    InitializeCriticalSection(&m_incomingMutex);
    m_isRunning = true;
    InitializeCriticalSection(&m_isRunningMutex);
    m_isDisconnecting = false;
    m_field119 = false;
    m_byte148 = false;
    m_dword14c = 0;
    m_fakeLag = 0;
    m_delay = 50;
    m_qword140 = nullptr;
    m_ticksSinceLastPacket = 0;
    m_estimatedSize = 0;
    m_field160 = 0;
    m_field164 = 0;
}

Connection::~Connection() {
    m_isRunning = false;

    nn::os::FinalizeMutex(&m_isRunningMutex);

    if (m_dataInputStream)
        m_dataInputStream->close();
    m_runReadThread->WaitForCompletion(0xFFFFFFFF);
    m_runWriteThread->WaitForCompletion(0xFFFFFFFF);

    nn::os::FinalizeMutex(&m_outgoingMutex);
    nn::os::FinalizeMutex(&m_countMutex);
    nn::os::FinalizeMutex(&m_incomingMutex);

    delete m_c4JEventImpl1;
    delete m_c4JEventImpl2;

    delete m_dataOutputStream2;
    m_dataOutputStream2 = nullptr;

    delete m_byteArrayOutputStream;
    m_byteArrayOutputStream = nullptr;

    if (m_dataOutputStream) {
        m_dataOutputStream->deleteChildStream();
        delete m_dataOutputStream;
        m_dataOutputStream = nullptr;
    }

    delete m_dataInputStream;
    m_dataInputStream = nullptr;

    delete m_runReadThread;
    m_runReadThread = nullptr;

    delete m_runWriteThread;
    m_runWriteThread = nullptr;
}

static char filename[0x100] = {};

Connection::Connection(Socket* socket, const std::wstring& type, PacketListener* packetListener)
    : m_incomingQueue(std::deque<std::shared_ptr<Packet>>()),
      m_outgoingQueue(std::deque<std::shared_ptr<Packet>>()),
      m_slowOutgoingQueue(std::deque<std::shared_ptr<Packet>>()) {
    _init();
    m_socket = socket;
    m_remoteSocketAddress = socket->getRemoteSocketAddress();
    m_packetListener = packetListener;

    socket->setSoTimeout(30000);
    socket->setTrafficClass(24);

    m_dataInputStream = new DataInputStream(socket->getInputStream(packetListener->isServerPacketListener()));

    m_socketOutputStream = socket->getOutputStream(packetListener->isServerPacketListener());
    m_dataOutputStream = new DataOutputStream(new BufferedOutputStream(m_socketOutputStream, 0x1400));

    m_byteArrayOutputStream = new ByteArrayOutputStream(0x1400);
    m_dataOutputStream2 = new DataOutputStream(m_byteArrayOutputStream);

    m_c4JEventImpl1 = new C4JEventImpl(C4JEvent::EMode::_0);
    m_c4JEventImpl2 = new C4JEventImpl(C4JEvent::EMode::_0);

    const char* name = wstringtofilename(type, filename);

    char readName[0x100];
    char writeName[0x100];
    sprintf(readName, "%s read\n", name);
    sprintf(writeName, "%s write\n", name);

    m_runReadThread = new C4JThreadImpl(Connection::runRead, this, readName, 0);
    m_runWriteThread = new C4JThreadImpl(Connection::runWrite, this, writeName, 0);

    m_runReadThread->SetProcessor(2);
    m_runWriteThread->SetProcessor(2);
    m_runReadThread->Run();
    m_runWriteThread->Run();

    m_timeInMs = 0;
}

int Connection::runRead(void* conn) {
    Connection* connection = (Connection*)conn;
    ShutdownManager::HasStarted(ShutdownManager::EThreadId::_8);
    if (connection) {
        Compression::CreateNewThreadStorage();
        EnterCriticalSection(&connection->m_countMutex);
        ++sReadConnections;
        LeaveCriticalSection(&connection->m_countMutex);
        MemSect(19);
        while (connection->m_isRunning) {
            if (connection->m_isDisconnecting || !ShutdownManager::ShouldRun(ShutdownManager::EThreadId::_8))
                break;
            while (connection->readTick() != 0)
                ;
            connection->m_c4JEventImpl1->WaitForSignal(100);
        }
        MemSect(0);
        Compression::ReleaseThreadStorage();
        ShutdownManager::HasFinished(ShutdownManager::EThreadId::_8);
        return 0;
    }
    return 0;
}

// NON_MATCHING: i've improved match within PULL_URL, it could be that it's just illusional improvement (as
// those are if and while hell)
int Connection::runWrite(void* conn) {
    Connection* connection = (Connection*)conn;
    ShutdownManager::HasStarted(ShutdownManager::EThreadId::_9);
    if (connection) {
        Compression::CreateNewThreadStorage();

        EnterCriticalSection(&connection->m_countMutex);
        ++sWriteConnections;
        LeaveCriticalSection(&connection->m_countMutex);

        if (connection->m_isRunning) {
            int writeStatus = 0;
            while (connection->m_isRunning || writeStatus) {  // issue is somewhere here
                if (!ShutdownManager::ShouldRun(ShutdownManager::EThreadId::_9))
                    break;

                long long startTime = System::processTimeInMilliSecs();

                bool writeSuccess = false;
                long long currentTime = startTime;

                do {
                    writeSuccess = connection->writeTick();
                    currentTime = System::processTimeInMilliSecs();

                    if (connection->m_dataOutputStream->getSize() == 0x7fffffff)
                        break;
                } while (writeSuccess | ((currentTime - startTime) > 199));

                writeStatus = connection->m_c4JEventImpl2->WaitForSignal(100);

                if (connection->m_dataOutputStream)
                    connection->m_dataOutputStream->flush();
            }
        }

        EnterCriticalSection(&connection->m_countMutex);
        --sWriteConnections;
        LeaveCriticalSection(&connection->m_countMutex);

        Compression::ReleaseThreadStorage();
    }

    ShutdownManager::HasFinished(ShutdownManager::EThreadId::_9);
    return 0;
}

void Connection::setListener(PacketListener* listener) {
    m_packetListener = listener;
}

void Connection::send(std::shared_ptr<Packet> packet) {
    if (!m_isDisconnecting) {
        m_timeInMs = System::processTimeInMilliSecs();
        MemSect(15);
        EnterCriticalSection(&m_outgoingMutex);
        m_estimatedSize += packet->getEstimatedSize() + 1;
        if (packet->m_shouldDelay) {
            packet->m_shouldDelay = false;
            m_slowOutgoingQueue.push_back(packet);
        } else {
            if (packet->getPacketId() == _ClientboundMapItemDataPacket)
                if (packet->tryReplaceDuplicatePacket(&m_outgoingQueue)) {
                    // TODO: Remove early return
                    LeaveCriticalSection(&m_outgoingMutex);
                    MemSect(0);
                    return;
                }

            m_outgoingQueue.push_back(packet);
        }
        LeaveCriticalSection(&m_outgoingMutex);
        MemSect(0);
    }
}

void Connection::queueSend(std::shared_ptr<Packet> packet) {
    if (!m_isDisconnecting) {
        EnterCriticalSection(&m_outgoingMutex);
        m_estimatedSize += packet->getEstimatedSize() + 1;
        m_slowOutgoingQueue.push_back(packet);
        LeaveCriticalSection(&m_outgoingMutex);
    }
}

bool Connection::writeTick() {
    if (!m_dataOutputStream || !m_dataOutputStream2)
        return false;

    bool returnValue;
    if (!m_outgoingQueue.empty()
        && (!m_fakeLag
            || (System::processTimeInMilliSecs() - m_outgoingQueue.front()->m_createdTime >= m_fakeLag))) {
        std::shared_ptr<Packet> packet;
        EnterCriticalSection(&m_outgoingMutex);

        packet = m_outgoingQueue.front();
        m_outgoingQueue.pop_front();

        m_estimatedSize -= packet->getEstimatedSize() + 1;
        LeaveCriticalSection(&m_outgoingMutex);

        Packet::writePacket(packet, m_dataOutputStream, m_packetListener->isServerPacketListener(),
                            m_field164);

        dword_71017869A0[packet->getPacketId()] += packet->getEstimatedSize() + 1;

        returnValue = true;
    } else {
        returnValue = false;
    }

    if (m_delay-- > 0 || m_slowOutgoingQueue.empty()
        || (m_fakeLag
            && System::processTimeInMilliSecs() - m_slowOutgoingQueue.front()->m_createdTime < m_fakeLag)) {
        return returnValue;
    }

    std::shared_ptr<Packet> packet;
    EnterCriticalSection(&m_outgoingMutex);
    packet = m_slowOutgoingQueue.front();
    m_slowOutgoingQueue.pop_front();

    m_estimatedSize -= packet->getEstimatedSize() + 1;
    LeaveCriticalSection(&m_outgoingMutex);

    if (packet->m_shouldDelay) {
        Packet::writePacket(packet, m_dataOutputStream2, m_packetListener->isServerPacketListener(),
                            m_field164);

        if (m_dataOutputStream)
            m_dataOutputStream->flush();
        m_socketOutputStream->writeWithFlags(m_byteArrayOutputStream->m_buffer, 0,
                                             m_byteArrayOutputStream->size(), 1);
        m_byteArrayOutputStream->clear();
    } else {
        Packet::writePacket(packet, m_dataOutputStream, m_packetListener->isServerPacketListener(),
                            m_field164);
    }

    dword_71017869A0[packet->getPacketId()] += packet->getEstimatedSize() + 1;

    m_delay = 0;
    return true;
}

void Connection::flush() {
    m_c4JEventImpl1->Set();
    m_c4JEventImpl2->Set();
}

bool Connection::readTick() {
    if (m_dataInputStream && !m_field119) {
        std::shared_ptr<Packet> packet = Packet::readPacket(
            m_dataInputStream, m_packetListener->isServerPacketListener(), m_field160, m_field119);
        if (packet) {
            dword_71017865A0[packet->getPacketId()] += packet->getEstimatedSize() + 1;
            EnterCriticalSection(&m_incomingMutex);
            if (!m_isDisconnecting)
                m_incomingQueue.push_back(packet);
            LeaveCriticalSection(&m_incomingMutex);
            return true;
        }
        return false;
    }
    return false;
}

void Connection::close(DisconnectPacket::eDisconnectReason reason) {
    if (!getAndSetRunning(false))
        return;
    m_byte148 = true;
    m_dword14c = reason;
    m_qword150 = nullptr;

    if (m_dataInputStream)
        m_dataInputStream->close();

    m_runReadThread->WaitForCompletion(0xFFFFFFFF);
    m_runWriteThread->WaitForCompletion(0xFFFFFFFF);

    delete m_dataInputStream;
    m_dataInputStream = nullptr;

    if (m_dataOutputStream) {
        m_dataOutputStream->close();
        m_dataOutputStream->deleteChildStream();
        delete m_dataOutputStream;
        m_dataOutputStream = nullptr;
    }

    if (m_dataOutputStream2) {
        m_dataOutputStream2->close();
        delete m_dataOutputStream2;
        m_dataOutputStream2 = nullptr;
    }

    if (m_socket) {
        m_socket->close(m_packetListener->isServerPacketListener());
        m_socket = nullptr;
    }
}

void Connection::tick() {
    if (m_field119)
        close(DisconnectPacket::eDisconnectReason::_29);
    if (m_estimatedSize > 0x100000)  // 1MB
        close(DisconnectPacket::eDisconnectReason::Overflow);
    EnterCriticalSection(&m_incomingMutex);
    long incomingQueueSize = m_incomingQueue.size();
    LeaveCriticalSection(&m_incomingMutex);
    if (incomingQueueSize != 0)
        m_ticksSinceLastPacket = 0;
    else {
        if (m_ticksSinceLastPacket++ == 1200)
            close(DisconnectPacket::eDisconnectReason::Timeout);
    }
    if ((int)(System::processTimeInMilliSecs() - m_timeInMs) > 1000) {
        if (m_packetListener->isServerPacketListener()) {
            ClientboundKeepAlivePacket* packet = new ClientboundKeepAlivePacket();
            send(std::shared_ptr<Packet>(packet));
        } else {
            ServerboundKeepAlivePacket* packet = new ServerboundKeepAlivePacket();
            send(std::shared_ptr<Packet>(packet));
        }
    }

    EnterCriticalSection(&m_incomingMutex);

    std::deque<std::shared_ptr<Packet>> queue;
    int maxIterations = 1000;

    while (!CGameNetworkManager::sInstance.IsLeavingGame()) {
        if (!CGameNetworkManager::sInstance.IsInSession())
            break;
        if (!m_incomingQueue.size())
            break;
        if (maxIterations-- < 0)
            break;

        std::shared_ptr<Packet> packet = m_incomingQueue.front();
        if (!m_byte148) {
            if (packet->getPacketId() == _ServerboundPlayerActionPacket) {
                int action = std::static_pointer_cast<ServerboundPlayerActionPacket>(packet)->getAction();

                if (action < 5 && action > 2) {
                    queue.push_front(packet);
                } else {
                    queue.push_back(packet);
                }
            } else {
                queue.push_back(packet);
            }
        }
        m_incomingQueue.pop_front();
    }
    LeaveCriticalSection(&m_incomingMutex);

    for (unsigned int i = 0; i < queue.size(); i++) {
        PIXBeginNamedEvent(0.0, "Handling packet %d\n", queue[i]->getPacketId());
        queue[i]->handle(m_packetListener);
        PIXEndNamedEvent();
    }

    flush();

    if (m_socket && m_socket->sub_71000EA668())
        close(DisconnectPacket::eDisconnectReason::Closed);
    if (m_byte148) {
        EnterCriticalSection(&m_incomingMutex);
        long incomingQueueSize = m_incomingQueue.size();
        LeaveCriticalSection(&m_incomingMutex);
        if (incomingQueueSize == 0) {
            m_packetListener->onDisconnect((DisconnectPacket::eDisconnectReason)m_dword14c, m_qword150);
            m_byte148 = false;
        }
    }
}

void Connection::sendAndQuit() {
    if (!m_isDisconnecting) {
        flush();
        m_isDisconnecting = true;
        close(DisconnectPacket::eDisconnectReason::Closed);
    }
}
