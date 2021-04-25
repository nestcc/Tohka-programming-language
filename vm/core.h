/*
 * @Author: Nestcc
 * @Date: 2021-03-12 16:22:55
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-25 17:43:47
 * @Description:  < file content > 
 */

#ifndef _CORE_H_
#define _CORE_H_

#include "../includes/common.h"
#include "../includes/utils.h"
#include "vm.h"

extern char *root_dir;
char *read_file(const char *fname);
void build_core(VM *vm);
VM::VmResult exec_module(VM *vm, Value module_name, const char *module_code);

#endif
