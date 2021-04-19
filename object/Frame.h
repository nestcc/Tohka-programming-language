/*
 * @Author: nestcc 
 * @Date: 2021/4/4 23:48
 * @LastEditors: nestcc
 * @LastEditTime: 2021/4/4 23:48
 * @Discription: 
 */

#ifndef _TOHKA_FRAME_H_
#define _TOHKA_FRAME_H_

#include <cinttypes>
#include "ObjClosure.h"

class Frame : public ObjClosure {
public:
    uint8_t *ip;    // 程序计数器 指向下一个将被执行的指令
//    ObjClosure *closure;    // 在本frame中执行的闭包函数
    Value *stack_start;     // 此项用于指向本frame所在thread运行时栈的起始地址

    Frame() = default;
};

#endif //TOHKA_FRAME_H
