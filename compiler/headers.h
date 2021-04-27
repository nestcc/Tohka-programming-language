/*
 * @Author: Nestcc
 * @Date: 2021-04-27 09:33:11
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-27 17:56:50
 * @Description:  < file content > 
 */


#ifndef _HEADERS_H_
#define _HEADERS_H_

#include <cinttypes>
#include <string>

class LocalVar;
class Loop;
class Upvalue;
class Signature;
class Compiler;
class ClassBookKeep;
class CompileUnit;

#define MAX_LOCAL_VAR_NUM 128
#define MAX_UPVALUE_NUM 128
#define MAX_ID_LEN 128   //变量名最大长度

#define MAX_METHOD_NAME_LEN MAX_ID_LEN
#define MAX_ARG_NUM 16

//函数名长度+'('+n个参数+(n-1)个参数分隔符','+')'
#define MAX_SIGN_LEN MAX_METHOD_NAME_LEN + MAX_ARG_NUM * 2 + 1

#define MAX_FIELD_NUM 128

#endif