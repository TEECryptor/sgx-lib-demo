message(STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")

# Set projects srouce files
set(LIB_A_TRUSTED_SRC_FILES 
        a.cpp
)

# Additional include paths
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${SGX_SDK}/include
        ${SGX_SDK}/include/tlibc
        ${SGX_SDK}/include/libcxx
)

# build static library
add_library(${TARGET_NAME}_t STATIC
            ${LIB_A_TRUSTED_SRC_FILES}
)

# Set all flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SGX_COMMON_CFLAGS} -nostdinc -fvisibility=hidden -fpie -fstack-protector")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -nostdinc++")
        
# Link flags
target_link_libraries(${TARGET_NAME}_t "${SGX_COMMON_CFLAGS} \
        -Wl,--no-undefined -nostdlib -nodefaultlibs -nostartfiles -L${SGX_LIBRARY_PATH} \
        -Wl,--whole-archive -l${SGX_TRTS_LIB} -Wl,--no-whole-archive \
        -Wl,--start-group -lsgx_tstdc -lsgx_tcxx -lsgx_tcrypto -Wl,--end-group \
        -Wl,-Bstatic -Wl,-Bsymbolic -Wl,--no-undefined \
        -Wl,-pie,-eenclave_entry -Wl,--export-dynamic \
        -Wl,--defsym,__ImageBase=0"
)

# Install target file
install(TARGETS ${TARGET_NAME}_t
        DESTINATION lib
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)

# Install include file
file(GLOB LIB_TRUST_HEADERS "include/*.h")
install(FILES ${LIB_TRUST_HEADERS}
        DESTINATION include/lib-a
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)

message(STATUS "\n\n")