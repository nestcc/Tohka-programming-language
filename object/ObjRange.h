/*
 * @Author: nestcc 
 * @Date: 2021/4/19 23:14
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-21 14:12:53
 * @Discription: 
 */

#ifndef _TOHKA_OBJRANGE_H_
#define _TOHKA_OBJRANGE_H_

#include "ObjectHeader.h"

class ObjRange : public ObjHeader{
public:
    ObjRange() = default;
    ObjRange(VM *vm, int from, int to);

    virtual bool equal_to(const ObjHeader *obj) override;
    
    uint64_t from;
    uint64_t to;
};


#endif //TOHKA_OBJRANGE_H
