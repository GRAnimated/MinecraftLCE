#pragma once

#include <nn/os/os_MutexTypes.h>
#include <nn/util.h>

namespace nn::os {

// todo: figure out where these go
void InitializeMutex(MutexType*, bool, s32);
void FinalizeMutex(MutexType*);
void LockMutex(MutexType*);
bool TryLockMutex(MutexType*);
void UnlockMutex(MutexType*);
bool IsMutexLockedByCurrentThread(const MutexType*);

class Mutex {
    NN_NO_COPY(Mutex);
    NN_NO_MOVE(Mutex);

public:
    explicit Mutex(bool recursive) { InitializeMutex(&m_Mutex, recursive, 0); }

    Mutex(bool, int);
    ~Mutex();

    void Lock() { LockMutex(&m_Mutex); }

    bool TryLock();
    void Unlock() { UnlockMutex(&m_Mutex); }
    bool IsLockedByCurrentThread() const;
    void lock();
    bool try_lock();
    void unlock();
    operator MutexType&();
    operator const MutexType&() const;
    MutexType* GetBase();

private:
    MutexType m_Mutex;
};

}  // namespace nn::os