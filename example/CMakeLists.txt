cmake_minimum_required(VERSION 3.13)
project(example "C" "CXX")

set(PROJECT_VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(SGX_SDK "/opt/intel/sgxsdk")
set(SGX_ARCH x64)
set(SGX_MODE HW CACHE STRING "SGX mode: SIM or HW")
set(SGX_BUILD DEBUG CACHE STRING "Build: DEBUG, PRERELEASE or RELEASE")

include (cmake/Init.cmake)
include (cmake/ConfigSGX.cmake)

set(SGX_LIB_A_ROOT ${CMAKE_SOURCE_DIR}/../3rdparty/sgx-lib-a)
set(SGX_LIB_A_INCLUDE_DIR ${SGX_LIB_A_ROOT}/include)
set(SGX_LIB_A_LIBRARY_DIR ${SGX_LIB_A_ROOT}/lib)
set(SGX_LIB_A_FILE_T ${SGX_LIB_A_LIBRARY_DIR}/libsgx-lib-a_t.a)
message(STATUS "SGX_LIB_A_FILE_T = ${SGX_LIB_A_FILE_T}")

set(SGX_LIB_B_ROOT ${CMAKE_SOURCE_DIR}/../3rdparty/sgx-lib-b)
set(SGX_LIB_B_INCLUDE_DIR ${SGX_LIB_B_ROOT}/include)
set(SGX_LIB_B_LIBRARY_DIR ${SGX_LIB_B_ROOT}/lib)
set(SGX_LIB_B_FILE_T ${SGX_LIB_B_LIBRARY_DIR}/libsgx-lib-b_t.a)
set(SGX_LIB_B_FILE_U ${SGX_LIB_B_LIBRARY_DIR}/libsgx-lib-b_u.a)
message(STATUS "SGX_LIB_B_FILE_T = ${SGX_LIB_B_FILE_T}")
message(STATUS "SGX_LIB_B_FILE_U = ${SGX_LIB_B_FILE_U}")

option(DEBUG "option for debug" OFF)
if (DEBUG)
        set(CMAKE_BUILD_TYPE "Debug")
        add_definitions(-DDEBUG -UNDEBUG -UEDEBUG)
else ()
        set(CMAKE_BUILD_TYPE "Release")
        add_definitions(-DNDEBUG -UEDEBUG -UDEBUG)
endif ()

add_subdirectory(App)
add_subdirectory(Enclave)

message(STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "\n\n")