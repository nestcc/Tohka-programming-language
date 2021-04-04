/*
 * @Author: nestcc 
 * @Date: 2021/4/4 23:42
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/4 23:42
 * @Discription: 
 */

#include "ObjUpvalue.h"

ObjUpvalue::ObjUpvalue(VM *vm, Value *local_value)
: ObjHeader(vm, OT_UPVALUE, nullptr) {
    local_val_ptr = local_value;
    closed_up_val = Value(VT_NULL);
    next = nullptr;
}
