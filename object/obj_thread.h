/*
 * @Author: Nestcc
 * @Date: 2021-04-24 20:33:33
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-24 21:59:23
 * @Description:  < file content > 
 */

#ifndef _OBJTHREAD_H_
#define _OBJTHREAD_H_

#include "object_header.h"
#include "value.h"
#include "frame.h"

class ObjThread : public ObjHeader {
    Value *stk;
    Value *esp;
    uint64_t stk_capacity;

    Frame *frames;
    uint64_t used_frame_num;
    uint64_t frame_capacity;

    ObjUpvalue *open_up_values;
    ObjThread *caller;
    Value err_obj;

public:
    ObjThread() = default;
    ObjThread(VM *vm, ObjClosure *obj_closure);
    void prepare_frame(ObjClosure *obj_closure, Value *stk_start);
    void reset(ObjClosure *obj_closure);
    ~ObjThread() override;
};

#endif
