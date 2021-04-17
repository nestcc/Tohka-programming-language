/*
 * @Author: nestcc 
 * @Date: 2021/4/4 23:28
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/4 23:28
 * @Discription: 
 */

#ifndef _TOHKA_VALUE_H_
#define _TOHKA_VALUE_H_

#include "headers.h"

class Value {
public:
    ValueType type;
    union {
        double num;
        ObjHeader* obj_header;
    };

    Value() = default;
    explicit Value(ValueType vt);
    explicit Value(const bool &bl);
    explicit Value(const double &num);
    explicit Value(const long &ln);

    explicit Value(ObjHeader *obj_ptr);

    explicit operator bool ();

    ~Value();
};   //通用的值结构

#endif //TOHKA_VALUE_H
