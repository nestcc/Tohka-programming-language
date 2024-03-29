/*
 * @Author: Nestcc
 * @Date: 2021-04-27 09:39:53
 * @LastEditors: Nestcc
 * @LastEditTime: 2022-01-21 16:50:13
 * @Description:  < file content >
 */

#ifndef _LOOP_H_
#define _LOOP_H_

#include "compiler/headers.h"

class Loop {
    uint64_t cond_start_index;
    uint64_t body_start_index;
    uint64_t scope_depth;
    uint64_t exit_index;
    Loop *enclosing_loop;
};

#endif
