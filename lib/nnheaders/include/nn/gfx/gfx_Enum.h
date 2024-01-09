#pragma once

namespace nn::gfx {

namespace detail {

enum FilterModeBit {
    FilterModeBit_Point = 1,
    FilterModeBit_Linear = 2,
    FilterModeBit_MinFilterShift = 4,
    FilterModeBit_MagFilterShift = 2,
    FilterModeBit_MipFilterShift = 0,
    FilterModeBit_MinPoint = FilterModeBit_Point << FilterModeBit_MinFilterShift,
    FilterModeBit_MinLinear = FilterModeBit_Linear << FilterModeBit_MinFilterShift,
    FilterModeBit_MagPoint = FilterModeBit_Point << FilterModeBit_MagFilterShift,
    FilterModeBit_MagLinear = FilterModeBit_Linear << FilterModeBit_MagFilterShift,
    FilterModeBit_MipPoint = FilterModeBit_Point << FilterModeBit_MipFilterShift,
    FilterModeBit_MipLinear = FilterModeBit_Linear << FilterModeBit_MipFilterShift,
    FilterModeBit_MinFilterMask = 3 << FilterModeBit_MinFilterShift,
    FilterModeBit_MagFilterMask = 3 << FilterModeBit_MagFilterShift,
    FilterModeBit_MipFilterMask = 3 << FilterModeBit_MipFilterShift,
    FilterModeBit_Anisotropic = 0x40,
    FilterModeBit_Comparison = 0x80,
    FilterModeBit_Minimum = 0x100,
    FilterModeBit_Maximum = 0x200
};

}  // namespace detail

enum LogicOperation {
    LogicOperation_Clear,
    LogicOperation_And,
    LogicOperation_AndReverse,
    LogicOperation_Copy,
    LogicOperation_AndInverted,
    LogicOperation_NoOp,
    LogicOperation_Xor,
    LogicOperation_Or,
    LogicOperation_Nor,
    LogicOperation_Equiv,
    LogicOperation_Invert,
    LogicOperation_OrReverse,
    LogicOperation_CopyInverted,
    LogicOperation_OrInverted,
    LogicOperation_Nand,
    LogicOperation_Set,
    LogicOperation_End
};

enum BlendFunction {
    BlendFunction_Add,
    BlendFunction_Subtract,
    BlendFunction_ReverseSubtract,
    BlendFunction_Min,
    BlendFunction_Max,
    BlendFunction_End
};

enum BlendFactor {
    BlendFactor_Zero,
    BlendFactor_One,
    BlendFactor_SourceColor,
    BlendFactor_OneMinusSourceColor,
    BlendFactor_DestinationColor,
    BlendFactor_OneMinusDestinationColor,
    BlendFactor_SourceAlpha,
    BlendFactor_OneMinusSourceAlpha,
    BlendFactor_DestinationAlpha,
    BlendFactor_OneMinusDestinationAlpha,
    BlendFactor_ConstantColor,
    BlendFactor_OneMinusConstantColor,
    BlendFactor_ConstantAlpha,
    BlendFactor_OneMinusConstantAlpha,
    BlendFactor_SourceAlphaSaturate,
    BlendFactor_Source1Color,
    BlendFactor_OneMinusSource1Color,
    BlendFactor_Source1Alpha,
    BlendFactor_OneMinusSource1Alpha,
    BlendFactor_End
};

enum StencilOperation {
    StencilOperation_Keep,
    StencilOperation_Zero,
    StencilOperation_Replace,
    StencilOperation_IncrementClamp,
    StencilOperation_DecrementClamp,
    StencilOperation_Invert,
    StencilOperation_IncrementWrap,
    StencilOperation_DecrementWrap,
    StencilOperation_End
};

enum ChannelMask {
    ChannelMask_Red = 1,
    ChannelMask_Green = 2,
    ChannelMask_Blue = 4,
    ChannelMask_Alpha = 8,
    ChannelMask_All = 15
};

enum PrimitiveTopology {
    PrimitiveTopology_PointList,
    PrimitiveTopology_LineList,
    PrimitiveTopology_LineStrip,
    PrimitiveTopology_TriangleList,
    PrimitiveTopology_TriangleStrip,
    PrimitiveTopology_LineListAdjacency,
    PrimitiveTopology_LineStripAdjacency,
    PrimitiveTopology_TriangleListAdjacency,
    PrimitiveTopology_TriangleStripAdjacency,
    PrimitiveTopology_PatchList,
    PrimitiveTopology_End
};

enum PrimitiveTopologyType {
    PrimitiveTopologyType_Undefined,
    PrimitiveTopologyType_Point,
    PrimitiveTopologyType_Line,
    PrimitiveTopologyType_Triangle,
    PrimitiveTopologyType_Patch,
    PrimitiveTopologyType_End
};

enum ConservativeRasterizationMode {
    ConservativeRasterizationMode_Disable,
    ConservativeRasterizationMode_Enable,
    ConservativeRasterizationMode_End
};

enum IndexFormat { IndexFormat_Uint8, IndexFormat_Uint16, IndexFormat_Uint32, IndexFormat_End };

enum FillMode { FillMode_Wireframe = 1, FillMode_Solid, FillMode_End };

enum CullMode { CullMode_None, CullMode_Front, CullMode_Back, CullMode_End };

enum FrontFace { FrontFace_Ccw, FrontFace_Cw, FrontFace_End };

enum TextureAddressMode {
    TextureAddressMode_Repeat,
    TextureAddressMode_Mirror,
    TextureAddressMode_ClampToEdge,
    TextureAddressMode_ClampToBorder,
    TextureAddressMode_MirrorClampToEdge,
    TextureAddressMode_End
};

// todo: is this using detail::FilterModeBit?
enum FilterMode {
    FilterMode_MinPoint_MagPoint_MipPoint = 21,
    FilterMode_MinPoint_MagPoint_MipLinear,
    FilterMode_MinPoint_MagLinear_MipPoint = 25,
    FilterMode_MinPoint_MagLinear_MipLinear,
    FilterMode_MinLinear_MagPoint_MipPoint = 37,
    FilterMode_MinLinear_MagPoint_MipLinear,
    FilterMode_MinLinear_MagLinear_MipPoint = 41,
    FilterMode_MinLinear_MagLinear_MipLinear,
    FilterMode_Anisotropic = 106,
    FilterMode_Comparison_MinPoint_MagPoint_MipPoint = 149,
    FilterMode_Comparison_MinPoint_MagPoint_MipLinear,
    FilterMode_Comparison_MinPoint_MagLinear_MipPoint = 153,
    FilterMode_Comparison_MinPoint_MagLinear_MipLinear,
    FilterMode_Comparison_MinLinear_MagPoint_MipPoint = 165,
    FilterMode_Comparison_MinLinear_MagPoint_MipLinear,
    FilterMode_Comparison_MinLinear_MagLinear_MipPoint = 169,
    FilterMode_Comparison_MinLinear_MagLinear_MipLinear,
    FilterMode_Comparison_Anisotropic = 234,
    FilterMode_Minimum_MinPoint_MagPoint_MipPoint = 277,
    FilterMode_Minimum_MinPoint_MagPoint_MipLinear,
    FilterMode_Minimum_MinPoint_MagLinear_MipPoint = 281,
    FilterMode_Minimum_MinPoint_MagLinear_MipLinear,
    FilterMode_Minimum_MinLinear_MagPoint_MipPoint = 293,
    FilterMode_Minimum_MinLinear_MagPoint_MipLinear,
    FilterMode_Minimum_MinLinear_MagLinear_MipPoint = 297,
    FilterMode_Minimum_MinLinear_MagLinear_MipLinear,
    FilterMode_Minimum_Anisotropic = 362,
    FilterMode_Maximum_MinPoint_MagPoint_MipPoint = 533,
    FilterMode_Maximum_MinPoint_MagPoint_MipLinear,
    FilterMode_Maximum_MinPoint_MagLinear_MipPoint = 537,
    FilterMode_Maximum_MinPoint_MagLinear_MipLinear,
    FilterMode_Maximum_MinLinear_MagPoint_MipPoint = 549,
    FilterMode_Maximum_MinLinear_MagPoint_MipLinear,
    FilterMode_Maximum_MinLinear_MagLinear_MipPoint = 553,
    FilterMode_Maximum_MinLinear_MagLinear_MipLinear,
    FilterMode_Maximum_Anisotropic = 618
};

enum ComparisonFunction {
    ComparisonFunction_Never,
    ComparisonFunction_Less,
    ComparisonFunction_Equal,
    ComparisonFunction_LessEqual,
    ComparisonFunction_Greater,
    ComparisonFunction_NotEqual,
    ComparisonFunction_GreaterEqual,
    ComparisonFunction_Always,
    ComparisonFunction_End
};

enum TextureBorderColorType {
    TextureBorderColorType_White,
    TextureBorderColorType_TransparentBlack,
    TextureBorderColorType_OpaqueBlack,
    TextureBorderColorType_End
};

enum ImageStorageDimension {
    ImageStorageDimension_Undefined,
    ImageStorageDimension_1d,
    ImageStorageDimension_2d,
    ImageStorageDimension_3d
};

enum ImageDimension {
    ImageDimension_1d,
    ImageDimension_2d,
    ImageDimension_3d,
    ImageDimension_CubeMap,
    ImageDimension_1dArray,
    ImageDimension_2dArray,
    ImageDimension_2dMultisample,
    ImageDimension_2dMultisampleArray,
    ImageDimension_CubeMapArray,
    ImageDimension_End
};

enum ChannelFormat {
    ChannelFormat_Undefined,
    ChannelFormat_R4_G4,
    ChannelFormat_R8,
    ChannelFormat_R4_G4_B4_A4,
    ChannelFormat_A4_B4_G4_R4,
    ChannelFormat_R5_G5_B5_A1,
    ChannelFormat_A1_B5_G5_R5,
    ChannelFormat_R5_G6_B5,
    ChannelFormat_B5_G6_R5,
    ChannelFormat_R8_G8,
    ChannelFormat_R16,
    ChannelFormat_R8_G8_B8_A8,
    ChannelFormat_B8_G8_R8_A8,
    ChannelFormat_R9_G9_B9_E5,
    ChannelFormat_R10_G10_B10_A2,
    ChannelFormat_R11_G11_B10,
    ChannelFormat_B10_G11_R11,
    ChannelFormat_R10_G11_B11,
    ChannelFormat_R16_G16,
    ChannelFormat_R24_G8,
    ChannelFormat_R32,
    ChannelFormat_R16_G16_B16_A16,
    ChannelFormat_R32_G8_X24,
    ChannelFormat_R32_G32,
    ChannelFormat_R32_G32_B32,
    ChannelFormat_R32_G32_B32_A32,
    ChannelFormat_Bc1,
    ChannelFormat_Bc2,
    ChannelFormat_Bc3,
    ChannelFormat_Bc4,
    ChannelFormat_Bc5,
    ChannelFormat_Bc6,
    ChannelFormat_Bc7,
    ChannelFormat_Eac_R11,
    ChannelFormat_Eac_R11_G11,
    ChannelFormat_Etc1,
    ChannelFormat_Etc2,
    ChannelFormat_Etc2_Mask,
    ChannelFormat_Etc2_Alpha,
    ChannelFormat_Pvrtc1_2Bpp,
    ChannelFormat_Pvrtc1_4Bpp,
    ChannelFormat_Pvrtc1_Alpha_2Bpp,
    ChannelFormat_Pvrtc1_Alpha_4Bpp,
    ChannelFormat_Pvrtc2_Alpha_2Bpp,
    ChannelFormat_Pvrtc2_Alpha_4Bpp,
    ChannelFormat_Astc_4x4,
    ChannelFormat_Astc_5x4,
    ChannelFormat_Astc_5x5,
    ChannelFormat_Astc_6x5,
    ChannelFormat_Astc_6x6,
    ChannelFormat_Astc_8x5,
    ChannelFormat_Astc_8x6,
    ChannelFormat_Astc_8x8,
    ChannelFormat_Astc_10x5,
    ChannelFormat_Astc_10x6,
    ChannelFormat_Astc_10x8,
    ChannelFormat_Astc_10x10,
    ChannelFormat_Astc_12x10,
    ChannelFormat_Astc_12x12,
    ChannelFormat_B5_G5_R5_A1,
    ChannelFormat_End
};

enum TypeFormat {
    TypeFormat_Undefined,
    TypeFormat_Unorm,
    TypeFormat_Snorm,
    TypeFormat_Uint,
    TypeFormat_Sint,
    TypeFormat_Float,
    TypeFormat_UnormSrgb,
    TypeFormat_DepthStencil,
    TypeFormat_UintToFloat,
    TypeFormat_SintToFloat,
    TypeFormat_Ufloat,
    TypeFormat_End,
    TypeFormat_Bits = 8
};

enum ImageFormat {
    ImageFormat_Undefined,
    ImageFormat_R8_Unorm = 513,
    ImageFormat_R8_Snorm,
    ImageFormat_R8_Uint,
    ImageFormat_R8_Sint,
    ImageFormat_R4_G4_B4_A4_Unorm = 769,
    ImageFormat_A4_B4_G4_R4_Unorm = 1025,
    ImageFormat_R5_G5_B5_A1_Unorm = 1281,
    ImageFormat_A1_B5_G5_R5_Unorm = 1537,
    ImageFormat_R5_G6_B5_Unorm = 1793,
    ImageFormat_B5_G6_R5_Unorm = 2049,
    ImageFormat_R8_G8_Unorm = 2305,
    ImageFormat_R8_G8_Snorm,
    ImageFormat_R8_G8_Uint,
    ImageFormat_R8_G8_Sint,
    ImageFormat_R16_Unorm = 2561,
    ImageFormat_R16_Snorm,
    ImageFormat_R16_Uint,
    ImageFormat_R16_Sint,
    ImageFormat_R16_Float,
    ImageFormat_D16_Unorm = 2567,
    ImageFormat_R8_G8_B8_A8_Unorm = 2817,
    ImageFormat_R8_G8_B8_A8_Snorm,
    ImageFormat_R8_G8_B8_A8_Uint,
    ImageFormat_R8_G8_B8_A8_Sint,
    ImageFormat_R8_G8_B8_A8_UnormSrgb = 2822,
    ImageFormat_B8_G8_R8_A8_Unorm = 3073,
    ImageFormat_B8_G8_R8_A8_Snorm,
    ImageFormat_B8_G8_R8_A8_Uint,
    ImageFormat_B8_G8_R8_A8_Sint,
    ImageFormat_B8_G8_R8_A8_UnormSrgb = 3078,
    ImageFormat_R9_G9_B9_E5_SharedExp = 3333,
    ImageFormat_R10_G10_B10_A2_Unorm = 3585,
    ImageFormat_R10_G10_B10_A2_Uint = 3587,
    ImageFormat_R11_G11_B10_Float = 3845,
    ImageFormat_B10_G11_R11_Float = 4101,
    ImageFormat_R16_G16_Unorm = 4609,
    ImageFormat_R16_G16_Snorm,
    ImageFormat_R16_G16_Uint,
    ImageFormat_R16_G16_Sint,
    ImageFormat_R16_G16_Float,
    ImageFormat_D24_Unorm_S8_Uint = 4871,
    ImageFormat_R32_Uint = 5123,
    ImageFormat_R32_Sint,
    ImageFormat_R32_Float,
    ImageFormat_D32_Float = 5127,
    ImageFormat_R16_G16_B16_A16_Unorm = 5377,
    ImageFormat_R16_G16_B16_A16_Snorm,
    ImageFormat_R16_G16_B16_A16_Uint,
    ImageFormat_R16_G16_B16_A16_Sint,
    ImageFormat_R16_G16_B16_A16_Float,
    ImageFormat_D32_Float_S8_Uint_X24 = 5639,
    ImageFormat_R32_G32_Uint = 5891,
    ImageFormat_R32_G32_Sint,
    ImageFormat_R32_G32_Float,
    ImageFormat_R32_G32_B32_Uint = 6147,
    ImageFormat_R32_G32_B32_Sint,
    ImageFormat_R32_G32_B32_Float,
    ImageFormat_R32_G32_B32_A32_Uint = 6403,
    ImageFormat_R32_G32_B32_A32_Sint,
    ImageFormat_R32_G32_B32_A32_Float,
    ImageFormat_Bc1_Unorm = 6657,
    ImageFormat_Bc1_UnormSrgb = 6662,
    ImageFormat_Bc2_Unorm = 6913,
    ImageFormat_Bc2_UnormSrgb = 6918,
    ImageFormat_Bc3_Unorm = 7169,
    ImageFormat_Bc3_UnormSrgb = 7174,
    ImageFormat_Bc4_Unorm = 7425,
    ImageFormat_Bc4_Snorm,
    ImageFormat_Bc5_Unorm = 7681,
    ImageFormat_Bc5_Snorm,
    ImageFormat_Bc6_Float = 7941,
    ImageFormat_Bc6_Ufloat = 7946,
    ImageFormat_Bc7_Unorm = 8193,
    ImageFormat_Bc7_UnormSrgb = 8198,
    ImageFormat_Eac_R11_Unorm = 8449,
    ImageFormat_Eac_R11_Snorm,
    ImageFormat_Eac_R11_G11_Unorm = 8705,
    ImageFormat_Eac_R11_G11_Snorm,
    ImageFormat_Etc1_Unorm = 8961,
    ImageFormat_Etc2_Unorm = 9217,
    ImageFormat_Etc2_UnormSrgb = 9222,
    ImageFormat_Etc2_Mask_Unorm = 9473,
    ImageFormat_Etc2_Mask_UnormSrgb = 9478,
    ImageFormat_Etc2_Alpha_Unorm = 9729,
    ImageFormat_Etc2_Alpha_UnormSrgb = 9734,
    ImageFormat_Pvrtc1_2Bpp_Unorm = 9985,
    ImageFormat_Pvrtc1_2Bpp_UnormSrgb = 9990,
    ImageFormat_Pvrtc1_4Bpp_Unorm = 10241,
    ImageFormat_Pvrtc1_4Bpp_UnormSrgb = 10246,
    ImageFormat_Pvrtc1_Alpha_2Bpp_Unorm = 10497,
    ImageFormat_Pvrtc1_Alpha_2Bpp_UnormSrgb = 10502,
    ImageFormat_Pvrtc1_Alpha_4Bpp_Unorm = 10753,
    ImageFormat_Pvrtc1_Alpha_4Bpp_UnormSrgb = 10758,
    ImageFormat_Pvrtc2_Alpha_2Bpp_Unorm = 11009,
    ImageFormat_Pvrtc2_Alpha_2Bpp_UnormSrgb = 11014,
    ImageFormat_Pvrtc2_Alpha_4Bpp_Unorm = 11265,
    ImageFormat_Pvrtc2_Alpha_4Bpp_UnormSrgb = 11270,
    ImageFormat_Astc_4x4_Unorm = 11521,
    ImageFormat_Astc_4x4_UnormSrgb = 11526,
    ImageFormat_Astc_5x4_Unorm = 11777,
    ImageFormat_Astc_5x4_UnormSrgb = 11782,
    ImageFormat_Astc_5x5_Unorm = 12033,
    ImageFormat_Astc_5x5_UnormSrgb = 12038,
    ImageFormat_Astc_6x5_Unorm = 12289,
    ImageFormat_Astc_6x5_UnormSrgb = 12294,
    ImageFormat_Astc_6x6_Unorm = 12545,
    ImageFormat_Astc_6x6_UnormSrgb = 12550,
    ImageFormat_Astc_8x5_Unorm = 12801,
    ImageFormat_Astc_8x5_UnormSrgb = 12806,
    ImageFormat_Astc_8x6_Unorm = 13057,
    ImageFormat_Astc_8x6_UnormSrgb = 13062,
    ImageFormat_Astc_8x8_Unorm = 13313,
    ImageFormat_Astc_8x8_UnormSrgb = 13318,
    ImageFormat_Astc_10x5_Unorm = 13569,
    ImageFormat_Astc_10x5_UnormSrgb = 13574,
    ImageFormat_Astc_10x6_Unorm = 13825,
    ImageFormat_Astc_10x6_UnormSrgb = 13830,
    ImageFormat_Astc_10x8_Unorm = 14081,
    ImageFormat_Astc_10x8_UnormSrgb = 14086,
    ImageFormat_Astc_10x10_Unorm = 14337,
    ImageFormat_Astc_10x10_UnormSrgb = 14342,
    ImageFormat_Astc_12x10_Unorm = 14593,
    ImageFormat_Astc_12x10_UnormSrgb = 14598,
    ImageFormat_Astc_12x12_Unorm = 14849,
    ImageFormat_Astc_12x12_UnormSrgb = 14854,
    ImageFormat_B5_G5_R5_A1_Unorm = 15105
};

enum AttributeFormat {
    AttributeFormat_Undefined,
    AttributeFormat_4_4_Unorm = 257,
    AttributeFormat_8_Unorm = 513,
    AttributeFormat_8_Snorm,
    AttributeFormat_8_Uint,
    AttributeFormat_8_Sint,
    AttributeFormat_8_UintToFloat = 520,
    AttributeFormat_8_SintToFloat,
    AttributeFormat_8_8_Unorm = 2305,
    AttributeFormat_8_8_Snorm,
    AttributeFormat_8_8_Uint,
    AttributeFormat_8_8_Sint,
    AttributeFormat_8_8_UintToFloat = 2312,
    AttributeFormat_8_8_SintToFloat,
    AttributeFormat_16_Unorm = 2561,
    AttributeFormat_16_Snorm,
    AttributeFormat_16_Uint,
    AttributeFormat_16_Sint,
    AttributeFormat_16_Float,
    AttributeFormat_16_UintToFloat = 2568,
    AttributeFormat_16_SintToFloat,
    AttributeFormat_8_8_8_8_Unorm = 2817,
    AttributeFormat_8_8_8_8_Snorm,
    AttributeFormat_8_8_8_8_Uint,
    AttributeFormat_8_8_8_8_Sint,
    AttributeFormat_8_8_8_8_UintToFloat = 2824,
    AttributeFormat_8_8_8_8_SintToFloat,
    AttributeFormat_10_10_10_2_Unorm = 3585,
    AttributeFormat_10_10_10_2_Snorm,
    AttributeFormat_10_10_10_2_Uint,
    AttributeFormat_10_10_10_2_Sint,
    AttributeFormat_16_16_Unorm = 4609,
    AttributeFormat_16_16_Snorm,
    AttributeFormat_16_16_Uint,
    AttributeFormat_16_16_Sint,
    AttributeFormat_16_16_Float,
    AttributeFormat_16_16_UintToFloat = 4616,
    AttributeFormat_16_16_SintToFloat,
    AttributeFormat_32_Uint = 5123,
    AttributeFormat_32_Sint,
    AttributeFormat_32_Float,
    AttributeFormat_16_16_16_16_Unorm = 5377,
    AttributeFormat_16_16_16_16_Snorm,
    AttributeFormat_16_16_16_16_Uint,
    AttributeFormat_16_16_16_16_Sint,
    AttributeFormat_16_16_16_16_Float,
    AttributeFormat_16_16_16_16_UintToFloat = 5384,
    AttributeFormat_16_16_16_16_SintToFloat,
    AttributeFormat_32_32_Uint = 5891,
    AttributeFormat_32_32_Sint,
    AttributeFormat_32_32_Float,
    AttributeFormat_32_32_32_Uint = 6147,
    AttributeFormat_32_32_32_Sint,
    AttributeFormat_32_32_32_Float,
    AttributeFormat_32_32_32_32_Uint = 6403,
    AttributeFormat_32_32_32_32_Sint,
    AttributeFormat_32_32_32_32_Float
};

enum GpuAccess {
    GpuAccess_Read = 0x1,
    GpuAccess_Write = 0x2,
    GpuAccess_VertexBuffer = 0x4,
    GpuAccess_IndexBuffer = 0x8,
    GpuAccess_ConstantBuffer = 0x10,
    GpuAccess_Texture = 0x20,
    GpuAccess_UnorderedAccessBuffer = 0x40,
    GpuAccess_ColorBuffer = 0x80,
    GpuAccess_DepthStencil = 0x100,
    GpuAccess_IndirectBuffer = 0x200,
    GpuAccess_ScanBuffer = 0x400,
    GpuAccess_QueryBuffer = 0x800,
    GpuAccess_Descriptor = 0x1000,
    GpuAccess_ShaderCode = 0x2000,
    GpuAccess_Image = 0x4000
};

enum TileMode { TileMode_Optimal, TileMode_Linear, TileMode_End };

enum ShaderStage {
    ShaderStage_Vertex,
    ShaderStage_Hull,
    ShaderStage_Domain,
    ShaderStage_Geometry,
    ShaderStage_Pixel,
    ShaderStage_Compute,
    ShaderStage_End
};

enum ShaderCodeType {
    ShaderCodeType_Binary,
    ShaderCodeType_Ir,
    ShaderCodeType_Source,
    ShaderCodeType_SourceArray,
    ShaderCodeType_End
};

enum ShaderSourceFormat {
    ShaderSourceFormat_Glsl,
    ShaderSourceFormat_Hlsl,
    ShaderSourceFormat_End
};

enum ChannelMapping {
    ChannelMapping_Zero,
    ChannelMapping_One,
    ChannelMapping_Red,
    ChannelMapping_Green,
    ChannelMapping_Blue,
    ChannelMapping_Alpha,
    ChannelMapping_End
};

enum DepthStencilFetchMode {
    DepthStencilFetchMode_DepthComponent,
    DepthStencilFetchMode_StencilIndex,
    DepthStencilFetchMode_End
};

enum DepthStencilClearMode {
    DepthStencilClearMode_Depth = 1,
    DepthStencilClearMode_Stencil,
    DepthStencilClearMode_DepthStencil
};

enum ShaderInterfaceType {
    ShaderInterfaceType_Input,
    ShaderInterfaceType_Output,
    ShaderInterfaceType_Sampler,
    ShaderInterfaceType_ConstantBuffer,
    ShaderInterfaceType_UnorderedAccessBuffer,
    ShaderInterfaceType_Image,
    ShaderInterfaceType_SeparateTexture,
    ShaderInterfaceType_SeparateSampler,
    ShaderInterfaceType_End
};

enum ColorChannel {
    ColorChannel_Red,
    ColorChannel_Green,
    ColorChannel_Blue,
    ColorChannel_Alpha,
    ColorChannel_End
};

enum DescriptorPoolType {
    DescriptorPoolType_BufferView,
    DescriptorPoolType_TextureView,
    DescriptorPoolType_Sampler,
    DescriptorPoolType_End
};

enum DescriptorSlotType {
    DescriptorSlotType_ConstantBuffer,
    DescriptorSlotType_UnorderedAccessBuffer,
    DescriptorSlotType_TextureSampler,
    DescriptorSlotType_End
};

enum PipelineType { PipelineType_Graphics, PipelineType_Compute, PipelineType_End };

enum MemoryPoolProperty {
    MemoryPoolProperty_CpuInvisible = 0x1,
    MemoryPoolProperty_CpuUncached = 0x2,
    MemoryPoolProperty_CpuCached = 0x4,
    MemoryPoolProperty_GpuInvisible = 0x8,
    MemoryPoolProperty_GpuUncached = 0x10,
    MemoryPoolProperty_GpuCached = 0x20,
    MemoryPoolProperty_ShaderCode = 0x40,
    MemoryPoolProperty_Compressible = 0x80
};

enum CommandBufferType {
    CommandBufferType_Direct,
    CommandBufferType_Nested,
    CommandBufferType_End
};

enum BufferState {
    BufferState_Undefined = 0x0,
    BufferState_DataTransfer = 0x1,
    BufferState_CopySource = 0x2,
    BufferState_CopyDestination = 0x4,
    BufferState_VertexBuffer = 0x8,
    BufferState_IndexBuffer = 0x10,
    BufferState_ConstantBuffer = 0x20,
    BufferState_UnorderedAccessBuffer = 0x40,
    BufferState_IndirectArgument = 0x80,
    BufferState_QueryBuffer = 0x100
};

enum TextureState {
    TextureState_Undefined = 0x0,
    TextureState_DataTransfer = 0x1,
    TextureState_CopySource = 0x2,
    TextureState_CopyDestination = 0x4,
    TextureState_ShaderRead = 0x8,
    TextureState_ShaderWrite = 0x10,
    TextureState_ColorTarget = 0x20,
    TextureState_DepthRead = 0x40,
    TextureState_DepthWrite = 0x80,
    TextureState_Clear = 0x100,
    TextureState_ResolveSource = 0x200,
    TextureState_ResolveDestination = 0x400,
    TextureState_Present = 0x800
};

enum ShaderStageBit {
    ShaderStageBit_Vertex = 0x1,
    ShaderStageBit_Hull = 0x2,
    ShaderStageBit_Domain = 0x4,
    ShaderStageBit_Geometry = 0x8,
    ShaderStageBit_Pixel = 0x10,
    ShaderStageBit_Compute = 0x20,
    ShaderStageBit_All = ShaderStageBit_Vertex | ShaderStageBit_Hull | ShaderStageBit_Domain |
                         ShaderStageBit_Geometry | ShaderStageBit_Pixel | ShaderStageBit_Compute
};

enum PipelineStageBit {
    PipelineStageBit_VertexInput = 0x1,
    PipelineStageBit_VertexShader = 0x2,
    PipelineStageBit_HullShader = 0x4,
    PipelineStageBit_DomainShader = 0x8,
    PipelineStageBit_GeometryShader = 0x10,
    PipelineStageBit_PixelShader = 0x20,
    PipelineStageBit_RenderTarget = 0x40,
    PipelineStageBit_ComputeShader = 0x80
};

enum DebugMode { DebugMode_Disable, DebugMode_Enable, DebugMode_Full, DebugMode_End };

enum QueryTarget {
    QueryTarget_Timestamp,
    QueryTarget_SamplesPassed,
    QueryTarget_InputVertices,
    QueryTarget_InputPrimitives,
    QueryTarget_VertexShaderInvocations,
    QueryTarget_GeometryShaderInvocations,
    QueryTarget_GeometryShaderPrimitives,
    QueryTarget_ClippingInputPrimitives,
    QueryTarget_ClippingOutputPrimitives,
    QueryTarget_PixelShaderInvocations,
    QueryTarget_HullShaderInvocations,
    QueryTarget_DomainShaderInvocations,
    QueryTarget_ComputeShaderInvocations,
    QueryTarget_End
};

enum ShaderInitializeResult {
    ShaderInitializeResult_Success,
    ShaderInitializeResult_InvalidType,
    ShaderInitializeResult_InvalidFormat,
    ShaderInitializeResult_SetupFailed
};

enum SyncResult { SyncResult_Success, SyncResult_TimeoutExpired };

enum AcquireScanBufferResult { AcquireScanBufferResult_Success, AcquireScanBufferResult_Failed };

}  // namespace nn::gfx