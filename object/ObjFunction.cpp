/*
 * @Author: nestcc 
 * @Date: 2021/4/4 23:35
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/4 23:35
 * @Discription: 
 */

#include "ObjFunction.h"
#include "ObjModule.h"
#include "ObjString.h"
#include "Value.h"

ObjFunction::ObjFunction(VM *vm, ObjModule *obj_module, uint64_t slot_num) :
ObjHeader(vm, OT_FUNCTION, vm -> func_cls){
    LOG_INFO(" new ObjFunction slot_num = %llu\n, module = %s\n", slot_num, obj_module -> name -> value.data());
    ins_stream = ByteBuffer();
    constants = ValueBuffer();

    module = obj_module;
    max_stk_slot_num = slot_num;
    up_val_num = arg_num = 0;
    size_t allocated = vm -> alloca_memory(sizeof(*this));

    LOG_INFO(" allocated ObjFunction by %lu\n", allocated);
}

//
//ObjFunction::~ObjFunction() {
//    this -> ObjHeader::vm -> realloca_memory();
//}
