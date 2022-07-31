/**
 * @file b.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "b.h"
#include "b_t.h"   // for ocall_printf
#include <string>

/* 
 * printf: 
 *   Invokes OCALL to display the enclave buffer to the terminal.
 */
int printf(const char* fmt, ...)
{
    char buf[BUFSIZ] = { '\0' };
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    ocall_printf(buf);
    return (int)strnlen(buf, BUFSIZ - 1) + 1;
}

int B_func_sum(int x, int y)
{
    printf("B_func_sum()-->x: %d, y: %d\n", x, y);
    return x + y;
}

int B::sum(int x, int y)
{
    printf("B::sum()-->x: %d, y: %d\n", x, y);
    return x + y;
}

// A null root public ECALL
void dummy( void )
{
}