/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 22:54:31
 * @Discription: 
 */

#ifndef _TOHKA_THIS_TOKEN_H_
#define _TOHKA_THIS_TOKEN_H_

#include "token/token.h"

class ThisToken : public Token {
public:
    ThisToken() : Token() { type = TOKEN_THIS; }

    void nud(CompileUnit *cu, bool can_assign) override;
    void led(CompileUnit *cu, bool can_assign) override {};
    void method_sign(CompileUnit *cu, Signature* signature) override {};
};


#endif // end of _TOHKA_THIS_TOKEN_H_
