/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 23:05:59
 * @Discription: 
 */

#ifndef _TOHKA_LEFT_BRACE_TOKEN_H_
#define _TOHKA_LEFT_BRACE_TOKEN_H_

#include "token/token.h"

class LeftBraceToken : public Token {
public:
    LeftBraceToken() : Token() { type = TOKEN_LEFT_BRACE; }

    void nud(CompileUnit *cu, bool can_assign) override;
    void led(CompileUnit *cu, bool can_assign) override {};
    void method_sign(CompileUnit *cu, Signature* signature) override {};
};


#endif // end of _TOHKA_LEFT_BRACE_TOKEN_H_
