# Set all flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SGX_COMMON_CFLAGS} -fPIC -Wno-attributes")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -std=c++11")

# Source files
set(LIB_B_UNTRUSTED_SRC_FILES
        ocall.cpp
)             

# Use the edger8r to generate C bindings from the EDL file.
add_custom_command(OUTPUT b_u.h b_u.c 
        DEPENDS ${CMAKE_SOURCE_DIR}/trusted/b.edl
        COMMAND ${SGX_EDGER8R} --untrusted ${CMAKE_SOURCE_DIR}/trusted/b.edl
        --search-path ${SGX_SDK}/include
)
message(STATUS "COMMAND: ${SGX_EDGER8R} --untrusted ${CMAKE_SOURCE_DIR}/trusted/b.edl")

# Additional include paths
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${SGX_SDK}/include
)

# Build static library
add_library(${TARGET_NAME}_u STATIC
            ${LIB_B_UNTRUSTED_SRC_FILES}
            ${CMAKE_CURRENT_BINARY_DIR}/b_u.c
)

# Needed for the generated file b_u.h
target_include_directories(${TARGET_NAME}_u PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# Files for make install
install(TARGETS ${TARGET_NAME}_u
    DESTINATION lib
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

# Install include file
file(GLOB LIB_UNTRUST_HEADERS "include/*.h")
install(FILES ${LIB_UNTRUST_HEADERS}
        DESTINATION include/lib-b
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)

message(STATUS "\n\n")
