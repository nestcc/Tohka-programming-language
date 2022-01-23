/*
 * @Author: nestcc
 * @Date: 2021/4/19 23:14
 * @LastEditors: Nestcc
 * @LastEditTime: 2022-01-24 01:29:42
 * @Discription:
 */

#include "object/obj_range.h"

#include "vm/vm.h"

static inline uint64_t hash_num(uint64_t num) {
    Bits64 bits64;
    bits64.num = num;
    return bits64.bits32[0] ^ bits64.bits32[1];
}

ObjRange::ObjRange(VM *vm, int from, int to)
    : ObjHeader(vm, OT_RANGE, vm->range_class), from(from), to(to) {}

bool ObjRange::equal_to(const ObjHeader *obj) {
    const ObjRange *other = dynamic_cast<const ObjRange *>(obj);
    if (other == nullptr) {
        return false;
    }
    return (from == other->from) && (to == other->to);
}

uint64_t ObjRange::hash_value() const { return hash_num(from) ^ hash_num(to); }
