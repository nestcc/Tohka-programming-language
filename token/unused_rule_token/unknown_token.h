/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 20:21:58
 * @Discription: 
 */

#ifndef _TOHKA_UNKNOWN_TOKEN_H_
#define _TOHKA_UNKNOWN_TOKEN_H_

#include "token/bp_none_token/bp_none_token.h"
#include "parser/parser.h"

class UnknownToken : public BpNoneToken {
public:
    UnknownToken() : BpNoneToken() {
        type = TOKEN_UNKNOWN;
    };
};


#endif // end of _TOHKA_UNKNOWN_TOKEN_H_
