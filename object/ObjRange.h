/*
 * @Author: nestcc 
 * @Date: 2021/4/19 23:14
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/19 23:14
 * @Discription: 
 */

#ifndef _TOHKA_OBJRANGE_H_
#define _TOHKA_OBJRANGE_H_

#include "ObjectHeader.h"

class ObjRange : public ObjHeader{
public:
    ObjRange() = default;
    ObjRange(VM *vm, int form, int to);

    uint64_t from;
    uint64_t to;
};


#endif //TOHKA_OBJRANGE_H
