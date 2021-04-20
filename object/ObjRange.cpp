/*
 * @Author: nestcc 
 * @Date: 2021/4/19 23:14
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/19 23:14
 * @Discription: 
 */

#include "ObjRange.h"

ObjRange::ObjRange(VM *vm, int form, int to) :
        ObjHeader(vm, OT_RANGE, vm -> range_class),
        from(from),
        to(to){
//    vm -> alloca_memory(sizeof(*this));
}
