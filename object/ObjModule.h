/*
 * @Author: nestcc 
 * @Date: 2021/4/4 18:40
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-21 13:39:11
 * @Discription: 
 */

#ifndef _TOHKA_OBJMODULE_H_
#define _TOHKA_OBJMODULE_H_

#include "ObjectHeader.h"

class ObjModule : public ObjHeader{
public:
    SymbolTable module_var_name;        // 模块中的模块变量名
    ValueBuffer module_var_value;       // 模块中的模块变量值
    ObjString *name;                    // 模块名

    ObjModule() = default;
    ObjModule(VM *vm, const std::string &mod_name);

    ~ObjModule() override;
};


#endif //TOHKA_OBJMODULE_H
