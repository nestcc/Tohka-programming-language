/*
 * @Author: nestcc 
 * @Date: 2021/4/4 23:35
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/4 23:35
 * @Discription: 
 */

#ifndef _TOHKA_OBJFUNCTION_H_
#define _TOHKA_OBJFUNCTION_H_

#include "ObjectHeader.h"

class ObjFunction : public ObjHeader {
public:
    ByteBuffer ins_stream;  // 函数编译后的指令流
    ValueBuffer constants;  // 函数中的常量表

    ObjModule *module;      // 本函数所属的模块
    uint64_t max_stk_slot_num;      // 本函数最多需要的栈空间,是栈使用空间的峰值
    uint64_t up_val_num;    // 本函数所涵盖的upvalue数量
    uint8_t arg_num;        // 函数期望的参数个数
};


#endif //TOHKA_OBJFUNCTION_H
