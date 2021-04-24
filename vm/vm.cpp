/*
 * @Author: Nestcc
 * @Date: 2021-03-12 16:19:21
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-24 21:58:45
 * @Description:  < file content > 
 */

#include <cstdint>
// #include <string>
#include "../object/ObjectHeader.h"
#include "../object/ObjMap.h"
#include "vm.h"

VM::VM() : allocated_byte(0), curr_parser(nullptr), all_objects(nullptr), obj_cnt(0) {}

VM *VM::getInstance() {
    if (instance == nullptr) {
        instance = new VM();
    }
    return instance;
}

VM *VM::instance = nullptr;

uint64_t VM::realloca_memory(uint64_t old_size, uint64_t new_size) {
    allocated_byte += (new_size - old_size);
    return new_size - old_size;
}

uint64_t VM::alloca_memory(uint64_t new_size) {
    allocated_byte += new_size;
    return new_size;
}

void VM::add_object(ObjHeader *obj) {
    if (all_objects == nullptr) {
        obj -> next = obj -> prev = obj;
        all_objects = obj;
        obj_cnt += 1;
        return;
    }
    obj -> prev = all_objects -> prev;
    obj -> next = all_objects;
    obj -> prev -> next = obj;
    obj -> next -> prev = obj;
    all_objects = obj;
    obj_cnt += 1;
}

void VM::remove_object(ObjHeader *obj) {
    if (obj_cnt == 1) {
        MEM_ERROR("object () not in vm.", obj -> type);
        return;
    }
    if (obj_cnt == 1) {
        all_objects = nullptr;
        obj_cnt = 0;
        return;
    }
    if (obj == all_objects) {
        all_objects = all_objects -> next;
    }
    obj -> prev -> next = obj -> next;
    obj -> next -> prev = obj -> prev;
    obj -> next = obj -> prev = nullptr;
    obj_cnt -= 1;
}
