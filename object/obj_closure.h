/*
 * @Author: nestcc 
 * @Date: 2021/4/4 23:44
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/4 23:44
 * @Discription: 
 */

#ifndef _TOHKA_OBJ_CLOSURE_H_
#define _TOHKA_OBJ_CLOSURE_H_

#include <vector>
#include "object/obj_function.h"


class ObjClosure : public ObjHeader {
public:
    ObjFunction *func;

    typedef std::vector<ObjUpvalue *> UpvalueBuff;
    UpvalueBuff upvalues;

    ObjClosure() = default;
    ObjClosure(VM *vm, ObjFunction *func_obj);

    ~ObjClosure() override = default;
};


#endif //TOHKA_OBJCLOSURE_H
