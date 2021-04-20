/*
 * @Author: Nestcc
 * @Date:
 * @LastEditors: Nestcc
 * @LastEditTime:
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
    virtual ~ObjHeader();

private:
};

#endif //TOHKA_OBJECT_HEADER_H
