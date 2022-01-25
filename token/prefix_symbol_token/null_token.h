/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 22:48:46
 * @Discription: 
 */

#ifndef _TOHKA_NULL_TOKEN_H_
#define _TOHKA_NULL_TOKEN_H_

#include "token/token.h"

class NullToken : public Token {
public:
    NullToken() : Token() { type = TOKEN_NULL; };

    void nud(CompileUnit *cu, bool can_assign) override;
    void led(CompileUnit *cu, bool can_assign) override {};
    void method_sign(CompileUnit *cu, Signature* signature) override {};
};


#endif // end of _TOHKA_NULL_TOKEN_H_
