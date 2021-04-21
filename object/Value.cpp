/*
 * @Author: nestcc 
 * @Date: 2021/4/4 23:30
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-21 13:16:46
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
    return (type != VT_FALSE);
}

Value::operator double() {
    return type == VT_NUM ? num : 0;
}

Value::operator ObjHeader *() {
    return type == VT_OBJ ? obj_header : nullptr;
}

Value::Value(ObjHeader *obj_ptr) {
    obj_header = obj_ptr;
}

Value::~Value() {
    if (type == VT_OBJ && obj_header != nullptr) { delete obj_header; }
}

Value::Value(const Value &val) {
    type = val.type;
    num = val.num;
}

Value::Value(Value &&val) {
    type = val.type;
    num = val.num;
    val.obj_header = nullptr;
//    return *this;
}

Value &Value::operator=(const Value &val) {
    type = val.type;
    num = val.num;
    return *this;
}

Value &Value::operator=(Value &&val) noexcept {
    type = val.type;
    num = val.num;
    val.obj_header = nullptr;
    return *this;
}

bool operator==(const Value &v1, const Value &v2) {
    if (v1.type != v2.type) { return false; }
    if (v1.type == VT_NUM) { return v1.num == v2.num; }
    if (v1.type == VT_OBJ) { return v1.obj_header == v2.obj_header; }
    return true;
}


//Value &Value::operator=(const Value &val) {
//    this->type = val.type;
//    this->num = val.num;
//    return *this;
//}

//Value &operator=(Value &self, Value &val) {
//    self.type = val.type;
//    self.num = val.num;
//    return self;
//}

//double Value::to_num() {
//    return num;
//}
//
//ObjHeader *Value::to_obj() {
//    return obj_header;
//}
