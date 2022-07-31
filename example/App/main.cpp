/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include "sgx_urts.h"
#include "Enclave_u.h"

sgx_enclave_id_t global_eid = 0;

/* Initialize the enclave:
 *   Call sgx_create_enclave to initialize an enclave instance
 */
sgx_status_t initialize_enclave(const char* enclave_file)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    
    /* Call sgx_create_enclave to initialize an enclave instance */
    /* Debug Support: set 2nd parameter to 1 */
    ret = sgx_create_enclave(enclave_file, SGX_DEBUG_FLAG, NULL, NULL, &global_eid, NULL);
    if (ret != SGX_SUCCESS) {
        printf("sgx_create_enclave() failed! ret: %d\n",ret);
        return ret;
    }

    return ret;
}

int SGX_CDECL main(int argc, char *argv[])
{
    int ret = 0;
    sgx_status_t result;

    // Initialize the enclave
    if ( ( result = initialize_enclave( (const char*)argv[1] ) ) != SGX_SUCCESS ) {
        fprintf( stderr, "initialize_enclave() failed! result = 0x%x, enclave file: %s\n", result, argv[1] );
        goto exit; 
    }
    fprintf( stdout, "Enclave is initialized!\n" );

    result = ecall_test_libA( global_eid, &ret, 1, 2 );
    fprintf( stdout, "ecall_test_libA(): 1 + 2 = %d\n", ret );
    fprintf( stdout, "\n" );

    result = ecall_test_libB( global_eid, &ret, 1, 2 );
    fprintf( stdout, "ecall_test_libB(): 1 + 2 = %d\n", ret );

exit:
    /* Destroy the enclave */
    sgx_destroy_enclave(global_eid);

    return 0;
}