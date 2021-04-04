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
    Value(ValueType vt);
    Value(const bool &bl);
    Value(const double &num);
    bool to_bool();
};   //通用的值结构

#endif //TOHKA_VALUE_H
