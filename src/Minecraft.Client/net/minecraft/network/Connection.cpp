#include "Minecraft.Network/Connection.h"

#include "Minecraft.Client/C4JEventImpl.h"
#include "Minecraft.Client/C4JThreadImpl.h"
#include "Minecraft.Client/CGameNetworkManager.h"
#include "Minecraft.Client/Compression.h"
#include "Minecraft.Client/ShutdownManager.h"
#include "Minecraft.Client/platform/NX/Platform.h"
#include "Minecraft.Core/System.h"
#include "Minecraft.Core/io/BufferedOutputStream.h"
#include "Minecraft.Core/io/ByteArrayOutputStream.h"
#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Core/io/File.h"
#include "Minecraft.Network/PacketListener.h"
#include "Minecraft.Network/PacketType.h"
#include "Minecraft.Network/Socket.h"
#include "Minecraft.Network/protocol/game/ServerboundPlayerActionPacket.h"
#include "nn/os/os_Mutex.h"
#include "protocol/game/ClientboundKeepAlivePacket.h"
#include "protocol/game/ServerboundKeepAlivePacket.h"
#include <cstdio>
#include <memory>

bool Connection::getAndSetRunning(bool running) {
    EnterCriticalSection(&mIsRunningMutex);
    bool prevIsRunning = mIsRunning;
    mIsRunning = running;
    LeaveCriticalSection(&mIsRunningMutex);
    return prevIsRunning;
}

void Connection::_init() {
    InitializeCriticalSection(&mOutgoingMutex);
    InitializeCriticalSection(&mCountMutex);
    InitializeCriticalSection(&mIncomingMutex);
    mIsRunning = true;
    InitializeCriticalSection(&mIsRunningMutex);
    mIsDisconnecting = false;
    field_119 = false;
    byte_148 = false;
    dword_14c = 0;
    mFakeLag = 0;
    mDelay = 50;
    qword_140 = nullptr;
    field_158 = 0;
    mEstimatedSize = 0;
    field_160 = 0;
    field_164 = 0;
}

Connection::~Connection() {
    mIsRunning = false;

    nn::os::FinalizeMutex(&mIsRunningMutex);

    if (mDataInputStream)
        mDataInputStream->close();
    mRunReadThread->WaitForCompletion(0xFFFFFFFF);
    mRunWriteThread->WaitForCompletion(0xFFFFFFFF);

    nn::os::FinalizeMutex(&mOutgoingMutex);
    nn::os::FinalizeMutex(&mCountMutex);
    nn::os::FinalizeMutex(&mIncomingMutex);

    delete mC4JEventImpl1;
    delete mC4JEventImpl2;

    delete mDataOutputStream2;
    mDataOutputStream2 = nullptr;

    delete mByteArrayOutputStream;
    mByteArrayOutputStream = nullptr;

    if (mDataOutputStream) {
        mDataOutputStream->deleteChildStream();
        delete mDataOutputStream;
        mDataOutputStream = nullptr;
    }

    delete mDataInputStream;
    mDataInputStream = nullptr;

    delete mRunReadThread;
    mRunReadThread = nullptr;

    delete mRunWriteThread;
    mRunWriteThread = nullptr;
}

static char filename[0x100] = {};

