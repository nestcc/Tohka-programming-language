/*
 * @Author: nestcc 
 * @Date: 2021/4/4 23:30
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/4 23:30
 * @Discription: 
 */

#include "Value.h"

Value::Value(ValueType vt) {
    type = vt;
    obj_header = nullptr;
}

Value::Value(const bool &bl) {
    type = bl ? VT_TRUE : VT_FALSE;
}

Value::Value(const double &num) {
    type = VT_NUM;
    this -> num = num;
}

Value::Value(const long &ln) {
    type = VT_NUM;
    num = ln;
}

Value::operator bool() {
    return (type == VT_TRUE);
}

Value::Value(ObjHeader *obj_ptr) {
    obj_header = obj_ptr;
}

Value::~Value() {
    if (type == VT_OBJ) { delete obj_header; }
}

//double Value::to_num() {
//    return num;
//}
//
//ObjHeader *Value::to_obj() {
//    return obj_header;
//}
