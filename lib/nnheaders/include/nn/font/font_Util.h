#pragma once

namespace nn::font::detail {

class RuntimeTypeInfo {
public:
    const RuntimeTypeInfo* m_ParentTypeInfo;

    explicit RuntimeTypeInfo(const RuntimeTypeInfo* parent) : m_ParentTypeInfo(parent) {}
    bool IsDerivedFrom(const RuntimeTypeInfo*) const;
};

}  // namespace nn::font::detail

// todo: figure out where to put this
#define NN_RUNTIME_TYPEINFO_BASE()                                                                 \
    static const nn::font::detail::RuntimeTypeInfo* GetRuntimeTypeInfoStatic() {                   \
        static const nn::font::detail::RuntimeTypeInfo s_TypeInfo(nullptr);                        \
        return &s_TypeInfo;                                                                        \
    }                                                                                              \
                                                                                                   \
    virtual const nn::font::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const {                  \
        return GetRuntimeTypeInfoStatic();                                                         \
    }

#define NN_RUNTIME_TYPEINFO(BASE)                                                                  \
    static const nn::font::detail::RuntimeTypeInfo* GetRuntimeTypeInfoStatic() {                   \
        static const nn::font::detail::RuntimeTypeInfo s_TypeInfo(                                 \
            BASE::GetRuntimeTypeInfoStatic());                                                     \
        return &s_TypeInfo;                                                                        \
    }                                                                                              \
                                                                                                   \
    virtual const nn::font::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const {                  \
        return GetRuntimeTypeInfoStatic();                                                         \
    }
