/*
 * @Author: Nestcc
 * @Date: 2021-04-27 17:48:13
 * @Description:  < file content >
 */

#ifndef _COMPILERUNIT_H_
#define _COMPILERUNIT_H_

#include "compiler/headers.h"
#include "compiler/local_var.h"
#include "compiler/upvalue.h"
#include "compiler/loop.h"
#include "object/obj_function.h"
#include "parser/parser.h"
#include "vm/opcode.h"
#include "vm/operand.h"


class CompilerUnit {
public:
    ObjFunction *_obj_func;      // 所编译的函数
    LocalVar _local_vars[MAX_LOCAL_VAR_NUM]; // 作用域中允许的局部变量的个量上限
    uint64_t _local_var_num;     // 已分配的局部变量个数
    Upvalue _upvalues[MAX_UPVALUE_NUM];      // 记录本层函数所引用的upvalue
    uint64_t _scope_depth;       // 此项表示当前正在编译的代码所处的作用域,
    uint64_t _stack_slot_num;    // 当前使用的slot个数
    Loop *_curr_loop;            // 当前正在编译的循环层
    ClassBookKeep *_enclosing_class_bk;  // 当前正编译的类的编译信息
    CompilerUnit *_enclosing_unit;   // 包含此编译单元的编译单元,即直接外层
    Parser *_curr_parser;        // 当前parser

    //把opcode定义到数组opCodeSlotsUsed中
#define OPCODE_SLOTS(opCode, effect) effect,
    const int _op_code_slots_used[OPCODE_NUM] = {
#include "vm/opcode.inc"
    };
#undef OPCODE_SLOTS

public:
    CompilerUnit() = default;
    CompilerUnit(Parser *parser, CompilerUnit *enclosing_unit, bool is_method);

    void compile_program();

private:
    int write_byte(Byte byte);

    void write_op_code(OpCode opcode);

    void write_byte_operand(ByteOperand operand);
    void write_short_operand(ShortOperand operand);

    void write_opcode_byte_operand(OpCode opcode, ByteOperand byte_operand);
    void write_opcode_short_operand(OpCode opcode, ShortOperand short_operand);
};

#endif
