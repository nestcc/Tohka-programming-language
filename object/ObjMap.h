/*
 * @Author: Nestcc
 * @Date: 2021-04-22 10:24:47
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-24 20:27:11
 * @Description:  < file content > 
 */

#ifndef _TOHKA_OBJMAP_H_
#define _TOHKA_OBJMAP_H_

#include "Value.h"

class ObjMap : public ObjHeader {
private:
    struct KV {
        Value key;
        Value val;
        KV *next;
        KV();
        KV(const KV &kv);
        KV &operator==(const KV &kv);
        KV(const Value &key, const Value &val);
        ~KV() = default;
    };
    
private:
    void clear();
    Value *get(const Value &key);
    
    uint64_t capacity, vsize, size;
    double  enlarge_ratio;

public:

    ObjMap() = default;
    ObjMap(VM *vm);
    ObjMap(VM *vm, uint64_t capacity);
    ~ObjMap();
    std::vector<KV *> items;
    int add_item(const Value &key, const Value &val);
    Value &get_item(const Value &key);
    int remove(const Value &key);
    
};

#endif