Connection::Connection(Socket* socket, const std::wstring& type, PacketListener* packetListener)
    : mIncomingQueue(std::deque<std::shared_ptr<Packet>>()),
      mOutgoingQueue(std::deque<std::shared_ptr<Packet>>()),
      mSlowOutgoingQueue(std::deque<std::shared_ptr<Packet>>()) {
    _init();
    mSocket = socket;
    mRemoteSocketAddress = socket->getRemoteSocketAddress();
    mPacketListener = packetListener;

    socket->setSoTimeout(30000);
    socket->setTrafficClass(24);

    mDataInputStream = new DataInputStream(socket->getInputStream(packetListener->isServerPacketListener()));

    mSocketOutputStream = socket->getOutputStream(packetListener->isServerPacketListener());
    mDataOutputStream = new DataOutputStream(new BufferedOutputStream(mSocketOutputStream, 0x1400));

    mByteArrayOutputStream = new ByteArrayOutputStream(0x1400);
    mDataOutputStream2 = new DataOutputStream(mByteArrayOutputStream);

    mC4JEventImpl1 = new C4JEventImpl(C4JEvent::EMode::_0);
    mC4JEventImpl2 = new C4JEventImpl(C4JEvent::EMode::_0);

    const char* name = wstringtofilename(type, filename);

    char readName[0x100];
    char writeName[0x100];
    sprintf(readName, "%s read\n", name);
    sprintf(writeName, "%s write\n", name);

    mRunReadThread = new C4JThreadImpl(Connection::runRead, this, readName, 0);
    mRunWriteThread = new C4JThreadImpl(Connection::runWrite, this, writeName, 0);

    mRunReadThread->SetProcessor(2);
    mRunWriteThread->SetProcessor(2);
    mRunReadThread->Run();
    mRunWriteThread->Run();

    mTimeInMs = 0;
}

int Connection::runRead(void* conn) {
    Connection* connection = (Connection*)conn;
    ShutdownManager::HasStarted(ShutdownManager::EThreadId::_8);
    if (connection) {
        Compression::CreateNewThreadStorage();
        EnterCriticalSection(&connection->mCountMutex);
        ++dword_7101786598;
        LeaveCriticalSection(&connection->mCountMutex);
        MemSect(19);
        while (connection->mIsRunning) {
            if (connection->mIsDisconnecting || !ShutdownManager::ShouldRun(ShutdownManager::EThreadId::_8))
                break;
            while (connection->readTick() != 0)
                ;
            connection->mC4JEventImpl1->WaitForSignal(100);
        }
        MemSect(0);
        Compression::ReleaseThreadStorage();
        ShutdownManager::HasFinished(ShutdownManager::EThreadId::_8);
        return 0;
    }
    return 0;
}

// NON_MATCHING
int Connection::runWrite(void* conn) {
    Connection* connection = (Connection*)conn;
    ShutdownManager::HasStarted(ShutdownManager::EThreadId::_9);
    if (connection) {
        Compression::CreateNewThreadStorage();

        EnterCriticalSection(&connection->mCountMutex);
        ++dword_710178659C;
        LeaveCriticalSection(&connection->mCountMutex);

        if (connection->mIsRunning) {
            int writeStatus;
            while ((connection->mIsRunning || !writeStatus)
                   && ShutdownManager::ShouldRun(ShutdownManager::EThreadId::_9)) {
                long long startTime = System::processTimeInMilliSecs();

                bool writeSuccess = false;
                long long currentTime = startTime;

                do {
                    writeSuccess = connection->writeTick();
                    currentTime = System::processTimeInMilliSecs();
                } while (connection->mDataOutputStream->getSize() != 0x7FFFFFFF && writeSuccess
                         && (currentTime - startTime) < 200);

                writeStatus = connection->mC4JEventImpl2->WaitForSignal(100);

                if (connection->mDataOutputStream)
                    connection->mDataOutputStream->flush();
            }
        }

        EnterCriticalSection(&connection->mCountMutex);
        --dword_710178659C;
        LeaveCriticalSection(&connection->mCountMutex);

        Compression::ReleaseThreadStorage();
    }

    ShutdownManager::HasFinished(ShutdownManager::EThreadId::_9);
    return 0;
}

void Connection::setListener(PacketListener* listener) {
    mPacketListener = listener;
}

