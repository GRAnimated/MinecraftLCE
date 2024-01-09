#pragma once

// Constants found by running nvnDeviceGetInteger for every value in NVNdeviceInfo within SMO

// TODO: 0x60 and 0x61 of NVNdeviceInfo don't exist in SMO, so those have not been added.
// TODO: These constants should probably have a comment explaining each one

#define NVN_DEVICE_UNIFORM_BUFFER_BINDINGS_PER_STAGE 14
#define NVN_DEVICE_MAX_UNIFORM_BUFFER_SIZE 65536
#define NVN_DEVICE_UNIFORM_BUFFER_ALIGNMENT 256
#define NVN_DEVICE_COLOR_BUFFER_BINDINGS 8
#define NVN_DEVICE_VERTEX_BUFFER_BINDINGS 16
#define NVN_DEVICE_TRANSFORM_FEEDBACK_BUFFER_BINDINGS 4
#define NVN_DEVICE_SHADER_STORAGE_BUFFER_BINDINGS_PER_STAGE 16
#define NVN_DEVICE_TEXTURE_BINDINGS_PER_STAGE 32
#define NVN_DEVICE_COUNTER_ALIGNMENT 16
#define NVN_DEVICE_TRANSFORM_FEEDBACK_BUFFER_ALIGNMENT 4
#define NVN_DEVICE_TRANSFORM_FEEDBACK_CONTROL_ALIGNMENT 4
#define NVN_DEVICE_INDIRECT_DRAW_ALIGNMENT 4
#define NVN_DEVICE_VERTEX_ATTRIBUTES 16
#define NVN_DEVICE_TEXTURE_DESCRIPTOR_SIZE 32
#define NVN_DEVICE_SAMPLER_DESCRIPTOR_SIZE 32
#define NVN_DEVICE_RESERVED_TEXTURE_DESCRIPTORS 256
#define NVN_DEVICE_RESERVED_SAMPLER_DESCRIPTORS 256
#define NVN_DEVICE_COMMAND_BUFFER_COMMAND_ALIGNMENT 4
#define NVN_DEVICE_COMMAND_BUFFER_CONTROL_ALIGNMENT 8
#define NVN_DEVICE_COMMAND_BUFFER_MIN_COMMAND_SIZE 512
#define NVN_DEVICE_COMMAND_BUFFER_MIN_CONTROL_SIZE 256
#define NVN_DEVICE_SHADER_SCRATCH_MEMORY_SCALE_FACTOR_MINIMUM 2
#define NVN_DEVICE_SHADER_SCRATCH_MEMORY_SCALE_FACTOR_RECOMMENDED 256
#define NVN_DEVICE_SHADER_SCRATCH_MEMORY_ALIGNMENT 4096
#define NVN_DEVICE_SHADER_SCRATCH_MEMORY_GRANULARITY 131072
#define NVN_DEVICE_MAX_TEXTURE_ANISOTROPY 16
#define NVN_DEVICE_MAX_COMPUTE_WORK_GROUP_SIZE_X 1536
#define NVN_DEVICE_MAX_COMPUTE_WORK_GROUP_SIZE_Y 1024
#define NVN_DEVICE_MAX_COMPUTE_WORK_GROUP_SIZE_Z 64
#define NVN_DEVICE_MAX_COMPUTE_WORK_GROUP_SIZE_THREADS 1536
#define NVN_DEVICE_MAX_COMPUTE_DISPATCH_WORK_GROUPS_X 65535
#define NVN_DEVICE_MAX_COMPUTE_DISPATCH_WORK_GROUPS_Y 65535
#define NVN_DEVICE_MAX_COMPUTE_DISPATCH_WORK_GROUPS_Z 65535
#define NVN_DEVICE_IMAGE_BINDINGS_PER_STAGE 8
#define NVN_DEVICE_MAX_TEXTURE_POOL_SIZE 1048576
#define NVN_DEVICE_MAX_SAMPLER_POOL_SIZE 4096
#define NVN_DEVICE_MAX_VIEWPORTS 16
#define NVN_DEVICE_MEMPOOL_TEXTURE_OBJECT_PAGE_ALIGNMENT 4096
#define NVN_DEVICE_SUPPORTS_MIN_MAX_FILTERING 1
#define NVN_DEVICE_SUPPORTS_STENCIL8_FORMAT 1
#define NVN_DEVICE_SUPPORTS_ASTC_FORMATS 1
#define NVN_DEVICE_L2_SIZE 262144
#define NVN_DEVICE_MAX_TEXTURE_LEVELS 15
#define NVN_DEVICE_MAX_TEXTURE_LAYERS 2048
#define NVN_DEVICE_GLSLC_MAX_SUPPORTED_GPU_CODE_MAJOR_VERSION 1
#define NVN_DEVICE_GLSLC_MIN_SUPPORTED_GPU_CODE_MAJOR_VERSION 1
#define NVN_DEVICE_GLSLC_MAX_SUPPORTED_GPU_CODE_MINOR_VERSION 14
#define NVN_DEVICE_GLSLC_MIN_SUPPORTED_GPU_CODE_MINOR_VERSION 5
#define NVN_DEVICE_SUPPORTS_CONSERVATIVE_RASTER 1
#define NVN_DEVICE_SUBPIXEL_BITS 8
#define NVN_DEVICE_MAX_SUBPIXEL_BIAS_BITS 8
#define NVN_DEVICE_INDIRECT_DISPATCH_ALIGNMENT 4
#define NVN_DEVICE_ZCULL_SAVE_RESTORE_ALIGNMENT 32
#define NVN_DEVICE_SHADER_SCRATCH_MEMORY_COMPUTE_SCALE_FACTOR_MINIMUM 128
#define NVN_DEVICE_LINEAR_TEXTURE_STRIDE_ALIGNMENT 32
#define NVN_DEVICE_LINEAR_RENDER_TARGET_STRIDE_ALIGNMENT 128
#define NVN_DEVICE_MEMORY_POOL_PAGE_SIZE 65536
#define NVN_DEVICE_SUPPORTS_ZERO_FROM_UNMAPPED_VIRTUAL_POOL_PAGES 1
#define NVN_DEVICE_UNIFORM_BUFFER_UPDATE_ALIGNMENT 4
#define NVN_DEVICE_MAX_TEXTURE_SIZE 16384
#define NVN_DEVICE_MAX_BUFFER_TEXTURE_SIZE 134217728
#define NVN_DEVICE_MAX_3D_TEXTURE_SIZE 2048
#define NVN_DEVICE_MAX_CUBE_MAP_TEXTURE_SIZE 16384
#define NVN_DEVICE_MAX_RECTANGLE_TEXTURE_SIZE 16384
#define NVN_DEVICE_SUPPORTS_PASSTHROUGH_GEOMETRY_SHADERS 1
#define NVN_DEVICE_SUPPORTS_VIEWPORT_SWIZZLE 1
#define NVN_DEVICE_SUPPORTS_SPARSE_TILED_PACKAGED_TEXTURES 1
#define NVN_DEVICE_SUPPORTS_ADVANCED_BLEND_MODES 1
#define NVN_DEVICE_MAX_PRESENT_INTERVAL 5
#define NVN_DEVICE_SUPPORTS_DRAW_TEXTURE 1
#define NVN_DEVICE_SUPPORTS_TARGET_INDEPENDENT_RASTERIZATION 1
#define NVN_DEVICE_SUPPORTS_FRAGMENT_COVERAGE_TO_COLOR 1
#define NVN_DEVICE_SUPPORTS_POST_DEPTH_COVERAGE 1
#define NVN_DEVICE_SUPPORTS_IMAGES_USING_TEXTURE_HANDLES 1
#define NVN_DEVICE_SUPPORTS_SAMPLE_LOCATIONS 1
#define NVN_DEVICE_MAX_SAMPLE_LOCATION_TABLE_ENTRIES 16
#define NVN_DEVICE_SHADER_CODE_MEMORY_POOL_PADDING_SIZE 1024
#define NVN_DEVICE_MAX_PATCH_SIZE 32
#define NVN_DEVICE_QUEUE_COMMAND_MEMORY_GRANULARITY 4096
#define NVN_DEVICE_QUEUE_COMMAND_MEMORY_MIN_SIZE 65536
#define NVN_DEVICE_QUEUE_COMMAND_MEMORY_DEFAULT_SIZE 65536
#define NVN_DEVICE_QUEUE_COMPUTE_MEMORY_GRANULARITY 256
#define NVN_DEVICE_QUEUE_COMPUTE_MEMORY_MIN_SIZE 16384
#define NVN_DEVICE_QUEUE_COMPUTE_MEMORY_DEFAULT_SIZE 262144
#define NVN_DEVICE_QUEUE_COMMAND_MEMORY_MIN_FLUSH_THRESHOLD 4096
#define NVN_DEVICE_SUPPORTS_FRAGMENT_SHADER_INTERLOCK 1
#define NVN_DEVICE_MAX_TEXTURES_PER_WINDOW 4
#define NVN_DEVICE_MIN_TEXTURES_PER_WINDOW 2
#define NVN_DEVICE_QUEUE_CONTROL_MEMORY_MIN_SIZE 4096
#define NVN_DEVICE_QUEUE_CONTROL_MEMORY_DEFAULT_SIZE 16384
#define NVN_DEVICE_QUEUE_CONTROL_MEMORY_GRANULARITY 4096
#define NVN_DEVICE_SEPARATE_TEXTURE_BINDINGS_PER_STAGE 128
#define NVN_DEVICE_SEPARATE_SAMPLER_BINDINGS_PER_STAGE 32