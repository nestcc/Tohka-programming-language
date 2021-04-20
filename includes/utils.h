/*
 * @Author: Zhao Yizhu
 * @Date: 2021-02-25 13:55:51
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-03-29 16:11:23
 * @Description:  < file content > 
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdarg.h>
#include <vector>
#include <string>
#include "../vm/vm.h"

#ifdef NDEBUG
#define LOG_INFO(...)
#else
#define LOG_INFO(...) \
{ printf( BLUE "[%s : %d] " NOCOLOR, __FILE__, __LINE__); printf(__VA_ARGS__); }
#endif

void *mem_manager(VM *vm, void *ptr, uint64_t old_size, uint64_t new_size);

#define ALLOCATE(vm_ptr, type) \
(type *) mem_manager(vm_ptr, NULL, 0, sizeof(type));

#define ALLOCATE_EXTRA(vm_ptr, type, extra_size) \
(type *) mem_manager(vm_ptr, NULL, 0, sizeof(type) + extra_size);

#define ALLOCATE_ARRAY(vm_ptr, type, capacity) \
(type *) mem_manager(vm_ptr, NULL, 0, sizeof(typr) * capacity);

#define DESTORY_ARRAY(vm_ptr, arr_ptr, capacity) \
mem_manager(vm_ptr, arr_ptr, sizeof(arr_ptr[0]) * capacity, 0);

#define DESTORY(vm_ptr, mem_ptr) \
mem_manager(vm_ptr, mem_ptr, 0, 0);

//uint64_t ceil_to_squar(uint64_t v);

template<typename Type>
class MemBufferSTL : public std::vector<Type> {
public:
    VM *vm = nullptr;
    uint64_t curr_size;

    MemBufferSTL() : vm(VM::getInstance()) , curr_size(0) {};

//    MemBuffer(VM *vm) : vm(vm) {};

    ~MemBufferSTL() {
        buff_clear(vm);
    }

    uint64_t total_size() {
        return std::vector<Type>::capacity() * sizeof(Type);
    }

    void adjust_size(VM *vm) {
        uint64_t new_size = total_size();
        vm -> realloca_memory(curr_size, new_size);
        curr_size = new_size;
    }

    void fill_wirte(VM *vm, Type data, uint64_t fill_cnt) {
        for (uint64_t i = 0; i < fill_cnt; i += 1) {
            this -> push_back(data);
        }
        adjust_size(vm);
    };

    void buff_add(VM *vm, Type data) {
        fill_wirte(vm, data, 1);
    };

    void buff_clear(VM *vm) {
        std::vector<Type>::clear();
        adjust_size(vm);
    }

};

typedef uint8_t Byte;
typedef char Char;
typedef int Int;

//template<typename Type>
//typedef MemBufferSTL<Type> MemBuffer;

typedef MemBufferSTL<std::string> SymbolTable;
typedef MemBufferSTL<uint8_t> ByteBuffer;


enum ErrorType {
    ERROR_IO,
    ERROR_MEM,
    ERROR_LEX,
    ERROR_COMPILE,
    ERROR_RUNTIME,
};

//void symbol_table_clear(VM *vm, SymbolTable *buffer);

void report_error(void *parser, ErrorType err_type, const char *fmt, ...);

#define IO_ERROR(...) \
report_error(NULL, ERROR_IO, __VA_ARGS__);

#define MEM_ERROR(...) \
report_error(NULL, ERROR_MEM, __VA_ARGS__);

#define LEX_ERROR(parser, ...) \
report_error(parser, ERROR_LEX, __VA_ARGS__);

#define COMPILE_ERROR(parser, ...) \
report_error(parser, ERROR_COMPILE, __VA_ARGS__);

#define RUNTIME_ERROR(parser, ...) \
report_error(parser, ERROR_RUNTIME, __VA_ARGS__);

#define DEFAULT_BUfFER_SIZE 512

#endif