void Connection::send(std::shared_ptr<Packet> packet) {
    if (!mIsDisconnecting) {
        mTimeInMs = System::processTimeInMilliSecs();
        MemSect(15);
        EnterCriticalSection(&mOutgoingMutex);
        mEstimatedSize += packet->getEstimatedSize() + 1;
        if (packet->mShouldDelay) {
            packet->mShouldDelay = false;
            mSlowOutgoingQueue.push_back(packet);
        } else {
            if (packet->getPacketId() == _ClientboundMapItemDataPacket)
                if (packet->tryReplaceDuplicatePacket(&mOutgoingQueue)) {
                    // TODO: Remove early return
                    LeaveCriticalSection(&mOutgoingMutex);
                    MemSect(0);
                    return;
                }

            mOutgoingQueue.push_back(packet);
        }
        LeaveCriticalSection(&mOutgoingMutex);
        MemSect(0);
    }
}

void Connection::queueSend(std::shared_ptr<Packet> packet) {
    if (!mIsDisconnecting) {
        EnterCriticalSection(&mOutgoingMutex);
        mEstimatedSize += packet->getEstimatedSize() + 1;
        mSlowOutgoingQueue.push_back(packet);
        LeaveCriticalSection(&mOutgoingMutex);
    }
}

// NON_MATCHING: Shared pointer stuff
bool Connection::writeTick() {
    if (!mDataOutputStream || !mDataOutputStream2)
        return false;

    bool returnValue;
    if (!mOutgoingQueue.empty()
        && (!mFakeLag
            || (System::processTimeInMilliSecs() - mOutgoingQueue.front()->mCreatedTime >= mFakeLag))) {
        std::shared_ptr<Packet> packet;
        EnterCriticalSection(&mOutgoingMutex);

        packet = mOutgoingQueue.front();
        mOutgoingQueue.pop_front();

        mEstimatedSize -= packet->getEstimatedSize() + 1;
        LeaveCriticalSection(&mOutgoingMutex);

        Packet::writePacket(packet, mDataOutputStream, mPacketListener->isServerPacketListener(), field_164);

        dword_71017869A0[packet->getPacketId()] += packet->getEstimatedSize() + 1;

        returnValue = true;
    } else {
        returnValue = false;
    }

    if (mDelay-- > 0 || mSlowOutgoingQueue.empty()
        || (mFakeLag
            && System::processTimeInMilliSecs() - mSlowOutgoingQueue.front()->mCreatedTime < mFakeLag)) {
        return returnValue;
    }

    EnterCriticalSection(&mOutgoingMutex);
    std::shared_ptr<Packet> packet = mSlowOutgoingQueue.front();
    mSlowOutgoingQueue.pop_front();

    mEstimatedSize += ~packet->getEstimatedSize();
    LeaveCriticalSection(&mOutgoingMutex);

    if (packet->mShouldDelay) {
        Packet::writePacket(packet, mDataOutputStream2, mPacketListener->isServerPacketListener(), field_164);

        if (mDataOutputStream)
            mDataOutputStream->flush();
        mSocketOutputStream->writeWithFlags(mByteArrayOutputStream->mBuffer, 0,
                                            mByteArrayOutputStream->size(), 1);
        mByteArrayOutputStream->clear();
    } else {
        Packet::writePacket(packet, mDataOutputStream, mPacketListener->isServerPacketListener(), field_164);
    }

    dword_71017869A0[packet->getPacketId()] += packet->getEstimatedSize() + 1;

    mDelay = 0;
    return true;
}

void Connection::flush() {
    mC4JEventImpl1->Set();
    mC4JEventImpl2->Set();
}

bool Connection::readTick() {
    if (mDataInputStream && !field_119) {
        std::shared_ptr<Packet> packet = Packet::readPacket(
            mDataInputStream, mPacketListener->isServerPacketListener(), field_160, field_119);
        if (packet) {
            dword_71017865A0[packet->getPacketId()] += packet->getEstimatedSize() + 1;
            EnterCriticalSection(&mIncomingMutex);
            if (!mIsDisconnecting)
                mIncomingQueue.push_back(packet);
            LeaveCriticalSection(&mIncomingMutex);
            return true;
        }
        return false;
    }
    return false;
}

