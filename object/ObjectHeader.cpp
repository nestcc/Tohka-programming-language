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

//    if (vm -> all_objects == nullptr) {
//        next = this;
//        prev = this;
//        vm -> all_objects = this;
//    }
//    else {
//        next = vm -> all_objects;
//        prev = vm -> all_objects -> prev;
//        next -> prev = this;
//        prev -> next = this;
//        vm -> all_objects = this;
//    }
    vm -> add_object(this);
    LOG_INFO("object type : %d add to vm.\n", type);
//    this -> vm = vm;
}

ObjHeader::~ObjHeader() {
    LOG_INFO("remove object (%d) from vm.\n", type);
    vm -> remove_object(this);
}
