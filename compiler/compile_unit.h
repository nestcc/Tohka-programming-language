/*
 * @Author: Nestcc
 * @Date: 2021-04-27 17:48:13
 * @Description:  < file content >
 */

#ifndef _COMPILERUNIT_H_
#define _COMPILERUNIT_H_

// #include "compiler/headers.h"
#include "object/obj_function.h"
#include "compiler/local_var.h"
#include "compiler/loop.h"
#include "compiler/upvalue.h"
#include "symbol/symbol_bind_rule.h"
#include "parser/parser.h"
#include "core/opcode.h"
#include "core/operand.h"

class CompileUnit {
public:
    ObjFunction *obj_func;                   // 所编译的函数
    LocalVar local_vars[MAX_LOCAL_VAR_NUM];  // 作用域中允许的局部变量的个量上限
    uint64_t local_var_num;                  // 已分配的局部变量个数
    Upvalue upvalues[MAX_UPVALUE_NUM];       // 记录本层函数所引用的upvalue
    uint64_t scope_depth;     // 此项表示当前正在编译的代码所处的作用域,
    uint64_t stack_slot_num;  // 当前使用的slot个数
    Loop *curr_loop;          // 当前正在编译的循环层
    ClassBookKeep *enclosing_class_bk;  // 当前正编译的类的编译信息
    CompileUnit *enclosing_unit;       // 包含此编译单元的编译单元,即直接外层
    Parser *curr_parser;                // 当前parser

    //把opcode定义到数组opCodeSlotsUsed中
#define OPCODE_SLOTS(opCode, effect) effect,
    const int _op_code_slots_used[OPCODE_NUM] = {
#include "core/opcode.inc"

    };
#undef OPCODE_SLOTS

public:
    CompileUnit() = default;
    CompileUnit(Parser *parser, CompileUnit *enclosing_unit, bool is_method);

    void compile_program();
    uint64_t add_constant(Value *constant);
    void emit_load_constant(Value *value);
    static void literal(CompileUnit *cu, bool can_assign UNUSED);

//private:
//    SymbolBindRule rules[3] = {{"__TOKEN_INVALID__", SymbolBindRule::BP_NONE, nullptr, nullptr, nullptr},
//                               {"__TOKEN_NUM__", SymbolBindRule::BP_NONE, literal, nullptr, nullptr}};

    int write_byte(Byte byte);

    void write_opcode(OpCode opcode);

    void write_byte_operand(ByteOperand operand);
    void write_short_operand(ShortOperand operand);

    void write_opcode_byte_operand(OpCode opcode, ByteOperand byte_operand);
    void write_opcode_short_operand(OpCode opcode, ShortOperand short_operand);

    void expression(SymbolBindRule::BindPower bp);
};

#endif
