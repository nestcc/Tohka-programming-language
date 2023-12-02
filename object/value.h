/*
 * @Author: nestcc 
 * @Date: 2021/4/4 23:28
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-05-08 15:12:55
 * @Discription: 
 */

#ifndef _TOHKA_VALUE_H_
#define _TOHKA_VALUE_H_

#include "object/object_header.h"
#include "core/vm.h"


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
    Value(const Value &val);
    Value(Value &&val);

    explicit operator bool ();

    explicit operator double();

    explicit operator ObjHeader *();

    Value &operator= (const Value &val);

    Value &operator= (Value &&val) noexcept ;

    uint64_t hash_value() const ;

    bool operator==(const double &num);

    bool operator==(ValueType vtype);

    friend bool operator==(const Value &v1, const Value &v2);

    friend bool operator!=(const Value &v1, const Value &v2);

    ObjHeader *toObj();

    VM::VmResult execute_module(const char* module_code);

    ~Value();
};   //通用的值结构

#endif //TOHKA_VALUE_H
