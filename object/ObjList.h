/*
 * @Author: nestcc 
 * @Date: 2021/4/6 18:36
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/6 18:36
 * @Discription: 
 */

#ifndef _TOHKA_OBJLIST_H_
#define _TOHKA_OBJLIST_H_

#include "ObjectHeader.h"

class ObjList : public ObjHeader {
public:
    ValueBuffer elements;

    ObjList() = default;
    ObjList(VM *vm, int size_n);
    Value &operator[](uint64_t index);
    Value remove_element(VM *vm, uint64_t index);
    void insert_element(VM *vm, uint64_t index, Value value);

    ~ObjList() override = default;

private:
    void resize(VM *vm, uint64_t new_size);
};


#endif //TOHKA_OBJLIST_H
