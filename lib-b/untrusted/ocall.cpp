/**
 * @file ocall.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>

#ifdef __cplusplus
extern "C"{
#endif

void ocall_printf(const char * str)
{
    printf("%s", str);
}

#ifdef __cplusplus
}
#endif