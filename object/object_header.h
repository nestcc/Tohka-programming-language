/*
 * @Author: Nestcc
 * @Date:
 * @LastEditors: Nestcc
 * @LastEditTime: 2022-01-24 01:30:11
 * @Discription:
 */

#ifndef _TOHKA_OBJECT_HEADER_H_
#define _TOHKA_OBJECT_HEADER_H_

#include "object/headers.h"

class ObjHeader {
public:
    ObjType type;
    bool is_dark;
    BaseClass *cls;  // super class
    ObjHeader *next, *prev;
    uint64_t ref_cnt;
    VM *vm;

public:
    ObjHeader() = default;
    ObjHeader(VM *vm, ObjType obj_type, BaseClass *base_cls);

    ObjHeader &operator=(const ObjHeader &obj) = delete;

    virtual bool equal_to(const ObjHeader *obj);

    virtual uint64_t hash_value() const;

    virtual ~ObjHeader();

private:
};

#endif  // TOHKA_OBJECT_HEADER_H
