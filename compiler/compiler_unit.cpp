/*
 * @Author: zhaoyzh
 * @Date: 2022-01-17 14:38:17
 * @Discription:
 */

#include "compiler/compiler_unit.h"

#include "compiler/headers.h"

CompilerUnit::CompilerUnit(Parser *parser, CompilerUnit *enclosing_unit, bool is_method) {
    parser->curr_compile_unit = this;
    _curr_parser = parser;
    _enclosing_unit = enclosing_unit;
    _curr_loop = nullptr;
    _enclosing_class_bk = nullptr;

    if (enclosing_unit == nullptr) {
        _scope_depth = -1;
        _local_var_num = 0;
    } else {
        // For methods, the 1st param is "this"
        if (is_method) {
            _local_vars[0].name = "this";

        }
        // For normal functions, to keep the same as methods, make the 1st param
        // is NULL
        else {
            _local_vars[0].name = "";
        }

        _local_vars[0].scope_depth = -1;
        _local_vars[0].is_upvalue = false;
        _local_var_num = 1;
        _scope_depth = 0;

        _stack_slot_num = _local_var_num;
        _obj_func = new ObjFunction(_curr_parser->vm, _curr_parser->curr_module, _local_var_num);
    }
}

int CompilerUnit::write_byte(Byte byte) {
#ifdef DEBUG
    _obj_func->dbg_info.line_no.push_back(_curr_parser->prev_token.line_no);
#endif
    _obj_func->instr_stream.push_back(byte);

    return _obj_func->instr_stream.size() - 1;
}

void CompilerUnit::write_op_code(OpCode opcode) {
    write_byte(opcode);
    _stack_slot_num += _op_code_slots_used[opcode];
    if (_stack_slot_num > _obj_func->max_stk_slot_num) {
        _obj_func->max_stk_slot_num = _stack_slot_num;
    }
}

void CompilerUnit::write_byte_operand(ByteOperand operand) { write_byte(operand); }

void CompilerUnit::write_short_operand(ShortOperand operand) {
    write_byte(operand.byte1);
    write_byte(operand.byte2);
}

void CompilerUnit::write_opcode_byte_operand(OpCode opcode, ByteOperand byte_operand) {
    write_op_code(opcode);
    write_byte_operand(byte_operand);
}

void CompilerUnit::write_opcode_short_operand(OpCode opcode, ShortOperand short_operand) {
    write_op_code(opcode);
    write_short_operand(short_operand);
}

void CompilerUnit::compile_program() { return; }
