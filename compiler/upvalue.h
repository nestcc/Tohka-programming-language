/*
 * @Author: Nestcc
 * @Date: 2021-04-27 09:31:47
 * @LastEditors: Nestcc
 * @LastEditTime: 2022-01-21 16:50:26
 * @Description:  < file content >
 */

#ifndef _UPVALUE_H_
#define _UPVALUE_H_

#include "compiler/headers.h"

class Upvalue {
public:
    bool is_enclosing_local_var;
    uint64_t index;
};

#endif
