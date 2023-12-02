// /*
//  * @Author: Nestcc
//  * @Date: 2021-03-12 16:22:55
//  * @LastEditors: Nestcc
//  * @LastEditTime: 2021-05-08 15:33:50
//  * @Description:  < file content >
//  */
//
// #ifndef _CORE_H_
// #define _CORE_H_
//
// #include "includes/common.h"
// #include "includes/utils.h"
// #include "object/headers.h"
// #include "core/mem_buffer_stl.h"
//
//
// class Core {
// public:
//     char *root_dir;
//     VM *vm;
//
// public:
//     Core() : root_dir(nullptr), vm(nullptr) {}
//
//     char *read_file(const char *fname);
//
//     void build();
//
//     VM::VmResult exec_module(Value module_name, const char *module_code);
//
//     int get_index_from_symbol_table(VM::MethodNameList *table, const std::string &name);
//     int add_symbol(SymbolTable *table, const std::string &symbol);
//     void bind_method(BaseClass *base_class, uint64_t index, Method *pMethod);
//     void bind_super_class(BaseClass *sub_class, BaseClass *super_class);
//
// private:
//     inline void func_bind_class(VM *vm, BaseClass *base_cls, const std::string &method_name, Primitive prim_func);
//     ObjModule *get_module(const Value &module_name);
//     ObjThread *load_module(const Value &module_name, const std::string &module_code);
// };
// #endif
