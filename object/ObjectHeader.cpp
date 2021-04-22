/*
 * @Author: Nestcc
 * @Date: 2021-04-04 16:38:13
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-22 14:10:11
 * @Description:  < file content > 
 */
//
// Created by nestcc on 2021/4/4.
//

#include <iostream>
#include "ObjectHeader.h"

ObjHeader::ObjHeader(VM *vm, ObjType obj_type, BaseClass *base_cls) {
    type = obj_type;
    cls = base_cls;
    is_dark = false;
    ref_cnt = 0;

    vm -> add_object(this);
    LOG_INFO("object type : %d add to vm.\n", type);
//    this -> vm = vm;
}

bool ObjHeader::equal_to(const ObjHeader *obj) {
    if (type != obj -> type) { return false; }
    return true;
}

uint64_t ObjHeader::hash_value() const {
    RUNTIME_WARRINING(nullptr, "Unsupport hash code for current object %d.", type);
    return -1;
}

ObjHeader::~ObjHeader() {
    LOG_INFO("remove object (%d) from vm.\n", type);
    vm -> remove_object(this);
}
