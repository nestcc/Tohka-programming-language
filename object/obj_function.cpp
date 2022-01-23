/*
 * @Author: nestcc 
 * @Date: 2021/4/4 23:35
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-05-08 16:30:50
 * @Discription: 
 */

#include "object/obj_function.h"
#include "object/obj_module.h"
#include "object/obj_string.h"
#include "object/value.h"


ObjFunction::ObjFunction(VM *vm, ObjModule *obj_module, uint64_t slot_num) :
        ObjHeader(vm, OT_FUNCTION, vm -> func_cls) {
    LOG_INFO(" new ObjFunction slot_num = %llu\n, module = %s\n", slot_num, obj_module -> name -> value . data());
    // instr_stream = ByteBuffer(vm, 0);
    new (&instr_stream) ByteBuffer(vm, 0);
    // constants = ValueBuffer(vm, 0);
    new (&constants) ValueBuffer(vm, 0);

    module = obj_module;
    max_stk_slot_num = slot_num;
    up_val_num = arg_num = 0;
    size_t allocated = vm->alloc_memory(sizeof(*this));

    LOG_INFO(" allocated ObjFunction by %lu\n", allocated);
}

//
//ObjFunction::~ObjFunction() {
//    this -> ObjHeader::vm -> realloc_memory();
//}
