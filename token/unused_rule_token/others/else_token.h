/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 21:38:09
 * @Discription: 
 */

#ifndef _TOHKA_ELSE_TOKEN_H_
#define _TOHKA_ELSE_TOKEN_H_

#include "token/bp_none_token/bp_none_token.h"

class ElseToken : public BpNoneToken {
public:
    ElseToken() : BpNoneToken() {
        type = TOKEN_ELSE;
        keyword = "else";
    }
};

#endif // end of _TOHKA_ELSE_TOKEN_H_
