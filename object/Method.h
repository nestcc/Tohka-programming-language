/*
 * @Author: nestcc 
 * @Date: 2021/4/4 23:28
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/4 23:28
 * @Discription: 
 */

#ifndef _TOHKA_METHOD_H_
#define _TOHKA_METHOD_H_

#include "headers.h"

class Method {
public:
    MethodType type;
    union {
        Primitive primFunc;
        ObjClosure *obj;
    };
};

#endif //TOHKA_METHOD_H
