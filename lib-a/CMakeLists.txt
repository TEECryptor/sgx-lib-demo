cmake_minimum_required(VERSION 3.13)

project(sgx-lib-a "C" "CXX")
set(TARGET_NAME sgx-lib-a)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(SGX_SDK "/opt/intel/sgxsdk")
set(SGX_ARCH x64)
set(SGX_MODE HW CACHE STRING "SGX mode: SIM or HW")
set(SGX_BUILD RELEASE CACHE STRING "Build: DEBUG, PRERELEASE or RELEASE")

include (cmake/Init.cmake)
include (cmake/ConfigSGX.cmake)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/../3rdparty/${PROJECT_NAME})

add_subdirectory(trusted)

message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message(STATUS "\n\n")