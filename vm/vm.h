/*
 * @Author: Nestcc
 * @Date: 2021-03-12 16:13:34
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-03-16 10:21:16
 * @Description:  < file content > 
 */


#ifndef _VM_H_
#define _VM_H_

#include "../includes/common.h"

class VM {
protected:
    uint32_t allocated_byte;
    Parser *curr_parser;

public:
    VM();
};

#endif
