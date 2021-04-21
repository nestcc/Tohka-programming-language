/*
 * @Author: nestcc 
 * @Date: 2021/4/4 18:40
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-21 13:39:23
 * @Discription: 
 */

#include "ObjModule.h"
#include "ObjString.h"
#include "Value.h"
#include <iostream>

ObjModule::ObjModule(VM *vm, const std::string &mod_name) :
ObjHeader(vm, OT_MODULE, nullptr) {
    module_var_name = SymbolTable();
    module_var_value = ValueBuffer();

    delete name;
    name = new ObjString(vm, mod_name);
    vm -> alloca_memory(sizeof(*this));
    LOG_INFO(" allocated ObjModule by %lu\n", sizeof(*this));
    LOG_INFO(" module name = ");
    std::cout << mod_name << std::endl;
}

ObjModule::~ObjModule() {
    delete name;
}
