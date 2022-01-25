/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 21:42:35
 * @Discription: 
 */

#ifndef _TOHKA_KEYWORD_TOKEN_H_
#define _TOHKA_KEYWORD_TOKEN_H_

#include <string>
#include "token/unused_rule_token/unused_rule_token.h"

class KeywordToken : public UnusedRuleToken {
public:
    KeywordToken() : UnusedRuleToken() {};
    KeywordToken(const std::string &kw, TokenType token_type) : KeywordToken() {
        keyword = kw;
        type = token_type;
    };
};

#endif // end of _TOHKA_KEYWORD_TOKEN_H_
