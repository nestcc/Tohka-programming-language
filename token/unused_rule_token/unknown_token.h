/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 20:21:58
 * @Discription: 
 */

#ifndef _TOHKA_UNKNOWN_TOKEN_H_
#define _TOHKA_UNKNOWN_TOKEN_H_

#include "token/token.h"

class UnknownToken : public Token {
public:
    UnknownToken() : Token() {
        type = TOKEN_UNKNOWN;
    };

    void nud(CompileUnit *cu, bool can_assign);
    void led(CompileUnit *cu, bool can_assign);
    void method_sign(CompileUnit *cu, Signature* signature);
};


#endif // end of _TOHKA_UNKNOWN_TOKEN_H_
