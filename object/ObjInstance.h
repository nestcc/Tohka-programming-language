/*
 * @Author: nestcc 
 * @Date: 2021/4/4 18:40
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/4 18:40
 * @Discription: 
 */

#ifndef _TOHKA_OBJINSTANCE_H_
#define _TOHKA_OBJINSTANCE_H_

#include <vector>
#include "ObjectHeader.h"

class ObjInstance : public ObjHeader{
public:
    typedef std::vector<Value> FieldType;
    FieldType fields;
    ObjInstance() = default;
    ObjInstance(VM *vm, BaseClass *base_class);
};


#endif //TOHKA_OBJINSTANCE_H
