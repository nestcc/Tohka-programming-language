/*
 * @Author: Nestcc
 * @Date: 2021-04-27 09:42:53
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-27 09:45:46
 * @Description:  < file content > 
 */

#ifndef _CLASSBOOKKEEP_H_
#define _CLASSBOOKKEEP_H_

#include "headers.h"
#include "../vm/MemBufferSTL.h"

class Signature;

class ClassBookKeep {
public:
    std::string name;
    SymbolTable fields;
    bool is_static;
    MemBufferSTL<int> instant_method;
    MemBufferSTL<int> static_method;
    Signature *signature;
};

#endif
