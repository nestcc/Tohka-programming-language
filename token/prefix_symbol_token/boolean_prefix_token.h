/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 22:43:41
 * @Discription: 
 */

#ifndef _TOHKA_BOOLEAN_PREFIX_TOKEN_H_
#define _TOHKA_BOOLEAN_PREFIX_TOKEN_H_

#include "token/token.h"

class BooleanPrefixToken : public Token {
public:
    BooleanPrefixToken(TokenType token_type) : Token() { type = token_type; };

    void nud(CompileUnit *cu, bool can_assign) override;
    void led(CompileUnit *cu, bool can_assign) override {};
    void method_sign(CompileUnit *cu, Signature* signature) override {};
};


#endif // end of _TOHKA_BOOLEAN_PREFIX_TOKEN_H_
