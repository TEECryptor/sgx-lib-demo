# CMake for application
#
# Set all flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SGX_COMMON_CFLAGS} -fPIC -Wno-attributes")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -std=c++11")

# Source files
set(APP_SRC_FILES 
        main.cpp
)

# Use the edger8r to generate C bindings from the EDL file.
add_custom_command(OUTPUT Enclave_u.h Enclave_u.c 
        DEPENDS ${CMAKE_SOURCE_DIR}/Enclave/Enclave.edl
        COMMAND ${SGX_EDGER8R} --untrusted ${CMAKE_SOURCE_DIR}/Enclave/Enclave.edl
        --search-path ${SGX_SDK}/include
        --search-path ${SGX_LIB_B_LIBRARY_DIR}
)
message(STATUS "COMMAND: ${SGX_EDGER8R} --untrusted ${CMAKE_SOURCE_DIR}/Enclave.edl")

add_executable(${PROJECT_NAME} 
        ${APP_SRC_FILES}
        ${CMAKE_CURRENT_BINARY_DIR}/Enclave_u.c
)

include_directories(
        ${SGX_SDK}/include
)
# Needed for the generated file Enclave_u.h
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

message(STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")

target_link_libraries(${PROJECT_NAME}
        -L${SGX_LIBRARY_PATH} -l${SGX_URTS_LIB} -l${SGX_USVC_LIB} 
        ${SGX_LIB_B_FILE_U} 
)

# Install target file
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
        DESTINATION ./
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ
)

message(STATUS "\n\n")
