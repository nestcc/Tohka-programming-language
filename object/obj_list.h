/*
 * @Author: nestcc 
 * @Date: 2021/4/6 18:36
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-21 13:28:43
 * @Discription: 
 */

#ifndef _TOHKA_OBJLIST_H_
#define _TOHKA_OBJLIST_H_

#include "object/object_header.h"
#include "vm/mem_buffer_stl.h"

class ObjList : public ObjHeader {
public:
    ValueBuffer elements;

    ObjList() = default;
    ObjList(VM *vm, int size_n);
    Value &operator[](uint64_t index);
    Value remove_element(VM *vm, uint64_t index);
    void insert_element(VM *vm, uint64_t index, Value value);

    ~ObjList() override;

private:
    void resize(VM *vm, uint64_t new_size);
};


#endif //TOHKA_OBJLIST_H
