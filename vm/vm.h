/*
 * @Author: Nestcc
 * @Date: 2021-03-12 16:13:34
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-24 21:57:13
 * @Description:  < file content > 
 */


#ifndef _VM_H_
#define _VM_H_

// #include "../includes/common.h"
// #include "../includes/utils.h"
#include "../object/headers.h"
//#include "../object/ObjMap.h"
#include <vector>
#include <string>

class ObjHeader;
class BaseClass;
class ObjMap;

class VM {
public:
    BaseClass *str_cls;
    BaseClass *func_cls;
    BaseClass *class_class;
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

    uint64_t allocated_byte;
    Parser *curr_parser;

    ObjHeader *all_objects;
    std::vector<std::string> all_methods;
//    ObjMap *all_modules;

    static VM *getInstance();

    uint64_t realloca_memory(uint64_t old_size, uint64_t new_size);

    uint64_t alloca_memory(uint64_t new_size);

    void add_object(ObjHeader *obj);

    void remove_object(ObjHeader *obj);

private:
    VM();
    VM(const VM &vm) = delete;
    ~VM() = default;
    static VM *instance;
    int obj_cnt;
};

#endif
