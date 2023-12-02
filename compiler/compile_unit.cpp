/*
 * @Author: zhaoyzh
 * @Date: 2022-01-17 14:38:17
 * @Discription:
 */

#include "compiler/compile_unit.h"

#include "compiler/headers.h"

CompileUnit::CompileUnit(Parser *parser, CompileUnit *enclosing_unit, bool is_method) {
    parser->curr_compile_unit = this;
    curr_parser = parser;
    enclosing_unit = enclosing_unit;
    curr_loop = nullptr;
    enclosing_class_bk = nullptr;

    if (enclosing_unit == nullptr) {
        scope_depth = -1;
        local_var_num = 0;
    } else {
        // For methods, the 1st param is "this"
        if (is_method) {
            local_vars[0].name = "this";

        }
        // For normal functions, to keep the same as methods, make the 1st param
        // is NULL
        else {
            local_vars[0].name = "";
        }

        local_vars[0].scope_depth = -1;
        local_vars[0].is_upvalue = false;
        local_var_num = 1;
        scope_depth = 0;

        stack_slot_num = local_var_num;
        obj_func = new ObjFunction(curr_parser->vm, curr_parser->curr_module, local_var_num);
    }
}

int CompileUnit::write_byte(Byte byte) {
#ifdef DEBUG
    obj_func->dbg_info.line_no.push_back(curr_parser->prev_token.line_no);
#endif
    obj_func->instr_stream.push_back(byte);

    return obj_func->instr_stream.size() - 1;
}

void CompileUnit::write_opcode(OpCode opcode) {
    write_byte(opcode);
    stack_slot_num += _op_code_slots_used[opcode];
    if (stack_slot_num > obj_func->max_stk_slot_num) {
        obj_func->max_stk_slot_num = stack_slot_num;
    }
}

void CompileUnit::write_byte_operand(ByteOperand operand) { write_byte(operand); }

void CompileUnit::write_short_operand(ShortOperand operand) {
    write_byte(operand.byte1);
    write_byte(operand.byte2);
}

void CompileUnit::write_opcode_byte_operand(OpCode opcode, ByteOperand byte_operand) {
    write_opcode(opcode);
    write_byte_operand(byte_operand);
}

void CompileUnit::write_opcode_short_operand(OpCode opcode, ShortOperand short_operand) {
    write_opcode(opcode);
    write_short_operand(short_operand);
}

void CompileUnit::compile_program() { return; }

uint64_t CompileUnit::add_constant(Value *constant) {
    obj_func->constants.buff_add(*constant);
    return obj_func->constants.size() - 1;
}

void CompileUnit::emit_load_constant(Value *value) {
    uint64_t index = add_constant(value);
    write_opcode_short_operand(OPCODE_LOAD_CONSTANT, ShortOperand(index));
}

void CompileUnit::literal(CompileUnit *cu, bool can_assign UNUSED) {
    cu->emit_load_constant(cu->curr_parser->prev_token->value);
}

void CompileUnit::expression(SymbolBindRule::BindPower bp) {
    DenotationFunc nud ;
}
