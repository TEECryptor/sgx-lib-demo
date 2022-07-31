/**
 * @file b.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _B_H_
#define _B_H_

int B_func_sum(int x, int y);

class B {
public:
    B(){};
    virtual ~B(){};
public:
    int sum(int x, int y);
};

#endif //_B_H_