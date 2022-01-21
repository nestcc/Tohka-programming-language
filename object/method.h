/*
 * @Author: nestcc 
 * @Date: 2021/4/4 23:28
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-05-01 09:54:46
 * @Discription: 
 */

#ifndef _TOHKA_METHOD_H_
#define _TOHKA_METHOD_H_

#include "object/headers.h"

class method {
public:
    MethodType type;
    union {
        Primitive prim_func;
        ObjClosure *obj;
    };
    method() = default;
};

#endif //TOHKA_METHOD_H
