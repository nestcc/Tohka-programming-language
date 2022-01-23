/*
 * @Author: nestcc
 * @Date: 2021/4/4 18:40
 * @LastEditors: Nestcc
 * @LastEditTime: 2022-01-24 01:58:11
 * @Discription:
 */

#ifndef _TOHKA_OBJ_MODULE_H_
#define _TOHKA_OBJ_MODULE_H_

#include "object/object_header.h"
#include "vm/mem_buffer_stl.h"
#include "vm/vm.h"

class ObjModule : public ObjHeader {
public:
    SymbolTable module_var_name;   // 模块中的模块变量名
    ValueBuffer module_var_value;  // 模块中的模块变量值
    ObjString *name;               // 模块名

public:
    ObjModule() = default;
    ObjModule(VM *vm, const std::string &mod_name);
    ~ObjModule() override;

    void compile_module(const char *module_code);
    uint64_t define_var(const std::string &name, Value *value);
};

#endif  // TOHKA_OBJMODULE_H
