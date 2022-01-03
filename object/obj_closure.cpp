/*
 * @Author: nestcc 
 * @Date: 2021/4/4 23:44
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/4 23:44
 * @Discription: 
 */

#include "obj_closure.h"

ObjClosure::ObjClosure(VM *vm, ObjFunction *func_obj) :
ObjHeader(vm, OT_UPVALUE, vm -> func_cls){
    upvalues = std::vector<ObjUpvalue *>(func_obj -> up_val_num);
    func = func_obj;

    for (uint64_t i = 0; i < func_obj -> up_val_num; i += 1) {
        upvalues[i] = nullptr;
    }
    size_t allocated = vm -> alloca_memory(sizeof(*this) +
            sizeof(ObjUpvalue *) * upvalues.capacity());
    LOG_INFO(" allocated ObjClosure by %lu\n", allocated);
}
