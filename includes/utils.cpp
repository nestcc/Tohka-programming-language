/*
 * @Author: Zhao Yizhu
 * @Date: 2021-02-25 14:10:12
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-03-12 16:54:36
 * @Description:  < file content >
 */

#include <iostream>
#include <cinttypes>
#include <cstdlib>

#include "common.h"
#include "utils.h"

uint32_t ceil_to_squar(uint32_t v) {
    v += (v == 0);
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

void *mem_manager(VM *vm, void *data, uint32_t old_size, uint32_t new_size) {

    // vm -> allocatedBytes += new_size - old_size;

    if (new_size == 0) {
        free(data);
        return nullptr;
    }

    return realloc(data, new_size);
}

void symbol_table_clear(VM *vm, SymbolTable *buffer) {
    for (uint32_t i = 0; i < buffer -> count; i += 1) {
        mem_manager(vm, buffer -> datas[i].str, 0, 0);
    }
    buffer -> buffClear(vm);
    return;
}

void report_error(void *parser, ErrorType err_type, const char *fmt, ...) {
    char buffer[DEFAULT_BUfFER_SIZE] = "\0";
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buffer, DEFAULT_BUfFER_SIZE, fmt, ap);
    va_end(ap);

    switch (err_type) {
    case ERROR_IO:
    case ERROR_MEM:
        fprintf(stderr, "%s:%d In function %s():%s\n",
            __FILE__, __LINE__, __func__, buffer);
        break;
    case ERROR_LEX:
    case ERROR_COMPILE:
        ASSERT(parser != nullptr, "parser is null!");
        // fprintf(stderr, "%s:%d \"%s\"\n", ((Parser *) parser)->file,
        //     ((Parser *) parser)->preToken.lineNo, buffer);
        break;
    case ERROR_RUNTIME:
        fprintf(stderr, "%s\n", buffer);
        break;
    default:
        NOT_REACHED();
    }
    exit(1);
}
