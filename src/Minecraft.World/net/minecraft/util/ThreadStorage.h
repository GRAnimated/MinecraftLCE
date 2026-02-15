#pragma once

#include "NX/Platform.h"

#define DECLARE_THREAD_STORAGE(Class)                                                                        \
public:                                                                                                      \
    class ThreadStorage {                                                                                    \
    public:                                                                                                  \
        ThreadStorage();                                                                                     \
        ~ThreadStorage();                                                                                    \
        Class* m_storage;                                                                                    \
        unsigned int m_unk;                                                                                  \
    };                                                                                                       \
    static ThreadStorage* sDefaultThreadStorage;                                                             \
    static int sThreadStorageIndex;                                                                          \
    static void CreateNewThreadStorage();                                                                    \
    static void UseDefaultThreadStorage();                                                                   \
    static void ReleaseThreadStorage();

#define DEFINE_THREAD_STORAGE(Class, PoolSize)                                                               \
    Class::ThreadStorage* Class::sDefaultThreadStorage;                                                      \
    int Class::sThreadStorageIndex;                                                                          \
                                                                                                             \
    Class::ThreadStorage::ThreadStorage() {                                                                  \
        m_storage = new Class[PoolSize];                                                                     \
        m_unk = 0;                                                                                           \
    }                                                                                                        \
                                                                                                             \
    Class::ThreadStorage::~ThreadStorage() {                                                                 \
        delete[] m_storage;                                                                                  \
    }                                                                                                        \
                                                                                                             \
    void Class::CreateNewThreadStorage() {                                                                   \
        ThreadStorage* storage = new ThreadStorage();                                                        \
        if (!sDefaultThreadStorage) {                                                                        \
            sThreadStorageIndex = TlsAlloc();                                                                \
            sDefaultThreadStorage = storage;                                                                 \
        }                                                                                                    \
        TlsSetValue(sThreadStorageIndex, storage);                                                           \
    }                                                                                                        \
                                                                                                             \
    void Class::UseDefaultThreadStorage() {                                                                  \
        TlsSetValue(sThreadStorageIndex, sDefaultThreadStorage);                                             \
    }                                                                                                        \
                                                                                                             \
    void Class::ReleaseThreadStorage() {                                                                     \
        ThreadStorage* storage = (ThreadStorage*)TlsGetValue(sThreadStorageIndex);                           \
        if (storage != sDefaultThreadStorage)                                                                \
            delete storage;                                                                                  \
    }

#define DECLARE_THREAD_STORAGE_SINGLE(Class)                                                                 \
public:                                                                                                      \
    class ThreadStorage {                                                                                    \
    public:                                                                                                  \
        ThreadStorage();                                                                                     \
        ~ThreadStorage();                                                                                    \
        Class* m_storage;                                                                                    \
    };                                                                                                       \
    static ThreadStorage* sDefaultThreadStorage;                                                             \
    static int sThreadStorageIndex;                                                                          \
    static void CreateNewThreadStorage();                                                                    \
    static void UseDefaultThreadStorage();                                                                   \
    static void ReleaseThreadStorage();

#define DEFINE_THREAD_STORAGE_SINGLE(Class)                                                                  \
    Class::ThreadStorage* Class::sDefaultThreadStorage;                                                      \
    int Class::sThreadStorageIndex;                                                                          \
                                                                                                             \
    Class::ThreadStorage::ThreadStorage() {                                                                  \
        m_storage = new Class();                                                                             \
    }                                                                                                        \
                                                                                                             \
    Class::ThreadStorage::~ThreadStorage() {                                                                 \
        delete m_storage;                                                                                    \
    }                                                                                                        \
                                                                                                             \
    void Class::CreateNewThreadStorage() {                                                                   \
        ThreadStorage* storage = new ThreadStorage();                                                        \
        if (!sDefaultThreadStorage) {                                                                        \
            sThreadStorageIndex = TlsAlloc();                                                                \
            sDefaultThreadStorage = storage;                                                                 \
        }                                                                                                    \
        TlsSetValue(sThreadStorageIndex, storage);                                                           \
    }                                                                                                        \
                                                                                                             \
    void Class::UseDefaultThreadStorage() {                                                                  \
        TlsSetValue(sThreadStorageIndex, sDefaultThreadStorage);                                             \
    }                                                                                                        \
                                                                                                             \
    void Class::ReleaseThreadStorage() {                                                                     \
        ThreadStorage* storage = (ThreadStorage*)TlsGetValue(sThreadStorageIndex);                           \
        if (storage != sDefaultThreadStorage)                                                                \
            delete storage;                                                                                  \
    }

#define START_DECLARE_THREAD_STORAGE()                                                                       \
public:                                                                                                      \
    class ThreadStorage {                                                                                    \
    public:                                                                                                  \
        ThreadStorage();                                                                                     \
        ~ThreadStorage();

#define END_DECLARE_THREAD_STORAGE()                                                                         \
    }                                                                                                        \
    ;                                                                                                        \
    static ThreadStorage* sDefaultThreadStorage;                                                             \
    static int sThreadStorageIndex;                                                                          \
    static void CreateNewThreadStorage();                                                                    \
    static void UseDefaultThreadStorage();                                                                   \
    static void ReleaseThreadStorage();
