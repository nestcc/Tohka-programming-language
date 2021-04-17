/*
 * @Author: nestcc 
 * @Date: 2021/4/6 18:36
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/6 18:36
 * @Discription: 
 */

#include <vector>
#include "ObjList.h"
#include "Value.h"
#include "../vm/vm.h"

ObjList::ObjList(VM *vm, int size_n) :
ObjHeader(vm, OT_LIST, vm -> list_class){
    elements.reserve(size_n);
    uint64_t allocated = vm -> alloca_memory(sizeof(Value) * size_n + sizeof(*this));
    LOG_INFO(" allocated list object by %lluB \n", allocated);
}

Value &ObjList::operator[](uint64_t index) {
    return elements[index];
}

Value ObjList::remove_element(VM *vm, uint64_t index) {
    Value ret = elements[index];
    elements.erase(elements.begin() + (long) index);
    return ret;
}

void ObjList::insert_element(VM *vm, uint64_t index, Value value) {
    uint64_t old_size = elements.capacity() * sizeof(Value);
    elements.insert(elements.begin() + (long) index, value);
    uint64_t new_size = elements.capacity() * sizeof(Value);
    vm -> realloca_memory(old_size, new_size);
}

void ObjList::resize(VM *vm, uint64_t new_size) {
    uint64_t o_size = elements.capacity() * sizeof(Value);
    elements.reserve(new_size);
    uint64_t n_size = elements.capacity() * sizeof(Value);
    vm -> realloca_memory(o_size, n_size);
}
