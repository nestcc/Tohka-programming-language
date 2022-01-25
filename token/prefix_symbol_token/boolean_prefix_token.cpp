/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 22:43:41
 * @Discription: 
 */

#include "boolean_prefix_token.h"
#include "compiler/compile_unit.h"
#include "vm/opcode.h"

void BooleanPrefixToken::nud(CompileUnit *cu, bool can_assign) {
    OpCode opcode = cu->curr_parser->prev_token->type == TOKEN_TRUE ? OPCODE_PUSH_TRUE : OPCODE_PUSH_FALSE;
    cu->write_opcode(opcode);
}
