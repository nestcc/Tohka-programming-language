/*
 * @Author: Nestcc
 * @Date:
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-22 14:42:24
 * @Discription:
 */

#ifndef _TOHKA_OBJECT_HEADER_H_
#define _TOHKA_OBJECT_HEADER_H_

#include "headers.h"

class ObjHeader {
public:
    ObjType type;
    bool is_dark;
    BaseClass *cls;
    ObjHeader *next, *prev;
    uint64_t ref_cnt;
    VM *vm;

    ObjHeader() = default;
    ObjHeader(VM *vm, ObjType obj_type, BaseClass *base_cls);

    ObjHeader &operator=(const ObjHeader &obj) = delete;

    virtual bool equal_to(const ObjHeader *obj);

    virtual uint64_t hash_value() const;

    virtual ~ObjHeader();
private:
};

#endif //TOHKA_OBJECT_HEADER_H
