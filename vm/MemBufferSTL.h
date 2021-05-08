/*
 * @Author: Nestcc
 * @Date: 2021-04-24 21:41:50
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-05-08 16:29:46
 * @Description:  < file content > 
 */

#ifndef _MEMALLOCATORSTL_H_
#define _MEMALLOCATORSTL_H_

#include <vector>
#include <string>
#include "vm.h"

template<typename Type>
class MemBufferSTL : public std::vector<Type> {
public:
    VM *vm = nullptr;
    uint64_t curr_size;

    MemBufferSTL() : std::vector<Type>(0), vm(nullptr) , curr_size(0) {};

    MemBufferSTL(VM *vm, uint64_t size) :
        std::vector<Type>(size),
        vm(vm),
        curr_size(size) {};

    MemBufferSTL(const MemBufferSTL<Type> &other) = delete;
    MemBufferSTL &operator=(const MemBufferSTL<Type> &other) = delete;

    MemBufferSTL(VM *vm, uint64_t size, const Type &t) :
        std::vector<Type>(size, t), 
        vm(vm),
        curr_size(size) {};

    ~MemBufferSTL() {
        if (vm != nullptr)
            buff_clear();
    }

    uint64_t total_size() {
        return std::vector<Type>::capacity() * sizeof(Type);
    }

    void adjust_size() {
        uint64_t new_size = total_size();
        vm -> realloca_memory(curr_size, new_size);
        curr_size = new_size;
    }

    void fill_wirte(Type data, uint64_t fill_cnt) {
        for (uint64_t i = 0; i < fill_cnt; i += 1) {
            this -> push_back(data);
        }
        adjust_size();
    };

    void buff_add(Type data) {
        fill_wirte(data, 1);
    };

    void buff_clear() {
        std::vector<Type>::clear();
        adjust_size();
    }

};

typedef MemBufferSTL<std::string> SymbolTable;
typedef MemBufferSTL<uint8_t> ByteBuffer;

#endif
