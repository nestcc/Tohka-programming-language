/*
 * @Author: nestcc 
 * @Date: 2021/4/4 23:30
 * @LastEditors: Nestcc
 * @LastEditTime: 2022-01-03 20:17:18
 * @Discription: 
 */

#include "object/value.h"

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

Value::Value(ObjHeader *obj_ptr) {
    type = VT_OBJ;
    obj_header = obj_ptr;
    obj_ptr -> ref_cnt += 1;
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

Value::~Value() {
    if (type == VT_OBJ && obj_header != nullptr && obj_header -> ref_cnt == 1)
        obj_header -> ref_cnt -= 1;
}

Value::Value(const Value &val) {
    type = val.type;
    num = val.num;
    if (type == VT_OBJ) {
        obj_header -> ref_cnt += 1;
    }
}

Value::Value(Value &&val) {
    type = val.type;
    num = val.num;
    val.obj_header = nullptr;
}

Value &Value::operator=(const Value &val) {
    if (type == VT_OBJ) {
        obj_header -> ref_cnt -= 1;
    }
    type = val.type;
    num = val.num;
    if (type == VT_OBJ) {
        obj_header -> ref_cnt += 1;
    }
    return *this;
}

Value &Value::operator=(Value &&val) noexcept {
    type = val.type;
    num = val.num;
    val.obj_header = nullptr;
    return *this;
}

uint64_t Value::hash_value() const {
    switch (type) {
        case VT_FALSE:
        case VT_NULL:
            return 0;
        case VT_TRUE:
            return 1;
        case VT_NUM:
            return num;
        case VT_OBJ:
            return obj_header -> hash_value();
        default:
            RUNTIME_ERROR(nullptr, "UNDEFINED type has no hash code.");
            return -1;
    }
    return 0;
}

bool Value::operator==(ValueType vtype) {
    return type == vtype;
}

bool operator==(const Value &v1, const Value &v2) {
    if (v1.type != v2.type) { return false; }
    if (v1.type == VT_NUM) { return v1.num == v2.num; }
    if (v1.type == VT_OBJ) { return v1.obj_header == v2.obj_header; }
    return true;
}

bool operator!=(const Value &v1, const Value &v2) {
    return !(v1 == v2);
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

ObjHeader *Value::toObj() {
    if (type != VT_OBJ) { return nullptr; }
    return obj_header;
}
