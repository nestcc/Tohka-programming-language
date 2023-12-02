/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 20:50:02
 * @Discription: 
 */

#ifndef _TOHKA_COLON_TOKEN_H_
#define _TOHKA_COLON_TOKEN_H_

#include "token/unused_rule_token/unused_rule_token.h"

class ColonToken : public UnusedRuleToken {
public:
    ColonToken() : UnusedRuleToken() { type = TOKEN_COLON; };
};


#endif // end of _TOHKA_COLON_TOKEN_H_
