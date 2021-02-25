/*
 * @Author: Zhao Yizhu
 * @Date: 2021-02-25 13:55:51
 * @LastEditors: Zhao Yizhu
 * @LastEditTime: 2021-02-25 15:34:22
 * @Description:  < file content > 
 */

#ifndef _UTILS_CPP_H_
#define _UTILS_CPP_H_

#include "common.h"

void *mem_manager(VM *vm, void *ptr, uint32_t old_size, uint32_t new_size);

#define ALLOCATE(vm_ptr, type) \
(type *) men_manager(vm_ptr, NULL, 0, sizeof(type));

#define ALLOCATE_EXTRA(vm_ptr, type, extra_size) \
(type *) mem_manager(vm_ptr, NULL, 0, sizeof(type) + extra_size);

#define ALLOCATE_ARRAY(vm_ptr, type, capacity) \
(type *) mem_manager(vm_ptr, NULL, 0, sizeof(typr) * capacity);

#define DESTORY_ARRAY(vm_ptr, arr_ptr, capacity) \
mem_manager(vm_ptr, arr_ptr, sizeof(arr_ptr[0]) * capacity, 0);

#define DESTORY(vm_ptr, mem_ptr) \
mem_manager(vm_ptr, mem_ptr, 0, 0);

uint32_t ceil_to_squar(uint32_t v);

struct STRING {
    uint32_t length;
    char *str;
};

struct CharVal {
    uint32_t length;
    char str[0];
};

template<typename Type>
class MemBuffer {
public:
    Type *data;
    
    uint32_t count;

    uint32_t capacity;
    
    MemBuffer() : data(nullptr), count(0) {} ;

    void fillWirte(VM *vm, Type &data, uint32_t fill_cnt);

    void buffAdd(VM *vm, Type &data);

    void buffClear(VM *vm);

};

#define SymbolTable MemBuffer<STRING>


typedef uint8_t Byte;
typedef char Char;
typedef int Int;

enum ErrType {
    ERROR_IO,
    ERROR_MEM,
    ERROR_LEX,
    ERROR_COMPILE,
    ERROR_RUNTIME,
};

void symbol_table_clear(VM *vm, SymbolTable *buffer);

void report_error(void *parser, ErrType err_type, const char *fmt, ...);

#define IO_ERROR(...) \
report_error(NULL, ErrType::ERROR_IO, __VA_ARGS__);

#define MEM_ERROR(...) \
report_error(NULL, ErrType::ERROR_MEM, __VA_ARGS__);

#define LEX_ERROR(parser, ...) \
report_error(parser, ErrType::ERROR_LEX, __VA_ARGS__);

#define COMPILE_ERROR(parser, ...) \
report_error(parser, ErrType::ERROR_COMPILE, __VA_ARGS__);

#define RUNTIME_ERROR(parser, ...) \
report_error(parser, ErrType::ERROR_RUNTIME, __VA_ARGS__);

#define DEFAULT_BUfFER_SIZE 512

#endif