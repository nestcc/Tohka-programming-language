/*
 * @Author: Nestcc
 * @Date: 2021-03-12 17:18:38
 * @LastEditors: Nestcc
 * @LastEditTime: 2022-01-24 01:27:08
 * @Description:  < file content >
 */

#ifndef _PARSER_H_
#define _PARSER_H_

#include "compiler/compile_unit.h"
#include "includes/common.h"
#include "includes/unicode.h"
#include "includes/utils.h"
#include "object/base_class.h"
#include "object/value.h"
#include "token/token.h"
#include "vm/core.h"
#include "vm/mem_buffer_stl.h"

class Parser {
public:
    const char *file;
    const char *source_code;

    const char *next_char_ptr;
    char curr_char;
    Token *curr_token;
    Token *prev_token;
    ObjModule *curr_module;
    CompileUnit *curr_compile_unit;
    VM *vm;
    Parser *parent;

public:
    Parser() = default;
    Parser(VM *vm, const char *file, const char *sourceCode, ObjModule *obj_mudule);
    char look_ahead() const;
    bool metch_token(Token::TokenType expected);
    void skip_blanks();
    void parse_id(Token::TokenType type);
    void get_next_token();
    void consume_curr_token(Token::TokenType expected, const char *errMsg);
    void consume_next_token(Token::TokenType expected, const char *errMsg);

private:
    // 处于内嵌表达式之中时,期望的右括号数量.
    // 用于跟踪小括号对儿的嵌套
    int interpolation_expect_rparen_num;

private:
    bool match_next_char(char expected_char);
    void parse_unicode_code_point(ByteBuffer *buf);
    void get_next_char();
    void parse_string();
    void skip_comment();
    void skip_line();
    bool match_token(Token::TokenType expected);
    void parse_dec_number();
    void parse_hex_number();
    void parse_oct_number();
    void parse_number();
};

#endif
