/*
 * @Author: Nestcc
 * @Date: 2021-04-27 09:28:49
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-27 19:11:01
 * @Description:  < file content > 
 */

#ifndef _COMPILER_H_
#define _COMPILER_H_

#include "../object/ObjFunction.h"

int define_module_value(VM *vm, ObjModule *obj_module, const char *name, uint64_t length, Value &val);

#endif
