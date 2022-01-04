/*
 * @Author: Nestcc
 * @Date: 2021-04-22 10:24:47
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-25 17:42:08
 * @Description:  < file content > 
 */

#ifndef _TOHKA_OBJ_MAP_H_
#define _TOHKA_OBJ_MAP_H_

#include "value.h"

class ObjMap : public ObjHeader {
private:
    struct KV {
        Value key;
        Value val;
        KV *next;
        KV();
        KV(KV &&kv);
        KV(const KV &kv);
        KV(Value &&key, Value &&val);
        KV(const Value &key, const Value &val);
        KV &operator=(const KV &kv);
        ~KV() = default;
    };
    
// private:
    void clear();
    Value *get(const Value &key);
    
    uint64_t capacity, vsize, size;
    double  enlarge_ratio;
    std::vector<KV *> items;

public:

    ObjMap() = default;
    ObjMap(VM *vm);
    ObjMap(VM *vm, uint64_t capacity);
    ~ObjMap();
    int add_item(const Value &key, const Value &val);
    Value *get_item(const Value &key);
    int remove(const Value &key);
    
};

#endif
