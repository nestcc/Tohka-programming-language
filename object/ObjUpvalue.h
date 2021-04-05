/*
 * @Author: nestcc 
 * @Date: 2021/4/4 23:42
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/4 23:42
 * @Discription: 
 */

#ifndef _TOHKA_UPVALUE_H_
#define _TOHKA_UPVALUE_H_

#include "ObjectHeader.h"
#include "Value.h"

class ObjUpvalue : public ObjHeader {
public:
    Value *local_val_ptr;
    Value closed_up_val;
    ObjUpvalue *next;

    ObjUpvalue() = default;
    ObjUpvalue(VM *vm, Value *local_value);
};



#endif //TOHKA_UPVALUE_H
