/*
 * @Author: nestcc 
 * @Date: 2021/4/4 22:48
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/4 22:48
 * @Discription: 
 */

#include "ObjString.h"
#include <string>

ObjString::ObjString(VM *vm, const std::string &str) :
ObjHeader(vm, OT_STRING, vm -> str_cls) {
    value = str;
    hash();
    vm -> alloca_memory(sizeof (*this));
}

uint64_t ObjString::hash() {
    hash_code = 2166136261;
    for (size_t i = 0; i < value.size(); i += 1) {
        hash_code ^= value[i];
        hash_code *= 16777619;
    }
    return hash_code;
}
