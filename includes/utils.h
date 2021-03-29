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

#ifdef NDEBUG
#define LOG_INFO(info, ...)
#else
#define LOG_INFO(...) \
printf( BLUE "[%s : %d] " NOCOLOR, __FILE__, __LINE__); \
printf(__VA_ARGS__);
#endif

void *mem_manager(VM *vm, void *ptr, uint32_t old_size, uint32_t new_size);

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

uint32_t ceil_to_squar(uint32_t v);

//struct STRING {
//    uint32_t length;
//    char *str;
//};
//
//struct CharVal {
//    uint32_t length;
//    char str[0];
//};

template<typename Type>
class MemBuffer {
public:
    Type *datas;
    
    uint32_t count;

    uint32_t capacity;

//    VM *vm;
    
    MemBuffer() : datas(nullptr), count(0), capacity(0) {};

    void fillWirte(VM *vm, Type data, uint32_t fill_cnt) {
        uint32_t new_cnt = count + fill_cnt;
        if (new_cnt > capacity) {
            size_t old_size = capacity * sizeof(Type);
            capacity = ceil_to_squar(new_cnt);
            size_t new_size = capacity * sizeof(Type);
            ASSERT(new_size > old_size, RED "> faint...memory allocated.\n" NOCOLOR);
            datas = (Type *) mem_manager(vm, (void *) datas, old_size, new_size);
        }

        for (uint32_t cnt = 0; cnt < fill_cnt; cnt += 1) {
            datas[count++] = data;
        }
        
        return ;
    };

    void buffAdd(VM *vm, Type data) {
        fillWirte(vm, data, 1);
        return ;
    };

    void buffClear(VM *vm) {
        size_t curr_size = count * sizeof(Type);
        mem_manager(vm, datas, curr_size, 0);
        datas = nullptr; count = 0; capacity = 0;
        return ;
    }

};

typedef uint8_t Byte;
typedef char Char;
typedef int Int;

typedef MemBuffer<std::string> SymbolTable;
typedef MemBuffer<uint8_t> ByteBuffer;


enum ErrorType {
    ERROR_IO,
    ERROR_MEM,
    ERROR_LEX,
    ERROR_COMPILE,
    ERROR_RUNTIME,
};

void symbol_table_clear(VM *vm, SymbolTable *buffer);

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