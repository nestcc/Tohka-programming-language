/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 21:39:31
 * @Discription: 
 */

#ifndef _TOHKA_WHILE_TOKEN_H_
#define _TOHKA_WHILE_TOKEN_H_

#include "token/bp_none_token/bp_none_token.h"

class WhileToken : public BpNoneToken {
public:
    WhileToken() : BpNoneToken() {
        type = TOKEN_WHILE;
        keyword = "while";
    }
};

#endif // end of _TOHKA_WHILE_TOKEN_H_
