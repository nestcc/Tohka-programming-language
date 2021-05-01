/*
 * @Author: Nestcc
 * @Date: 2021-05-01 09:30:28
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-05-01 09:57:18
 * @Description:  < file content > 
 */

#ifndef _PRIMITIVE_METHODS_H_
#define _PRIMITIVE_METHODS_H_

#include "core.h"
#include "vm.h"
#include "../object/headers.h"

// !object
bool obj_not(VM *vm, Value *args);

// args[0] == args[1]
bool obj_equal(VM *vm, Value *args);

// args[0] != args[1]
bool obj_not_equal(VM *vm, Value *args);

// args[0] is args[1] : args[0] is a sub-class of args[1]
bool obj_is_sub(VM *vm, Value *args);

// args[0].type
bool obj_type(VM *vm, Value *args);

// args[0].typeName
bool obj_type_name(VM *vm, Value *args);

// args[0].superType : return super class of args[0]
bool obj_super_type(VM *vm, Value *args);

// bind a function to a method
inline void func_bind_method(Method *method, Primitive *prim_func);

#endif