void Connection::close(DisconnectPacket::eDisconnectReason reason) {
    if (!getAndSetRunning(false))
        return;
    byte_148 = true;
    dword_14c = reason;
    qword_150 = nullptr;

    if (mDataInputStream)
        mDataInputStream->close();

    mRunReadThread->WaitForCompletion(0xFFFFFFFF);
    mRunWriteThread->WaitForCompletion(0xFFFFFFFF);

    delete mDataInputStream;
    mDataInputStream = nullptr;

    if (mDataOutputStream) {
        mDataOutputStream->close();
        mDataOutputStream->deleteChildStream();
        delete mDataOutputStream;
        mDataOutputStream = nullptr;
    }

    if (mDataOutputStream2) {
        mDataOutputStream2->close();
        delete mDataOutputStream2;
        mDataOutputStream2 = nullptr;
    }

    if (mSocket) {
        mSocket->close(mPacketListener->isServerPacketListener());
        mSocket = nullptr;
    }
}

// NON_MATCHING
void Connection::tick() {
    if (field_119)
        close(DisconnectPacket::eDisconnectReason::_29);
    if (mEstimatedSize > 0x100000)  // 1MB
        close(DisconnectPacket::eDisconnectReason::Overflow);
    EnterCriticalSection(&mIncomingMutex);
    long test = (reinterpret_cast<long*>(&mIncomingQueue)[5]);
    LeaveCriticalSection(&mIncomingMutex);
    if (test)
        field_158 = 0;
    else {
        field_158++;
        if (field_158 == 1200)
            close(DisconnectPacket::eDisconnectReason::Timeout);
    }
    if (System::processTimeInNanoSecs() - mTimeInMs > 1000) {
        if (mPacketListener->isServerPacketListener()) {
            ClientboundKeepAlivePacket* packet = new ClientboundKeepAlivePacket();
            send(std::shared_ptr<Packet>(packet));
        } else {
            ServerboundKeepAlivePacket* packet = new ServerboundKeepAlivePacket();
            send(std::shared_ptr<Packet>(packet));
        }
    }
    EnterCriticalSection(&mIncomingMutex);
    std::deque<std::shared_ptr<Packet>> queue;
    int maxIterations = 1000;
    CGameNetworkManager inst = CGameNetworkManager::sInstance;
    while (!inst.IsLeavingGame()) {
        if (!inst.IsInSession())
            break;
        if (mIncomingQueue.size() == 0)
            break;
        if (maxIterations-- < 0)
            break;

        std::shared_ptr<Packet> packet = mIncomingQueue.front();
        if (!byte_148) {
            if (packet->getPacketId() == _ServerboundPlayerActionPacket) {
                auto actionPacket = std::shared_ptr<Packet>(packet);
                int action = static_cast<ServerboundPlayerActionPacket*>(actionPacket.get())->getAction();

                if (action > 2 && action < 5) {
                    queue.push_front(actionPacket);
                } else {
                    queue.push_back(packet);
                }
            } else {
                queue.push_back(packet);
            }
        }
        mIncomingQueue.pop_front();
    }
    LeaveCriticalSection(&mIncomingMutex);

    for (auto it = queue.begin(); it != queue.end(); ++it) {
        std::shared_ptr<Packet> packet = *it;
        PIXBeginNamedEvent(0.0, "Handling packet %d\n", packet->getPacketId());
        packet->handle(mPacketListener);
        PIXEndNamedEvent();
    }

    flush();

    if (mSocket && mSocket->sub_71000EA668())
        close(DisconnectPacket::eDisconnectReason::Closed);
    if (byte_148) {
        EnterCriticalSection(&mIncomingMutex);
        long test = (reinterpret_cast<long*>(&mIncomingQueue)[5]);
        LeaveCriticalSection(&mIncomingMutex);
        if (!test)
            mPacketListener->onDisconnect((DisconnectPacket::eDisconnectReason)dword_14c, qword_150);
        byte_148 = false;
    }
}

void Connection::sendAndQuit() {
    if (!mIsDisconnecting) {
        flush();
        mIsDisconnecting = true;
        close(DisconnectPacket::eDisconnectReason::Closed);
    }
}
