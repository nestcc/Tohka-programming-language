/*
 * @Author: nestcc 
 * @Date: 2021/4/4 22:48
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/4 22:48
 * @Discription: 
 */

#ifndef _TOHKA_OBJSTRING_H_
#define _TOHKA_OBJSTRING_H_

#include <cinttypes>
#include "ObjectHeader.h"

class ObjString : public ObjHeader {
public:
    uint64_t hash_code;
    std::string value;

    ObjString() = delete;
    ObjString(VM *vm, const std::string &str);
    uint64_t hash();
};


#endif //TOHKA_OBJSTRING_H
