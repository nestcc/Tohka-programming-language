/*
 * @Author: Zhao Yizhu
 * @Date: 2021-02-25 14:10:12
 * @LastEditors: Nestcc
 * @LastEditTime: 2022-01-24 01:25:51
 * @Description:  < file content >
 */

#include "includes/utils.h"

#include <cstdlib>

#include "includes/common.h"
#include "parser/parser.h"
#include "core/vm.h"

uint64_t ceil_to_square(uint64_t v) {
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

void *mem_manager(VM *vm, void *data, uint64_t old_size, uint64_t new_size) {
    vm->allocated_byte += new_size - old_size;

    if (new_size == 0) {
        free(data);
        return nullptr;
    }
    // return nullptr;
    return realloc(data, new_size);
}

void report_error(void *parser, ErrorType err_type, const char *fmt, ...) {
    char buffer[DEFAULT_BUFFER_SIZE] = "\0";
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buffer, DEFAULT_BUFFER_SIZE, fmt, ap);
    va_end(ap);

    switch (err_type) {
    case ERROR_IO:
    case ERROR_MEM:
        fprintf(stderr, RED "%s:%d" NOCOLOR " In function %s():%s\n", __FILE__, __LINE__, __func__,
                buffer);
        break;
    case ERROR_LEX:
    case ERROR_COMPILE:
        ASSERT(parser != nullptr, "parser is null!");
        fprintf(stderr, RED "%s:%llu" NOCOLOR " \"%s\"\n", ((Parser *)parser)->file,
                ((Parser *)parser)->prev_token->line_no, buffer);
        break;
    case ERROR_RUNTIME:
        fprintf(stderr, RED "%s\n" NOCOLOR, buffer);
        break;

    case ERROR_WARRNING:
        fprintf(stderr, YELLOW "%s:%d > " NOCOLOR "%s\n", __FILE__, __LINE__, buffer);
        return;
    default:
        NOT_REACHED();
    }
    exit(-1);
}
