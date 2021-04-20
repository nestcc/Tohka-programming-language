/*
 * @Author: Nestcc
 * @Date: 2021-03-12 16:13:34
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-03-16 10:21:16
 * @Description:  < file content > 
 */


#ifndef _VM_H_
#define _VM_H_

#include "../includes/common.h"
//#include "../object/ObjectHeader.h"
//#include "../object/BaseClass.h"

class ObjHeader;
class BaseClass;

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
