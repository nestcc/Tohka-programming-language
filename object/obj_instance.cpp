/*
 * @Author: nestcc 
 * @Date: 2021/4/4 18:40
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-24 21:05:12
 * @Discription: 
 */

#include "object/obj_instance.h"
#include "object/base_class.h"
#include "object/value.h"

ObjInstance::ObjInstance(VM *vm, BaseClass *base_class) :
ObjHeader(vm, OT_INSTANCE, base_class) {
    for (uint64_t i = 0; i < base_class -> field_num; i += 1) {
        fields.push_back(Value(VT_NULL));
    }
    size_t allocated = vm->alloc_memory(sizeof(*this) + sizeof(Value) * fields.capacity());
    LOG_INFO(" allocated ObjFunction by %lu B\n", allocated);
}
