/*
 * @Author: Nestcc
 * @Date: 2021-04-22 10:36:45
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-24 21:04:26
 * @Description:  < file content > 
 */

#include <utility>
#include "object/obj_map.h"

ObjMap::KV::KV() : key(Value(0.0)), val(Value(0.0)), next(nullptr) {};

ObjMap::KV::KV(ObjMap::KV &&kv) : key(std::forward<Value>(kv.key)), val(std::forward<Value>(kv.val)), next(nullptr) {}

ObjMap::KV::KV(const KV &kv) : key(kv.key), val(kv.val), next(nullptr) {};

ObjMap::KV::KV(Value &&key, Value &&val) : key(std::forward<Value>(key)), val(std::forward<Value>(val)), next(nullptr) {}

ObjMap::KV::KV(const Value &key, const Value &val) : key(key), val(val), next(nullptr) {};

ObjMap::KV &ObjMap::KV::operator= (const KV &kv) {
    if (key == kv.key) {
        val = kv.val;
    }
    else {
        RUNTIME_ERROR(nullptr, "class KV assignment, key not equal.");
    }
    return *this;
}

ObjMap::ObjMap(VM *vm) :
ObjHeader(vm, OT_MAP, vm -> map_class),
capacity(1024),
vsize(0),
size(0), 
enlarge_ratio(0.8),
items(std::vector<KV *> (capacity, nullptr)) {
    vm->alloc_memory(sizeof(*this));
}

ObjMap::ObjMap(VM *vm, uint64_t capacity) :
    ObjHeader(vm, OT_MAP, vm -> map_class),
    capacity(capacity),
    vsize(0),
    size(0), 
    enlarge_ratio(0.8),
    items(std::vector<KV *> (capacity, nullptr)) {}

int ObjMap::add_item(const Value &key, const Value &val) {
    if (capacity == 0) { MEM_ERROR("Capacity of a map object is 0."); }
    uint64_t index = key.hash_value() % capacity;
    if (items[index] == nullptr) {
        items[index] = new KV(key, val);
        vsize += 1;
    }
    else {
        KV *head = items[index];
        while (head && head -> key != key) { head = head -> next; }

        if (head == nullptr) {
            head = new KV(key, val);
            head -> next = items[index];
            items[index] = head;
        }
        else {
            head -> val = val;
        }
    }
    size += 1;
    if (vm != nullptr)
        vm->alloc_memory(sizeof(KV));
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

    if (vm != nullptr)
        vm->realloc_memory(sizeof(KV), 0);
    return 0;
}

Value *ObjMap::get(const Value &key) {
    uint64_t index = key.hash_value() % capacity;

    KV *head = items[index];
    while (head && head -> key != key) { head = head -> next; }
    return head == nullptr ? nullptr : &(head -> val);
}

void ObjMap::clear() {
    for (uint64_t i = 0; i < capacity; i += 1) {
        if (items[i] == nullptr) { continue; }
        KV *curr = items[i], *next;
        while (curr != nullptr) {
            next = curr -> next;
            delete curr;
            curr = curr -> next;
        }
    }

    if (vm != nullptr)
        vm->realloc_memory(sizeof(KV) * size, 0);
    vsize = size = 0;
}

Value *ObjMap::get_item(const Value &key) {
    return this -> get(key);
}

ObjMap::~ObjMap() {
    clear();
}
