/*
 * @Author: nestcc 
 * @Date: 2021/4/19 23:14
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-21 14:12:45
 * @Discription: 
 */

#include "ObjRange.h"

ObjRange::ObjRange(VM *vm, int from, int to) :
        ObjHeader(vm, OT_RANGE, vm -> range_class),
        from(from),
        to(to){
}

bool ObjRange::equal_to(const ObjHeader *obj) {
    const ObjRange *other = dynamic_cast<const ObjRange *> (obj);
    if (other == nullptr) { return false; }
    return (from == other -> from) && (to == other -> to);
}
