/*
 * @Author: Nestcc
 * @Date: 2021-04-27 09:37:26
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-27 09:39:42
 * @Description:  < file content > 
 */

#ifndef _SIGNATURE_H_
#define _SIGNATURE_H_

#include "headers.h"

class Signature {
public:
    enum SignatureType {
        SIGN_CONSTRUCT,  //构造函数
        SIGN_METHOD,  //普通方法
        SIGN_GETTER, //getter方法
        SIGN_SETTER, //setter方法
        SIGN_SUBSCRIPT, //getter形式的下标
        SIGN_SUBSCRIPT_SETTER   //setter形式的下标
    };

    SignatureType type;
    std::string name;
    uint64_t arg_num;
};

#endif
