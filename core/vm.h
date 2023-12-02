/*
 * @Author: Nestcc
 * @Date: 2021-03-12 16:13:34
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-05-08 15:33:30
 * @Description:  < file content > 
 */

#ifndef _VM_H_
#define _VM_H_

#include <vector>
#include <string>
#include "object/headers.h"

class ObjHeader;
class BaseClass;
class ObjMap;
class ObjThread;


class VM {
public:
    typedef std::vector<std::string> MethodNameList;

    // 虚拟机执行结果
    enum VmResult {
        VM_RESULT_SUCCESS,
        VM_RESULT_ERROR
    };
    char *root_dir;
    uint64_t allocated_byte;
    Parser *curr_parser;
    ObjHeader *all_objects;

    BaseClass *str_cls;
    BaseClass *func_cls;
    BaseClass *class_of_class;
    BaseClass *object_class;
    BaseClass *string_class;
    BaseClass *map_class;
    BaseClass *range_class;
    BaseClass *list_class;
    BaseClass *null_class;
    BaseClass *bool_class;
    BaseClass *num_class;
    BaseClass *fn_class;
    BaseClass *thread_class;
    MethodNameList all_method_name;
    ObjMap *all_modules;
    ObjThread *curr_thread;

public:
    VM();
    ~VM();

    uint64_t realloc_memory(uint64_t old_size, uint64_t new_size);
    uint64_t alloc_memory(uint64_t new_size);
    void add_object(ObjHeader *obj);
    void remove_object(ObjHeader *obj);

//    int get_index_from_symbol_table(const std::string &name);
    uint64_t get_method_index(const std::string &name);
    char *read_file(const char *fpath);


    // VmResult exec_module(Value *module_name, const char *module_code);
private:
    int obj_cnt;

private:
    VM(const VM &vm) = delete;

    void _build_core();
    ObjModule *_get_module(Value *module_name);
    ObjThread *_load_module(Value *module_name, const char *module_code);
    // void _bind_super_class(BaseClass *sub_class, BaseClass *super_class);
    // uint64_t _define_module_value(ObjModule *obj_module, std::string name, Value *val);
    // void _bind_method(BaseClass *base_class, uint64_t index, method *method_ptr);
    // void _func_bind_class(BaseClass *base_cls, const std::string &method_name, Primitive prim_func);
};

#endif
