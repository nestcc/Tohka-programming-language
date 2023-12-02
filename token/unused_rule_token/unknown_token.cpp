/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 20:21:58
 * @Discription: 
 */

#include "includes/common.h"
#include "includes/utils.h"
#include "token/unused_rule_token/unknown_token.h"


void UnknownToken::nud(CompileUnit* cu, bool can_assign) {
    COMPILE_ERROR(&parser, "Got UNKNOW_TOKEN");
}

void UnknownToken::led(CompileUnit *cu, bool can_assign) {
    COMPILE_ERROR(&parser, "Got UNKNOW_TOKEN");
}

void UnknownToken::method_sign(CompileUnit *cu, Signature *signature) {
    COMPILE_ERROR(&parser, "Got UNKNOW_TOKEN");
}
