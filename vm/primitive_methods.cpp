/*
 * @Author: Nestcc
 * @Date: 2021-05-01 09:30:09
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-05-01 10:12:40
 * @Description:  < file content > 
 */

#include "primitive_methods.h"
#include "../object/Method.h"
#include "../object/Value.h"
#include "../includes/utils.h"

inline void func_bind_method(Method *method, Primitive prim_func) {
    if (method == nullptr) {
        COMPILE_ERROR(nullptr, "method is nullptr.");
        return;
    }
    else if (prim_func == nullptr) {
        COMPILE_ERROR(nullptr, "primitive function is nullptr.");
        return;
    }
    method -> prim_func = prim_func;
}

bool obj_not(VM *vm, Value *args) {
    return args[0] == VT_NULL;
}

bool obj_equal(VM *vm, Value *args) {
    return args[0] == args[1];
}

bool obj_not_equal(VM *vm, Value *args) {
    return !(args[0] == args[1]);
}

bool obj_is_sub(VM *vm, Value *args) {
    if (args[1].type != VT_OBJ || args[1].obj_header -> type != OT_CLASS) 
        RUNTIME_ERROR("Argument must be a class.");
    
    BaseClass *curr_cls = nullptr;
}

bool obj_type(VM *vm, Value *args);

bool obj_type_name(VM *vm, Value *args);

bool obj_super_type(VM *vm, Value *args);
