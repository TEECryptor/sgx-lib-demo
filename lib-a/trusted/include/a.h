/**
 * @file a.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _A_H_
#define _A_H_

int A_func_sum(int x, int y);

class A {
public:
    A(){};
    virtual ~A(){};
public:
    int sum(int x, int y);
};

#endif //_A_H_