/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 21:37:31
 * @Discription: 
 */

#ifndef _TOHKA_IF_TOKEN_H_
#define _TOHKA_IF_TOKEN_H_

#include "token/bp_none_token/bp_none_token.h"

class IfToken : public BpNoneToken {
public:
    IfToken() : BpNoneToken() {
        type = TOKEN_IF;
        keyword = "if";
    }
};

#endif // end of _TOHKA_IF_TOKEN_H_
