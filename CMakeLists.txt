cmake_minimum_required(VERSION 3.13)
project(mcswitch CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Use response files when linking objects because of the large number of source files
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_OBJECTS ON)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options(-fcolor-diagnostics)
  # Required to silence "unused argument" warnings for -stdlib=libc++ when using distcc
  add_compile_options(-Wno-unused-command-line-argument)
  # Required to fix source paths in debug info when using distcc
  add_compile_options(-fdebug-prefix-map=/tmp=${CMAKE_CURRENT_BINARY_DIR})
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES_GAME ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.c ${PROJECT_SOURCE_DIR}/src/*.hpp ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/lib/windows.cpp)

file(GLOB_RECURSE UNITY_SOURCES
    ${PROJECT_SOURCE_DIR}/src/Minecraft.World/UnityWorld*.cpp
    ${PROJECT_SOURCE_DIR}/src/Minecraft.Client/UnityClient*.cpp
)

set(FINAL_SOURCES ${SOURCES_GAME})

foreach(UNITY_FILE ${UNITY_SOURCES})
    file(READ ${UNITY_FILE} CONTENTS)

    string(REGEX MATCHALL "#include +\"[^\"]+\\.cpp\"" INCLUDES "${CONTENTS}")

    foreach(INC ${INCLUDES})
        string(REGEX REPLACE "#include +\"" "" INC "${INC}")
        string(REGEX REPLACE "\"" "" INC "${INC}")

        foreach(SRC ${SOURCES_GAME})
            if(SRC MATCHES "${INC}$")
                list(REMOVE_ITEM FINAL_SOURCES "${SRC}")
            endif()
        endforeach()
    endforeach()
endforeach()

list(APPEND FINAL_SOURCES ${UNITY_SOURCES})

add_executable(mcswitch ${FINAL_SOURCES})

# Writing sources to a file so build.py script knows the sources
set(SOURCES_OUTPUT_FILE "${CMAKE_BINARY_DIR}/.build_sources")
file(WRITE ${SOURCES_OUTPUT_FILE} "")

get_target_property(SOURCES_COMBINED mcswitch SOURCES)

foreach (SOURCE ${SOURCES_COMBINED})
  file(APPEND ${SOURCES_OUTPUT_FILE} "${SOURCE}\n")
endforeach()

set(NN_SDK_MAJOR 4)
set(NN_SDK_MINOR 4)
set(NN_SDK_PATCH 1)
set(NN_SDK_TYPE "Release")

target_include_directories(mcswitch PRIVATE src)
target_include_directories(mcswitch PRIVATE src/Minecraft.Client)
target_include_directories(mcswitch PRIVATE src/Minecraft.World)
target_include_directories(mcswitch PRIVATE src/4JLibraries_Source)
target_include_directories(mcswitch PRIVATE src/PlatformLibraries_Source)
target_include_directories(mcswitch PUBLIC lib/nnheaders/include)

target_include_directories(mcswitch PUBLIC lib/stb_image)
target_include_directories(mcswitch PUBLIC lib/libpng)
target_include_directories(mcswitch PUBLIC lib/zlib)
target_include_directories(mcswitch PUBLIC lib)

target_compile_definitions(mcswitch PRIVATE NON_MATCHING)
target_compile_definitions(mcswitch PRIVATE MATCHING_HACK)
target_compile_options(mcswitch PRIVATE -fno-exceptions)
target_compile_options(mcswitch PRIVATE -fno-strict-aliasing)
target_compile_options(mcswitch PRIVATE -fsigned-char)
target_compile_options(mcswitch PRIVATE -Wall -Wextra -Wdeprecated)
target_compile_options(mcswitch PRIVATE -Wextra-semi)
target_compile_options(mcswitch PRIVATE -fno-inline -fno-inline-functions)
target_compile_options(mcswitch PRIVATE -fno-builtin)

# Disable some warnings that are unavoidable
target_compile_options(mcswitch PRIVATE -Wno-unused-parameter -Wno-unused-private-field -Wno-unused-variable)
target_compile_options(mcswitch PRIVATE -Wno-invalid-offsetof)
target_compile_options(mcswitch PRIVATE -Wno-deprecated)
# target_compile_options(mcswitch PRIVATE -Wno-delete-incomplete) # clangd warns about this one in MultiPlayerLevel.cpp
target_compile_options(mcswitch PRIVATE -Wno-sign-compare)

add_definitions(-D SAFETY_CHECKS)
add_definitions(-D UNUSED_DELETE)

add_subdirectory(lib/zlib)
target_include_directories(mcswitch PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/lib/zlib) # for zconf.h
target_link_libraries(mcswitch PRIVATE zlibstatic)

add_subdirectory(lib/libpng)
target_compile_options(libpng PRIVATE
  -fno-inline
  -fno-inline-functions
  -fno-builtin
)
target_link_options(mcswitch PRIVATE
    "SHELL:-Wl,--whole-archive"
    "$<TARGET_FILE:libpng>"
    "SHELL:-Wl,--no-whole-archive"
)
target_link_libraries(mcswitch PRIVATE libpng)
