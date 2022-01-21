/*
 * @Author: Nestcc
 * @Date: 2021-04-27 09:28:49
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-05-08 15:44:48
 * @Description:  < file content > 
 */

#ifndef _COMPILER_H_
#define _COMPILER_H_

#include <string>
#include "object/obj_function.h"
#include "compiler/headers.h"
#include "compiler/local_var.h"
#include "compiler/upvalue.h"
#include "compiler/loop.h"
#include "object/obj_function.h"
#include "parser/parser.h"

int define_module_value(VM *vm, ObjModule *obj_module, std::string name, const Value &val);

ObjFunction *compile_module(VM *vm, ObjModule *module, const std::string &module_code);

#endif
