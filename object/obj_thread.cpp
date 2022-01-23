/*
 * @Author: Nestcc
 * @Date: 2021-04-24 20:44:39
 * @LastEditors: Nestcc
 * @LastEditTime: 2022-01-03 20:16:38
 * @Description:  < file content > 
 */

#include "object/obj_thread.h"
#include "object/obj_upvalue.h"
#include "object/obj_closure.h"


void ObjThread::prepare_frame(ObjClosure *obj_closure, Value *stk_start) {
    ASSERT(frame_capacity > used_frame_num, "Not enough frame for thread.");
    
    Frame &f = frames[used_frame_num++];
    f.stack_start = stk_start;
    f.closure = obj_closure;
    f.ip = obj_closure -> func -> instr_stream.data();
}

void ObjThread::reset(ObjClosure *obj_closure) {
    ASSERT(obj_closure != nullptr, "Closure object is null.");
    esp = stk;
    if (open_up_values != nullptr) { open_up_values -> ref_cnt -= 1; }
    open_up_values = nullptr;

    if (caller != nullptr) { caller -> ref_cnt -= 1; }
    caller = nullptr;

    err_obj = Value(VT_NULL);
    used_frame_num = 0;

    prepare_frame(obj_closure, stk);
}

ObjThread::ObjThread(VM *vm, ObjClosure *obj_closure) :
ObjHeader(vm, OT_THREAD, vm -> thread_class) {
    ASSERT(obj_closure != nullptr, "Closure object is null.");
    
    frames = new Frame[INITIAL_FNUM];
    frame_capacity = INITIAL_FNUM;
    
    stk = new Value[stk_capacity];
    stk_capacity = obj_closure -> func -> max_stk_slot_num + 1;
    
    reset(obj_closure);
    vm->alloc_memory(sizeof(*this));
}

ObjThread::~ObjThread() {
    vm->realloc_memory(sizeof(*this), 0);
}
