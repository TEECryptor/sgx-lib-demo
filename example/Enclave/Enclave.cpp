/**
 * @file Enclave.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

 #include "Enclave_t.h"
 #include <lib-a/a.h>
 #include <lib-b/b.h>

int ecall_test_libA(int x, int y)
{
    int ret = 0;
    A a;

    ret = A_func_sum(x, y);

    ret = a.sum(x, y);

    return ret;
}

int ecall_test_libB(int x, int y)
{
    int ret = 0;
    B b;

    ret = B_func_sum(x, y);

    ret = b.sum(x, y);

    return ret;
}