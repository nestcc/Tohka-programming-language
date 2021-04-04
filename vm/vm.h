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
    size_t allocated_byte;
    Parser *curr_parser;
    ObjHeader *all_objects;
    static VM *getInstance();

    void realloca_memory(size_t old_size, size_t new_size);

private:
    static VM *instance;
    VM();
    VM(const VM &vm) = delete;
    ~VM() = default;
};

#endif
