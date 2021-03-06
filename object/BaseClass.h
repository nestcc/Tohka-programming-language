/*
 * @Author: nestcc 
 * @Date: 2021/4/4 18:17
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-05-08 16:02:14
 * @Discription: 
 */

#ifndef _TOHKA_BASE_CLASS_H_
#define _TOHKA_BASE_CLASS_H_

#include "ObjectHeader.h"
#include "ObjString.h"
#include "Method.h"
#include "../vm/MemBufferSTL.h"

class BaseClass : public ObjHeader {
public:
    BaseClass *super_class;
    uint64_t field_num;
    typedef MemBufferSTL<Method> MethodBuffer;
    MethodBuffer methods;
    ObjString *name;

    BaseClass() = default;
    BaseClass(VM *vm, std::string name, uint64_t field_num);
    BaseClass(const BaseClass &base_class) = delete;
    BaseClass &operator=(const BaseClass &base_class) = delete;
    ~BaseClass() override;
};

// inline BaseClass *get_class_of_val(VM *vm, Value *val);

#endif //TOHKA_BASE_CLASS_H
