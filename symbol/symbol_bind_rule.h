/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 16:35:19
 * @Discription: 
 */

#ifndef _TOHKA_SYMBOL_BIND_RULE_H_
#define _TOHKA_SYMBOL_BIND_RULE_H_

#include <string>
#include "compiler/headers.h"

class SymbolBindRule {
public:
    enum BindPower {
        BP_NONE,      // No bind power
        BP_LOWEST,    // Lowest
        BP_ASSIGN,    // =
        BP_CONDITION,   // ?:
        BP_LOGIC_OR,    // ||
        BP_LOGIC_AND,   // &&
        BP_EQUAL,      // == !=
        BP_IS,        // is
        BP_CMP,       // < > <= >=
        BP_BIT_OR,    // |
        BP_BIT_AND,   // &
        BP_BIT_SHIFT, // << >>
        BP_RANGE,       // ..
        BP_TERM,      // + -
        BP_FACTOR,      // * / %
        BP_UNARY,    // - ! ~
        BP_CALL,     // . () []
        BP_HIGHEST
    };

    std::string id;

    BindPower lbp; // left bind power
//    DenotationFunc nud; // Methods called by tokens that don't care about left operand
//    DenotationFunc led; // Methods called by tokens that concern about left operand

    virtual void nud(CompilerUnit *cu, bool can_assign) = 0; // Methods called by tokens that don't care about left operand
    virtual void led(CompilerUnit *cu, bool can_assign) = 0; // Methods called by tokens that concern about left operand
    virtual void method_sign(CompilerUnit *cu, Signature *signature) = 0;

    void expression(CompilerUnit *cu, BindPower bp);
};

#endif // end of _TOHKA_SYMBOL_BIND_RULE_H_
