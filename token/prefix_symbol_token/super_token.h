/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 23:00:43
 * @Discription: 
 */

#ifndef _TOHKA_SUPER_TOKEN_H_
#define _TOHKA_SUPER_TOKEN_H_

#include "token/token.h"

class SuperToken : public Token {
public:
    SuperToken() : Token() { type = TOKEN_SUPER; }

    void nud(CompileUnit *cu, bool can_assign) override;
    void led(CompileUnit *cu, bool can_assign) override {};
    void method_sign(CompileUnit *cu, Signature* signature) override {};
};


#endif // end of _TOHKA_SUPER_TOKEN_H_
