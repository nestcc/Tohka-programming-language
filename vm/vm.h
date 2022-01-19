/*
 * @Author: Nestcc
 * @Date: 2021-03-12 16:13:34
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-05-08 15:33:30
 * @Description:  < file content > 
 */

#ifndef _VM_H_
#define _VM_H_

#include "../object/headers.h"
#include <vector>
#include <string>

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

    static VM *getInstance();

    uint64_t realloc_memory(uint64_t old_size, uint64_t new_size);

    uint64_t alloc_memory(uint64_t new_size);

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
