/*
 * @Author: Nestcc
 * @Date: 2021-04-27 17:48:13
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-27 18:42:06
 * @Description:  < file content > 
 */

#ifndef _COMPILERUNIT_H_
#define _COMPILERUNIT_H_

#include "headers.h"
#include "LocalVar.h"
#include "Upvalue.h"
#include "Loop.h"
#include "../object/ObjFunction.h"
#include "../parser/parser.h"

class CompilerUnit {
public:
    ObjFunction *obj_func;      // 所编译的函数
    LocalVar local_vars[MAX_LOCAL_VAR_NUM]; // 作用域中允许的局部变量的个量上限
    uint64_t loval_var_num;     // 已分配的局部变量个数
    Upvalue upvalues[MAX_UPVALUE_NUM];      // 记录本层函数所引用的upvalue
    uint64_t scope_depth;       // 此项表示当前正在编译的代码所处的作用域,
    uint64_t stack_slot_num;    // 当前使用的slot个数
    Loop *curr_loop;            // 当前正在编译的循环层
    ClassBookKeep *enclosing_class_bk;  // 当前正编译的类的编译信息
    CompilerUnit *enclosing_unit;   // 包含此编译单元的编译单元,即直接外层
    Parser *curr_parser;        // 当前parser
};

#endif
