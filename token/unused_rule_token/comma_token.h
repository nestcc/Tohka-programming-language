/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 20:45:13
 * @Discription: 
 */

#ifndef _TOHKA_COMMA_TOKEN_H_
#define _TOHKA_COMMA_TOKEN_H_

#include "token/unused_rule_token/unused_rule_token.h"

class CommaToken : public UnusedRuleToken {
public:
    CommaToken() : UnusedRuleToken() { type = TOKEN_COMMA; };
};


#endif // end of _TOHKA_COMMA_TOKEN_H_
