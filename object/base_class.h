/*
 * @Author: nestcc
 * @Date: 2021/4/4 18:17
 * @LastEditors: Nestcc
 * @LastEditTime: 2022-01-21 16:48:00
 * @Discription:
 */

#ifndef _TOHKA_BASE_CLASS_H_
#define _TOHKA_BASE_CLASS_H_

#include "object/method.h"
#include "object/obj_string.h"
#include "object/object_header.h"
#include "core/mem_buffer_stl.h"

class BaseClass : public ObjHeader {
public:
    BaseClass *super_class;
    uint64_t field_num;
    typedef MemBufferSTL<Method> MethodBuffer;
    MethodBuffer methods_buffer;
    ObjString *name;

    BaseClass() = default;
    BaseClass(VM *vm, std::string name, uint64_t field_num);
    BaseClass(const BaseClass &base_class) = delete;
    BaseClass &operator=(const BaseClass &base_class) = delete;
    ~BaseClass() override;

    void bind_super_class(BaseClass *super_class);
    void bind_method(uint64_t index, Method *methods);
    void bind_func(std::string method_name, Primitive prim_func);
};

// inline BaseClass *get_class_of_val(VM *vm, Value *val);

#endif  // TOHKA_BASE_CLASS_H
