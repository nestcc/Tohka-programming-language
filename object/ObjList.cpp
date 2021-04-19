/*
 * @Author: nestcc 
 * @Date: 2021/4/6 18:36
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/6 18:36
 * @Discription: 
 */

#include <vector>
#include <cerrno>
#include "ObjList.h"
#include "Value.h"

ObjList::ObjList(VM *vm, int size_n) :
ObjHeader(vm, OT_LIST, vm -> list_class){
    elements.reserve(size_n);
    uint64_t allocated = vm -> alloca_memory(sizeof(Value) * size_n + sizeof(*this));
    LOG_INFO(" allocated list object by %lluB \n", allocated);
}

Value &ObjList::operator[](uint64_t index) {
    if (index > elements.size()) {
        errno = ERROR_MEM;
        MEM_ERROR("index out of range");
        exit(EXIT_FAILURE);
    }
    return elements[index];
}

Value ObjList::remove_element(VM *vm, uint64_t index) {
    if (index >= elements.size()) {
        errno = ERROR_MEM;
        MEM_ERROR("index out of range");
        exit(EXIT_FAILURE);
    }
    Value ret = elements[index];
    elements.erase(elements.begin() + (long) index);
    elements. adjust_size(vm);
    return ret;
}

void ObjList::insert_element(VM *vm, uint64_t index, Value value) {
    if (index > elements.size()) {
        errno = ERROR_MEM;
        MEM_ERROR("index out of range");
        exit(EXIT_FAILURE);
    }
    elements.insert(elements.begin() + (long) index, value);
    elements. adjust_size(vm);
}

void ObjList::resize(VM *vm, uint64_t new_size) {
    elements.reserve(new_size);
    elements. adjust_size(vm);
}
