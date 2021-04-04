/*
 * @Author: nestcc 
 * @Date: 2021/4/4 18:40
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/4 18:40
 * @Discription: 
 */

#include "ObjModule.h"

ObjModule::ObjModule(VM *vm, const std::string &mod_name) :
ObjHeader(vm, OT_MODULE, nullptr){
    vm -> realloca_memory(0, sizeof ObjModule);

}
