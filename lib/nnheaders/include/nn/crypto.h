/**
 * @file crypto.h
 * @brief Crypto service implementation.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace crypto {

class Sha256Context;

// dstBufferSize max size is 0x38
Result GenerateCryptographicallyRandomBytes(void* dstBuffer, u64 dstBufferSize);
bool IsSameBytes(const void* data1, const void* data2, u64 size);

// MD5 Hash
void GenerateMd5Hash(void* dstBuffer, u64 dstBufferSize, const void* srcBuffer, u64 srcBufferSize);

// SHA-1 Hash
void GenerateSha1Hash(void* dstBuffer, u64 dstBufferSize, const void* srcBuffer, u64 srcBufferSize);

// SHA-256 Hash
void GenerateSha256Hash(void* dstBuffer, u64 dstBufferSize, const void* srcBuffer,
                        u64 srcBufferSize);

// SHA-512 Hash
void GenerateSha512Hash(void* dstBuffer, u64 dstBufferSize, const void* srcBuffer,
                        u64 srcBufferSize);

// HMAC-SHA1
void GenerateHmacSha1Mac(void* dstBuffer, u64 dstBufferSize, const void* srcBuffer,
                         u64 srcBufferSize, const void* hmacKey, u64 hmacKeySize);

// HMAC-SHA256
void GenerateHmacSha256Mac(void* dstBuffer, u64 dstBufferSize, const void* srcBuffer,
                           u64 srcBufferSize, const void* hmacKey, u64 hmacKeySize);

// AES-128 CBC Decrypt - returns srcBufferSize
u64 DecryptAes128Cbc(void* dstBuffer, u64 dstBufferSize, const void* key, u64 keySize,
                     const void* iv, u64 ivSize, const void* srcBuffer, u64 srcBufferSize);

// AES-128 CBC Encrypt - returns srcBufferSize
u64 EncryptAes128Cbc(void* dstBuffer, u64 dstBufferSize, const void* key, u64 keySize,
                     const void* iv, u64 ivSize, const void* srcBuffer, u64 srcBufferSize);

// AES-128 CTR Decrypt - returns srcBufferSize
u64 DecryptAes128Ctr(void* dstBuffer, u64 dstBufferSize, const void* key, u64 keySize,
                     const void* ctr, u64 ctrSize, const void* srcBuffer, u64 srcBufferSize);

u64 DecryptAes128CtrPartial(void* dstBuffer, u64 dstBufferSize, const void* key, u64 keySize,
                            const void* ctr, u64 ctrSize, s64 partialSize, const void* srcBuffer,
                            u64 srcBufferSize);

// AES-128 CTR Encrypt - returns srcBufferSize
u64 EncryptAes128Ctr(void* dstBuffer, u64 dstBufferSize, const void* key, u64 keySize,
                     const void* ctr, u64 ctrSize, const void* srcBuffer, u64 srcBufferSize);

u64 EncryptAes128CtrPartial(void* dstBuffer, u64 dstBufferSize, const void* key, u64 keySize,
                            const void* ctr, u64 ctrSize, s64 partialSize, const void* srcBuffer,
                            u64 srcBufferSize);

// AES-192 CTR Decrypt - returns srcBufferSize
u64 DecryptAes192Ctr(void* dstBuffer, u64 dstBufferSize, const void* key, u64 keySize,
                     const void* ctr, u64 ctrSize, const void* srcBuffer, u64 srcBufferSize);

u64 DecryptAes192CtrPartial(void* dstBuffer, u64 dstBufferSize, const void* key, u64 keySize,
                            const void* ctr, u64 ctrSize, s64 partialSize__, const void* srcBuffer,
                            u64 srcBufferSize);

// AES-192 CTR Encrypt - returns srcBufferSize
u64 EncryptAes192Ctr(void* dstBuffer, u64 dstBufferSize, const void* key, u64 keySize,
                     const void* ctr, u64 ctrSize, const void* srcBuffer, u64 srcBufferSize);

u64 EncryptAes192CtrPartial(void* dstBuffer, u64 dstBufferSize, const void* key, u64 keySize,
                            const void* ctr, u64 ctrSize, s64 partialSize, const void* srcBuffer,
                            u64 srcBufferSize);

// AES-256 CTR Decrypt - returns srcBufferSize
u64 DecryptAes256Ctr(void* dstBuffer, u64 dstBufferSize, const void* key, u64 keySize,
                     const void* ctr, u64 ctrSize, const void* srcBuffer, u64 srcBufferSize);

u64 DecryptAes256CtrPartial(void* dstBuffer, u64 dstBufferSize, const void* key, u64 keySize,
                            const void* ctr, u64 ctrSize, s64 partialSize, const void* srcBuffer,
                            u64 srcBufferSize);

// AES-256 CTR Encrypt - returns srcBufferSize
u64 EncryptAes256Ctr(void* dstBuffer, u64 dstBufferSize, const void* key, u64 keySize,
                     const void* ctr, u64 ctrSize, const void* srcBuffer, u64 srcBufferSize);

u64 EncryptAes256CtrPartial(void* dstBuffer, u64 dstBufferSize, const void* key, u64 keySize,
                            const void* ctr, u64 ctrSize, s64 partialSize, const void* srcBuffer,
                            u64 srcBufferSize);

// AES-128 CCM Decrypt
u64 DecryptAes128Ccm(void*, u64, void*, u64, const void*, u64, const void*, u64, const void*, u64,
                     const void*, u64, u64);

// AES-128 CCM Encrypt
u64 EncryptAes128Ccm(void*, u64, void*, u64, const void*, u64, const void*, u64, const void*, u64,
                     const void*, u64, u64);

// AES-128 GCM Decrypt
u64 DecryptAes128Gcm(void*, u64, void*, u64, const void*, u64, const void*, u64, const void*, u64,
                     const void*, u64);

// AES-128 GCM Encrypt
u64 EncryptAes128Gcm(void*, u64, void*, u64, const void*, u64, const void*, u64, const void*, u64,
                     const void*, u64);

// AES-256 GCM Decrypt
u64 DecryptAes256Gcm(void* dstBuffer, u64 dstBufferSize, void*, u64, const void*, u64, const void*,
                     u64, const void*, u64, const void*, u64);

// AES-256 GCM Encrypt
u64 EncryptAes256Gcm(void* dstBuffer, u64 dstBufferSize, void*, u64, const void*, u64, const void*,
                     u64, const void*, u64, const void*, u64);

namespace detail {
class Md5Impl {
public:
    void Initialize();
    void Update(void const*, u64 dataSize);
    void ProcessBlock();
    void GetHash(void*, u64 hashSize);
    void ProcessLastBlock();

    u32 _x0;
    u32 _x4;
    u32 _x8;
    u32 _xC;
    u8 _x10[0x50 - 0x10];
    u64 _x50;
    u32 _x58;
};

class Sha1Impl {
public:
    void Initialize();
    void Update(void const*, u64);
    void ProcessBlock(void const*);
    void GetHash(void* destHash, u64);
    void ProcessLastBlock();

    u64 _x0;
    u64 _x8;
    u32 _x10;
    u128 _x14;
    u128 _x24;
    u128 _x34;
    u32 _x44;
    u64 _x48;
    u64 _x50;
    u64 _x58;
    u64 _x60;
};

class Sha256Impl {
public:
    void Initialize();
    void Update(void const*, u64);
    void ProcessBlocks(u8 const*, u64);
    void GetHash(void* destHash, u64);
    void ProcessLastBlock();
    void InitializeWithContext(nn::crypto::Sha256Context const*);
    void GetContext(nn::crypto::Sha256Context*) const;

    u64 _x0;
    u64 _x8;
    u32 _x10;
    u128 _x14;
    u128 _x24;
    u128 _x34;
    u32 _x44;
    u64 _x48;
    u64 _x50;
    u64 _x58;
    u64 _x60;
    u64 _x68;
    u32 _x70;
};
}  // namespace detail
}  // namespace crypto
}  // namespace nn
