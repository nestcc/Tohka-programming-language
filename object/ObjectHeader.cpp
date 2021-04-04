//
// Created by nestcc on 2021/4/4.
//

#include "ObjectHeader.h"

ObjHeader::ObjHeader(VM *vm, ObjType obj_type, BaseClass *base_cls) {
    type = obj_type;
    cls = base_cls;
    is_dark = false;
    next = vm -> all_objects;
    vm -> all_objects = next;
}
