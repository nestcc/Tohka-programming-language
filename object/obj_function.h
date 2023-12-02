/*
 * @Author: nestcc 
 * @Date: 2021/4/4 23:35
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-27 09:31:00
 * @Discription: 
 */

#ifndef _TOHKA_OBJFUNCTION_H_
#define _TOHKA_OBJFUNCTION_H_

#include <string>
#include "object/headers.h"
#include "object/object_header.h"
#include "core/mem_buffer_stl.h"


class ObjFunction : public ObjHeader {
public:

    ByteBuffer instr_stream;  // 函数编译后的指令流
    ValueBuffer constants;  // 函数中的常量表

    ObjModule *module;      // 本函数所属的模块
    uint64_t max_stk_slot_num;      // 本函数最多需要的栈空间,是栈使用空间的峰值
    uint64_t up_val_num;    // 本函数所涵盖的upvalue数量
    uint8_t arg_num;        // 函数期望的参数个数

    struct FuncDebug {
        FuncDebug() = default;
        std::string file_name;
        MemBufferSTL<uint64_t> line_no;
    } dbg_info;

    ObjFunction() = default;
    ObjFunction(VM *vm, ObjModule *obj_module, uint64_t slot_num);

    ~ObjFunction() override = default;
};


#endif //TOHKA_OBJFUNCTION_H
