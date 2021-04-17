/*
 * @Author: Nestcc
 * @Date: 2021-03-12 16:19:21
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-03-12 16:20:36
 * @Description:  < file content > 
 */

#include <cstdint>
#include <string>
#include "vm.h"

VM::VM() : allocated_byte(0), curr_parser(nullptr), all_objects(nullptr) {}

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
