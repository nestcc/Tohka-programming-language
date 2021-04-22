/*
 * @Author: nestcc 
 * @Date: 2021/4/4 23:12
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-22 14:03:04
 * @Discription: 
 */

#ifndef _TOHKA_HEADERS_H_
#define _TOHKA_HEADERS_H_

#include "../includes/common.h"
#include "../includes/utils.h"

class Value;
class ObjHeader;
class ObjClosure;
class ObjModule;
class ObjUpvalue;
class ObjString;

enum ObjType{
    OT_CLASS,   //此项是class类型,以下都是object类型   0
    OT_LIST,
    OT_MAP,
    OT_MODULE,
    OT_RANGE,
    OT_STRING,                  // 5
    OT_UPVALUE,
    OT_FUNCTION,
    OT_CLOSURE,
    OT_INSTANCE,
    OT_THREAD                   // 10
};  //对象类型

enum ValueType {
    VT_UNDEFINED,
    VT_NULL,
    VT_FALSE,
    VT_TRUE,
    VT_NUM,
    VT_OBJ   //值为对象,指向对象头
};     //value类型

enum MethodType {
    MT_NONE,        // 空方法类型,并不等同于undefined
    MT_PRIMITIVE,   // 在vm中用c实现的原生方法
    MT_SCRIPT,	    // 脚本中定义的方法
    MT_FN_CALL,     // 有关函数对象的调用方法,用来实现函数重载
};

union Bits64 {
    uint64_t bits64;
    uint32_t bits32[2];
    double num;
};

typedef MemBufferSTL<Value> ValueBuffer;
typedef bool (*Primitive) (VM *vm, Value *args);

#define CAPACITY_GROW_FACTOR 4
#define MIN_CAPACITY 64


//uint32_t hash_string(const std::string &str) {
//    uint32_t hash_code = 2166136261;
//    for (int i = 0; i < str.size(); i += 1) {
//        hash_code ^= str[i];
//        hash_code *= 16777619;
//    }
//    return hash_code;
//}

#endif //TOHKA_OBJ_HEADERS_H
