/**
 * @file ro.h
 * @brief Dynamic module API.
 */

#pragma once

#include <elf.h>
#include <nn/types.h>
#include <nn/util/util_BinTypes.h>

namespace nn {
namespace ro {

namespace detail {
class RoModule {
public:
    RoModule* next;
    RoModule* prev;
    union {
        Elf64_Rel* rel_plt;
        Elf64_Rela* rela_plt;
        void* rel_rela_plt;
    };
    union {
        Elf64_Rel* rel;
        Elf64_Rela* rela;
        void* rel_rela;
    };
    u8* moduleBaseAddr;
    Elf64_Dyn* dynamic;
    bool is_rela;
    u8 pad_x31[7];
    Elf64_Xword plt_size;
    void (*initFunc)();
    void (*finiFunc)();
    Elf64_Word* hashBucket;
    Elf64_Word* hashChain;
    char* dynstrTable;
    Elf64_Sym* dynsymTable;
    Elf64_Xword dynstrTable_size;
    void** got_plt;
    Elf64_Xword rela_dyn_size;
    Elf64_Xword rel_dyn_size;
    Elf64_Xword relEnt_count;
    Elf64_Xword relaEnt_count;
    Elf64_Xword nchain;
    Elf64_Xword nbucket;
    Elf64_Xword off_soname;
    u64 unk_xb8;
    bool unk_xc0;
    u8 pad_xc1[7];
    Elf64_Xword ArchitectureData;

    void Initialize(u8* moduleBaseAddr, u64 arg1_0, Elf64_Dyn* dynamic, bool arg4_0);
    Elf64_Sym* Lookup(const char* symbol);
    void Relocation(bool lazyGotPlt);
    void CallInit();
    void CallFini();
    bool ResolveSym(Elf64_Addr* symbolAddr, Elf64_Sym* symbol);
};

static_assert(sizeof(RoModule) == 0xD0, "RoModule definition!");
}  // namespace detail

class Module {
public:
    detail::RoModule* ModuleObject;
    u32 State;
    void* NroPtr;
    void* BssPtr;
    void* _x20;
    void* SourceBuffer;
    char Name[256]; /* Created by retype action */
    u8 _x130;
    u8 _x131;
    bool isLoaded;  // bool
};

struct ModuleId {
    u8 build_id[0x20];
};

struct NroHeader {
    static constexpr u32 NroMagic = util::MakeSignature('N', 'R', 'O', '0');

    u32 entrypoint_insn;
    u32 mod_offset;
    u8 _x8[0x8];
    u32 magic;
    u8 _x14[0x4];
    u32 size;
    u8 _x1c[0x4];
    u32 text_offset;
    u32 text_size;
    u32 ro_offset;
    u32 ro_size;
    u32 rw_offset;
    u32 rw_size;
    u32 bss_size;
    u8 _x3c[0x4];
    ModuleId module_id;
    u8 _x60[0x20];
};
static_assert(sizeof(NroHeader) == 0x80, "NroHeader definition!");

struct ProgramId {
    u64 value;

    inline explicit operator u64() const { return this->value; }
};

struct NrrCertification {
    u64 programID_Mask;
    u64 programID_Pattern;
    u8 reserved_x10[0x10];

    u8 modulus[0x100];
    u8 signature[0x100];
};
static_assert(sizeof(NrrCertification) == 0x220, "NrrCertification definition!");

enum NrrKind : u8 {
    NrrKind_User = 0,
    NrrKind_JitPlugin = 1,
    NrrKind_Count,
};

struct NrrHeader {
    static constexpr u32 NrrMagic = util::MakeSignature('N', 'R', 'R', '0');

    u32 magic;
    u8 _x4[0xC];
    NrrCertification certiicate;
    u8 nrr_signature[0x100];
    ProgramId program_id;
    u32 size;
    NrrKind type; /* 7.0.0+ */
    u8 _x33d[3];
    u32 hashes_offset;
    u32 num_hashes;
    u8 _x348[8];
};
static_assert(sizeof(NrrHeader) == 0x350, "NrrHeader definition!");

struct RegistrationInfo {
    enum State {
        State_Unregistered,
        State_Registered,
    };
    State state;
    NrrHeader* nrrPtr;
    u64 _x10;
    u64 _x18;
};

enum BindFlag {
    BindFlag_Now = 1,
    BindFlag_Lazy = 2,
};

Result Initialize();
Result InitializeWithPortName(const char* portname);  // "ldr:ro" or "ro:1"
Result Finalize();

Result GetBufferSize(u64* size, const void* nro);  // Gets Bss size from nro+0x38

Result RegisterModuleInfo(nn::ro::RegistrationInfo* regInfo, const void* nrr);
Result RegisterModuleInfo(nn::ro::RegistrationInfo* regInfo, const void* nrr, u32);
Result UnregisterModuleInfo(nn::ro::RegistrationInfo* regInfo);

Result LoadModule(Module* outModule, const void* nro, void* nroBss, u64 nroBssSize, s32 flags);
Result LoadModule(Module* outModule, const void* nro, void* nroBss, u64 nroBssSize, s32 flags,
                  bool);
Result UnloadModule(Module* module);

Result LookupSymbol(u64* funcAddress, const char* symbolName);
Result LookupModuleSymbol(u64* funcAddress, const Module* module, const char* symbolName);
}  // namespace ro

}  // namespace nn
