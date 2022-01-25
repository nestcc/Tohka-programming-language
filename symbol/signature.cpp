/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 17:40:41
 * @Discription: 
 */

#include "signature.h"

std::string Signature::to_string() {
    std::string sign_str = name;
    switch (type) {
        case SIGN_GETTER:
            break;
        case SIGN_SETTER:
            // sign=(_)
            sign_str += "=(_)";
            break;
        case SIGN_CONSTRUCT:
        case SIGN_METHOD:
            // sign(_,...)
            sign_str += '(';
            for (auto i = 0; i < arg_num-1; i += 1) {
                sign_str += "_,";
            }
            sign_str += "_)";
            break;
        case SIGN_SUBSCRIPT:
            // sign[_,...]
            sign_str += '[';
            for (auto i = 0; i < arg_num; i += 1) {
                sign_str += "_,";
            }
            sign_str += "_]";
            break;
        case SIGN_SUBSCRIPT_SETTER:
            // sign[_,...]=(_)
            sign_str += '[';
            for (auto i = 0; i < arg_num-1; i += 1) {
                sign_str += "_,";
            }
            sign_str += "_]=(_)";
            break;
    }
    return sign_str;
}
