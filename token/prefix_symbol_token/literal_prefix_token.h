/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 22:22:53
 * @Discription: 
 */

#ifndef _TOHKA_LITERAL_PREFIX_TOKEN_H_
#define _TOHKA_LITERAL_PREFIX_TOKEN_H_

#include "token/token.h"
#include "compiler/compile_unit.h"

class LiteralPrefixToken : public Token {
public:
    LiteralPrefixToken(TokenType token_type) : Token() { type = token_type; }

    void nud(CompileUnit *cu, bool can_assign) override;
    void led(CompileUnit *cu, bool can_assign) override {};
    void method_sign(CompileUnit *cu, Signature* signature) override {};
};


#endif // end of _TOHKA_LITERAL_PREFIX_TOKEN_H_
