/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 22:48:46
 * @Discription: 
 */

#include "null_token.h"
#include "compiler/compile_unit.h"

void NullToken::nud(CompileUnit *cu, bool can_assign) {
    cu->write_opcode(OPCODE_PUSH_NULL);
}
