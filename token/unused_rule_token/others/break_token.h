/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 21:41:31
 * @Discription: 
 */

#ifndef _TOHKA_BREAK_TOKEN_H_
#define _TOHKA_BREAK_TOKEN_H_

#include "token/bp_none_token/bp_none_token.h"

class BreakToken : public BpNoneToken {
public:
    BreakToken() : BpNoneToken() {
        type = TOKEN_BREAK;
        keyword = "BREAK";
    }
};

#endif // end of _TOHKA_BREAK_TOKEN_H_
