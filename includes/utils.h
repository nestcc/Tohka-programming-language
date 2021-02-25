/*
 * @Author: Zhao Yizhu
 * @Date: 2021-02-25 10:57:56
 * @LastEditors: Zhao Yizhu
 * @LastEditTime: 2021-02-25 14:12:14
 * @Description:  < file content > 
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include "common.h"

/**
 * @description: Manage memory
 * @param {VM} *vm
 * @param {void} *ptr
 * @param {uint32_t} old_size
 * @param {uint32_t} new_size
 * @return {void *}
 */

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

uint32_t ceil_to_power_of(uint32_t v);

typedef struct {
    uint32_t length;
    char *str;
} String;

typedef struct {
    uint32_t length;
    char str[0];
} CharVal;

#define DECLARE_BUFFER_TYPE(type) \
typedef struct { \
    type *data; \
    uint32_t count; \
    uint32_t capacity; \
} type##Buffer; \
void type##BufferInit(type##Buffer *buff); \
void type##BufferFillWrite(VM *vm, type##Buffer *buff, type data, uint32_t fill_cnt); \
void type##BufferAdd(VM *vm, type##Buffer *buff, type data); \
void type##BufferClear(VM *vm, type##Buffer *buff); 


#endif
