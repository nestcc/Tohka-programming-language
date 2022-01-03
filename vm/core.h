/*
 * @Author: Nestcc
 * @Date: 2021-03-12 16:22:55
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-05-08 15:33:50
 * @Description:  < file content > 
 */

#ifndef _CORE_H_
#define _CORE_H_

#include "../includes/common.h"
#include "../includes/utils.h"
#include "../object/headers.h"
#include "mem_buffer_stl.h"

extern char *root_dir;
char *read_file(const char *fname);
void build_core(VM *vm);
VM::VmResult exec_module(VM *vm, Value module_name, const char *module_code);
int get_index_from_symbol_table(MethodNameList *table, std::string &name);

void bind_method(BaseClass *base_class, uint64_t index, method *pMethod);
void bind_super_class(BaseClass *sub_class, BaseClass *super_class);

#endif
