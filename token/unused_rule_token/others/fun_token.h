/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 21:32:03
 * @Discription: 
 */

#ifndef _TOHKA_FUN_TOKEN_H_
#define _TOHKA_FUN_TOKEN_H_

#include "token/bp_none_token/bp_none_token.h"

class FunToken : public BpNoneToken {
public:
    FunToken() : BpNoneToken() {
        type = TOKEN_FUNC;
        keyword = "func";
    }
};

#endif // end of _TOHKA_FUN_TOKEN_H_
