/*
 * @Author: Nestcc
 * @Date: 2021-05-01 09:30:09
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-05-08 16:06:57
 * @Description:  < file content > 
 */

#include "vm.h"
#include "core.h"
#include "primitive_methods.h"
#include "../object/method.h"
#include "../object/value.h"
#include "../object/base_class.h"
#include "../includes/utils.h"

static inline BaseClass *get_class_of_val(VM *vm, Value *val) {
    switch (val -> type) {
        case VT_NULL:
            return vm -> null_class;
        case VT_TRUE:
        case VT_FALSE:
            return vm -> bool_class;
        case VT_NUM:
            return vm -> num_class;
        case VT_OBJ:
            return val -> obj_header -> cls;
        // case VT_UNDEFINED:
        default:
            NOT_REACHED();
    }
    return nullptr;
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

// bool obj_meta_type(VM *vm, Value *args) {
    
// }
