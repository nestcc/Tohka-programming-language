/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 19:05:49
 * @Discription: 
 */

#ifndef _TOHKA_OPERATOR_H_
#define _TOHKA_OPERATOR_H_

#include "symbol_bind_rule.h"

class Operator : SymbolBindRule {
    void expression(CompileUnit *cu, BindPower bp);
};


#endif // end of _TOHKA_OPERATOR_H_
