#include <nvnTool/nvnTool_GlslcInterface.h>

bool glslcCompile(GLSLCcompileObject*);
const GLSLCoutput* const* glslcCompilePreSpecialized(GLSLCcompileObject*,
                                                     const GLSLCspecializationBatch*);
uint8_t glslcCompileSpecialized(GLSLCcompileObject*);
void glslcFinalize(GLSLCcompileObject*);
uint8_t glslcGetDefaultOptions(GLSLCcompileObject*);
GLSLCversion glslcGetVersion();
void glslcInitialize(GLSLCallocateFunction, GLSLCfreeFunction, GLSLCreallocateFunction, void*);
GLSLCoptions glslcSetAllocator();

namespace nn::gfx::detail {
typedef bool (*GlslcCompilePreSpecializedType)(GLSLCcompileObject*);
typedef const GLSLCoutput* const* (*GlslcCompileSpecializedType)(GLSLCcompileObject*,
                                                                 const GLSLCspecializationBatch*);
typedef uint8_t (*GlslcInitializeType)(GLSLCcompileObject*);
typedef void (*GlslcFinalizeType)(GLSLCcompileObject*);
typedef uint8_t (*GlslcCompileType)(GLSLCcompileObject*);
typedef GLSLCversion (*GlslcGetVersionType)();
typedef void (*GlslcSetAllocatorType)(GLSLCallocateFunction, GLSLCfreeFunction,
                                      GLSLCreallocateFunction, void*);
typedef GLSLCoptions (*GlslcGetDefaultOptionsType)();

GlslcCompilePreSpecializedType GetGlslcCompilePreSpecializedFunction() {
    return glslcCompile;
}

GlslcCompileSpecializedType GetGlslcCompileSpecializedFunction() {
    return glslcCompilePreSpecialized;
}

GlslcInitializeType GetGlslcInitializeFunction() {
    return glslcCompileSpecialized;
}

GlslcFinalizeType GetGlslcFinalizeFunction() {
    return glslcFinalize;
}

GlslcCompileType GetGlslcCompileFunction() {
    return glslcGetDefaultOptions;
}

GlslcGetVersionType GetGlslcGetVersionFunction() {
    return glslcGetVersion;
}

GlslcSetAllocatorType GetGlslcSetAllocatorFunction() {
    return glslcInitialize;
}

GlslcGetDefaultOptionsType GetGlslcGetDefaultOptionsFunction() {
    return glslcSetAllocator;
}

}  // namespace nn::gfx::detail