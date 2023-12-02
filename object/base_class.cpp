/*
 * @Author: Nestcc
 * @Date: 2021-04-28 10:38:25
 * @LastEditors: Nestcc
 * @LastEditTime: 2022-01-24 01:26:19
 * @Description:  < file content >
 */

#include "object/base_class.h"

#include "object/headers.h"
#include "object/value.h"

BaseClass::BaseClass(VM *vm, std::string name, uint64_t field_num)
    : ObjHeader(vm, OT_CLASS, nullptr) {
    this->name = new ObjString(vm, name);
    this->field_num = field_num;
    // this -> methods = MethodBuffer(vm, 0);
    new (&methods_buffer) MethodBuffer(vm, 0);
}

BaseClass::~BaseClass() {
    if (name != nullptr) {
        name->ref_cnt -= 1;
        if (name->ref_cnt == 0) {
            delete name;
        }
    }
}

void BaseClass::bind_super_class(BaseClass* super_class) {
    this -> super_class = super_class;
    this -> field_num += super_class -> field_num;
    for (uint64_t idx = 0; idx < super_class -> methods_buffer.size(); idx += 1) {
        bind_method(idx, &(super_class -> methods_buffer[idx]));
    }
}

void BaseClass::bind_method(uint64_t index, Method* method) {
    if (index >= methods_buffer.size()) {
        methods_buffer.fill_wirte(Method(), index - methods_buffer.size() + 1);
    }
    methods_buffer[index] = *method;
}

void BaseClass::bind_func(std::string method_name, Primitive prim_func) {
    if (method_name.empty()) {
        COMPILE_ERROR(nullptr, "method_name is empty.");
        return;
    }
    else if (prim_func == nullptr) {
        COMPILE_ERROR(nullptr, "primitive function is nullptr.");
        return;
    }

    uint64_t global_index = vm -> get_method_index(method_name);
    Method *method = new Method();
    method -> prim_func = prim_func;
    method -> type = MT_PRIMITIVE;
    bind_method(global_index, method);
}

// inline BaseClass *get_class_of_val(VM *vm, Value *val) {
//     switch (val -> type) {
//         case VT_NULL:
//             return vm -> null_class;
//         case VT_TRUE:
//         case VT_FALSE:
//             return vm -> bool_class;
//         case VT_NUM:
//             return vm -> num_class;
//         case VT_OBJ:
//             return val -> obj_header -> cls;
//     }
// }
