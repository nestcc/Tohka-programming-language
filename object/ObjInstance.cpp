/*
 * @Author: nestcc 
 * @Date: 2021/4/4 18:40
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/4 18:40
 * @Discription: 
 */

#include "ObjInstance.h"
#include "BaseClass.h"
#include "Value.h"

ObjInstance::ObjInstance(VM *vm, BaseClass *base_class) :
ObjHeader(vm, OT_INSTANCE, base_class) {
    for (uint64_t i = 0; i < base_class -> field_num; i += 1) {
        fields.push_back(Value(VT_NULL));
    }
    size_t allocated = vm -> alloca_memory(sizeof(*this) + sizeof(Value) * fields.capacity());
    LOG_INFO(" allocated ObjFunction by %lu B\n", allocated);
}
