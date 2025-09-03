# Stripped version of zlib's CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

project(zlib C)

set(VERSION "1.2.8")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/zconf.h.cmakein
                 ${CMAKE_CURRENT_BINARY_DIR}/zconf.h @ONLY)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(ZLIB_PUBLIC_HDRS
    ${CMAKE_CURRENT_BINARY_DIR}/zconf.h
    zlib.h
)
set(ZLIB_PRIVATE_HDRS
    crc32.h
    deflate.h
    gzguts.h
    inffast.h
    inffixed.h
    inflate.h
    inftrees.h
    trees.h
    zutil.h
)
set(ZLIB_SRCS
    adler32.c
    compress.c
    crc32.c
    deflate.c
    gzclose.c
    gzlib.c
    gzread.c
    gzwrite.c
    inflate.c
    infback.c
    inftrees.c
    inffast.c
    trees.c
    uncompr.c
    zutil.c
)

# zlib has lots of warnings that we don't care about
add_compile_options(-w)

# parse the full version number from zlib.h and include in ZLIB_FULL_VERSION
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/zlib.h _zlib_h_contents)
string(REGEX REPLACE ".*#define[ \t]+ZLIB_VERSION[ \t]+\"([-0-9A-Za-z.]+)\".*"
    "\\1" ZLIB_FULL_VERSION ${_zlib_h_contents})

add_library(zlibstatic STATIC ${ZLIB_SRCS} ${ZLIB_PUBLIC_HDRS})
set_target_properties(zlibstatic PROPERTIES OUTPUT_NAME z)

# add_library(zlib SHARED ${ZLIB_SRCS} ${ZLIB_PUBLIC_HDRS})
# set_target_properties(zlib PROPERTIES OUTPUT_NAME z DEFINE_SYMBOL ZLIB_DLL)