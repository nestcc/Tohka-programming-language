/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 20:54:44
 * @Discription: 
 */

#ifndef _TOHKA_LEFT_PAREN_TOKEN_H_
#define _TOHKA_LEFT_PAREN_TOKEN_H_

#include "token/token.h"

class LeftParenToken : public Token {
public:
    LeftParenToken() : Token() { type = TOKEN_LEFT_PAREN; };

    void nud(CompileUnit *cu, bool can_assign) override;
    void led(CompileUnit *cu, bool can_assign) override {};
    void method_sign(CompileUnit *cu, Signature* signature) override {};
};


#endif // end of _TOHKA_LEFT_PAREN_TOKEN_H_
