/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 21:31:04
 * @Discription: 
 */

#ifndef _TOHKA_VAR_TOKEN_H_
#define _TOHKA_VAR_TOKEN_H_

#include "token/bp_none_token/bp_none_token.h"

class VarToken : public BpNoneToken {
public:
    VarToken() : BpNoneToken() {
        type = TOKEN_VAR;
        keyword = "var";
    }
};

#endif // end of _TOHKA_VAR_TOKEN_H_
