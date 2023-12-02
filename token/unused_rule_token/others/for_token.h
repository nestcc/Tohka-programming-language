/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 21:40:41
 * @Discription: 
 */

#ifndef _TOHKA_FOR_TOKEN_H_
#define _TOHKA_FOR_TOKEN_H_

#include "token/bp_none_token/bp_none_token.h"

class ForToken : public BpNoneToken {
public:
    ForToken() : BpNoneToken() {
        type = TOKEN_FOR;
        keyword = "for";
    }
};

#endif // end of _TOHKA_FOR_TOKEN_H_
