/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 22:22:53
 * @Discription: 
 */

#include "literal_prefix_token.h"

void LiteralPrefixToken::nud(CompileUnit *cu, bool can_assign) {
    cu->emit_load_constant(cu->curr_parser->prev_token->value);
}
