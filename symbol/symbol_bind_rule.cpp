/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 19:12:13
 * @Discription: 
 */

#include "symbol/symbol_bind_rule.h"
#include "compiler/compiler_unit.h"

void SymbolBindRule::expression(CompilerUnit *cu, BindPower rbp) {
    cu->_curr_parser->get_next_token();
    nud(cu, rbp<BP_ASSIGN);
//    while (rbp < )
}
