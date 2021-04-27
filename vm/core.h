/*
 * @Author: Nestcc
 * @Date: 2021-03-12 16:22:55
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-27 19:53:27
 * @Description:  < file content > 
 */

#ifndef _CORE_H_
#define _CORE_H_

#include "../includes/common.h"
#include "../includes/utils.h"
#include "../object/headers.h"
#include "MemBufferSTL.h"

extern char *root_dir;
char *read_file(const char *fname);
void build_core(VM *vm);
VM::VmResult exec_module(VM *vm, Value module_name, const char *module_code);
int get_index_from_symbol_table(SymbolTable *table, std::string &name);

void bind_method(BaseClass *base_class, uint64_t index, Method *method);
void bind_super_class(BaseClass *sub_class, BaseClass *super_class);

#endif
