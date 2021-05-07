/*
 * @Author: Nestcc
 * @Date: 2021-05-01 09:30:09
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-05-07 15:44:46
 * @Description:  < file content > 
 */

#include "primitive_methods.h"
#include "../object/Method.h"
#include "../object/Value.h"
#include "../object/BaseClass.h"
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

#define RET_VALUE(val) args[0] = val; return true;

bool obj_not(VM *vm, Value *args) {
    args[0] = Value(VT_NULL);
    return true;
}

bool obj_equal(VM *vm, Value *args) {
    args[0] = Value(args[0] == args[1]);
    return true;
}

bool obj_not_equal(VM *vm, Value *args) {
    args[0] = Value(args[0] != args[1]);
    return true;
}

bool obj_is_sub(VM *vm, Value *args) {
    if (args[1].type != VT_OBJ || args[1].obj_header -> type != OT_CLASS) 
        RUNTIME_ERROR("Argument must be a class.");
    
    BaseClass *curr_cls = get_class_of_val(vm, &args[0]);
    BaseClass *base_cls = dynamic_cast<BaseClass *> (args[1].obj_header);

    while (base_cls) {
        if (curr_cls == base_cls) {
            RET_VALUE(Value(true));
        }
        base_cls = base_cls -> super_class;
    }
    RET_VALUE(Value(false));
}

bool obj_type(VM *vm, Value *args) {
    BaseClass *base_cls = get_class_of_val(vm, &args[0]);
    RET_VALUE(Value(base_cls));
}

bool obj_type_name(VM *vm, Value *args) {
    ObjHeader *obj = (ObjHeader *) args[0];
    RET_VALUE(Value(obj -> cls -> name));
}

bool obj_super_type(VM *vm, Value *args) {
    ObjHeader *obj = (ObjHeader *) args[0];
    RET_VALUE(Value(obj -> cls -> super_class));
}
