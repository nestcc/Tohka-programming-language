/*
 * @Author: Nestcc
 * @Date: 2021-04-22 10:36:45
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-22 14:50:44
 * @Description:  < file content > 
 */

#include "ObjMap.h"


ObjMap::KV::KV() : key(Value(0.0)), val(Value(0.0)), next(nullptr) {};

ObjMap::KV::KV(const KV &kv) : key(kv.val), val(kv.val), next(nullptr) {};

ObjMap::KV::KV(const Value &key, const Value &val) : key(key), val(val), next(nullptr) {};

ObjMap::KV &ObjMap::KV::operator== (const KV &kv) {
    if (key == kv.key) {
        val = kv.val;
    }
    else {
        RUNTIME_ERROR(nullptr, "class KV assignment, key not equal.");
    }
    return *this;
}

ObjMap::ObjMap(VM *vm) :
ObjHeader(vm, OT_MAP, vm -> map_class) {
    capacity = 1024, vsize = 0, size = 0, enlarge_ratio = 0.8;
    items = std::vector<KV *> (capacity, nullptr);
}

int ObjMap::add_item(const Value &key, const Value &val) {
    uint64_t index = key.hash_value() % capacity;
    if (items[index] == nullptr) {
        items[index] = new KV(key, val);
        vsize += 1;
    }
    else {
        KV *head = new KV(key, val);
        head -> next = items[index];
        items[index] = head;
    }
    size += 1;
    return 0;
}

int ObjMap::remove(const Value &key) {
    uint64_t index = key.hash_value() % capacity;
    if (items[index] == nullptr) {
        RUNTIME_ERROR(nullptr, "Removing value %lf error, element not in hash table.", key.num);
        return -1;
    }

    KV *rm = items[index], *prev = rm;

    if (rm -> key == key) {
        items[index] = rm -> next;
        delete rm;
        vsize -= 1;
        size -= 1;
        return 0;
    }

    rm = rm -> next;
    while (rm && rm -> key != key) {
        rm = rm -> next;
        prev = prev -> next;
    }

    if (rm == nullptr) {
        RUNTIME_ERROR(nullptr, "Removing value %lf error, element not in hash table.", key.num);
        return -1;
    }

    prev -> next = rm -> next;
    delete rm;
    size -= 1;
    return 0;
}

Value *ObjMap::get(const Value &key) {
    uint64_t index = key.hash_value() % capacity;

    if (items[index] == nullptr) { return nullptr; }

    KV *res = items[index];
    while (res && res -> key != key) { res = res -> next; }
    return res == nullptr ? nullptr : &(res -> val);
}
