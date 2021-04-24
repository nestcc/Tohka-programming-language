/*
 * @Author: Nestcc
 * @Date:
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-24 21:50:55
 * @Discription:
 */

#ifndef _TOHKA_OBJECT_HEADER_H_
#define _TOHKA_OBJECT_HEADER_H_

#include "headers.h"
#include "../vm/MemBufferSTL.h"

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

typedef MemBufferSTL<Value> ValueBuffer;

#endif //TOHKA_OBJECT_HEADER_H
