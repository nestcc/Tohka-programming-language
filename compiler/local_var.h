/*
 * @Author: Nestcc
 * @Date: 2021-04-27 09:34:25
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-27 09:37:01
 * @Description:  < file content > 
 */

#ifndef _LOCALVAR_H_
#define _LOCALVAR_H_

#include "headers.h"

class LocalVar {
public:
    std::string name;
    uint64_t scope_depth;
    bool is_upvalue;
};

#endif