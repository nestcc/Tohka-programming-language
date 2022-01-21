/*
 * @Author: Nestcc
 * @Date: 2022-01-15 22:23:17
 * @Discription: 
 */

#ifndef _TOHKA_OPCODE_H_
#define _TOHKA_OPCODE_H_

#define OPCODE_SLOTS(opcode, effect) OPCODE_##opcode,
typedef enum {
#include "vm/opcode.inc"
} OpCode;
#undef OPCODE_SLOTS

#endif // end of _TOHKA_OPCODE_H_
