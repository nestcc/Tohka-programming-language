/*
 * @Author: nestcc 
 * @Date: 2021/4/4 22:48
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-22 14:10:40
 * @Discription: 
 */

#ifndef _TOHKA_OBJSTRING_H_
#define _TOHKA_OBJSTRING_H_

#include <cinttypes>
#include <string>
#include "ObjectHeader.h"

class ObjString : public ObjHeader {
public:
    uint64_t hash_code;
    std::string value;

    ObjString() = delete;
    ObjString(VM *vm, const std::string &str);
    ObjString(VM *vm, const char *str, uint32_t ssize);
    
    uint64_t hash_value() const override;

    uint64_t hash();

    virtual bool equal_to(const ObjHeader *obj) override;
    
    ~ObjString() override;
};


#endif //TOHKA_OBJSTRING_H
