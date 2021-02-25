/*
 * @Author: Zhao Yizhu
 * @Date: 2021-02-25 10:36:52
 * @LastEditors: Zhao Yizhu
 * @LastEditTime: 2021-02-25 10:57:01
 * @Description:  Some basic data structures 
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "color.h"

typedef struct _VM VM;
typedef struct _PARSER Parser;
typedef struct _CLASS Class;

#define bool char
#define True 1
#define False 0
#define UNUSED __attribute__((unused))

#ifdef DEBUG
#define LOG_ERROR(condition, errmsg)    \
do {    \
    if (!condition) {   \
        fprintf(stderr, RED "An error occured!\n" NOCOLOR "%s at : %s,%d:%s()\n",   \
            errmsg, __FILE__, __LINE__, __func__);  \
        abort();    \
    }   \
} while (0);

#else
#define LOG_ERROR(condition, errmsg)
#endif

#define NOT_REACHED()   \
do {    \
    fprintf(stderr, BROWN "Not reached:\n" NOCOLOR "%s,%d:%s()\n",   \
        __FILE__, __LINE__, __func__);  \
} while (0);

#endif
