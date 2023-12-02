/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 21:17:21
 * @Discription: 
 */

#ifndef _TOHKA_UNUSED_RULE_TOKEN_H_
#define _TOHKA_UNUSED_RULE_TOKEN_H_

#include "token/token.h"
#include "compiler/compile_unit.h"

class UnusedRuleToken : public Token {
public:
    UnusedRuleToken() : Token() {}

    void nud(CompileUnit *cu, bool can_assign) override {};
    void led(CompileUnit *cu, bool can_assign) override {};
    void method_sign(CompileUnit *cu, Signature* signature) override {};
};


#endif // end of _TOHKA_UNUSED_RULE_TOKEN_H_
