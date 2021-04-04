/*
 * @Author: nestcc 
 * @Date: 2021/4/4 18:17
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/4 18:17
 * @Discription: 
 */

#ifndef _TOHKA_BASE_CLASS_H_
#define _TOHKA_BASE_CLASS_H_

#include "ObjectHeader.h"
#include "ObjString.h"
#include "Method.h"

class BaseClass {
public:
    ObjHeader header;
    BaseClass *super_class;
    uint64_t field_num;
    typedef MemBuffer<Method> MethodBuffer;
    MethodBuffer methods;
    ObjString *name;
};

#endif //TOHKA_BASE_CLASS_H
