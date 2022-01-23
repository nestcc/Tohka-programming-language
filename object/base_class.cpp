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
    new (&methods) MethodBuffer(vm, 0);
}

BaseClass::~BaseClass() {
    if (name != nullptr) {
        name->ref_cnt -= 1;
        if (name->ref_cnt == 0) {
            delete name;
        }
    }
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
