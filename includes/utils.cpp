/*
 * @Author: Zhao Yizhu
 * @Date: 2021-02-25 14:10:12
 * @LastEditors: Zhao Yizhu
 * @LastEditTime: 2021-02-25 15:06:44
 * @Description:  < file content > 
 */

#include "includes/utils_cpp.h"

// 找出大于等于v最近的2次幂
uint32_t ceilToPowerOf2(uint32_t v) {
   v += (v == 0);  //修复当v等于0时结果为0的边界情况
   v--;
   v |= v >> 1;
   v |= v >> 2;
   v |= v >> 4;
   v |= v >> 8;
   v |= v >> 16;
   v++;
   return v;
}


template<typename Type>
void MemBuffer<Type>::fillWirte(VM *vm, Type &data, uint32_t fill_cnt) {
    uint32_t new_cnt = count + fill_cnt;
    if (new_cnt > capacity) {
        size_t old_size = capacity * sizeof(Type);
        capacity = ceil_to_squar(new_cnt);

        size_t new_size = capacity * sizeof(Type);
        LOG_ERROR(new_size > old_size, "Faint memory allocate");
        this -> data = (Type *) mem_manager(vm, this -> data, old_size, new_size);
    }

    uint32_t cnt = 0;
    while (cnt < fill_cnt) {
        this -> data[count++] = data;
    }
    return ;
}

template<typename Type>
void MemBuffer<Type>::buffAdd(VM *vm, Type &data) {
    fillWirte(vm, data, 1);
    return ;
}

template<typename Type>
void MemBuffer<Type>::buffClear(VM *vm) {
    size_t old_size = capacity * sizeof(data[0]);
    mem_manager(vm, data, old_size, 0);
    return ;
}
