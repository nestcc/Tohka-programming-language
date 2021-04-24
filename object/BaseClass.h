/*
 * @Author: nestcc 
 * @Date: 2021/4/4 18:17
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-24 21:49:10
 * @Discription: 
 */

#ifndef _TOHKA_BASE_CLASS_H_
#define _TOHKA_BASE_CLASS_H_

#include "ObjectHeader.h"
#include "ObjString.h"
#include "Method.h"
#include "../vm/MemBufferSTL.h"

class BaseClass : public ObjHeader {
public:
    BaseClass *super_class;
    uint64_t field_num;
    typedef MemBufferSTL<Method> MethodBuffer;
    MethodBuffer methods;
    ObjString *name;
};

#endif //TOHKA_BASE_CLASS_H
