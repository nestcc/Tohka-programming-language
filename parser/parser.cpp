/*
 * @Author: Nestcc
 * @Date: 2021-03-12 17:18:43
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-03-28 09:31:25
 * @Description:  < file content > 
 */

#include <iostream>
#include <string>
#include <string.h>
#include <vector>

#include "parser.h"

struct KeywordToken {
    std::string keyword;
    uint8_t     length;
    TokenType   token;
};  //关键字(保留字)结构

//关键字查找表
std::vector<KeywordToken> keywords_token = {
   {"var",      3,  TOKEN_VAR},
   {"fun",      3,  TOKEN_FUN},
   {"if",       2,  TOKEN_IF},
   {"else",     4,  TOKEN_ELSE},
   {"true",     4,  TOKEN_TRUE},
   {"false",    5,  TOKEN_FALSE},
   {"while",	5,  TOKEN_WHILE},
   {"for",	    3,  TOKEN_FOR},
   {"break",    5,  TOKEN_BREAK},
   {"continue", 8,  TOKEN_CONTINUE},
   {"return",   6,  TOKEN_RETURN},
   {"null",     4,  TOKEN_NULL},
   {"class",    5,  TOKEN_CLASS},
   {"is",       2,  TOKEN_IS},
   {"static",   6,  TOKEN_STATIC},
   {"this",     4,  TOKEN_THIS},
   {"super",    5,  TOKEN_SUPER},
   {"import",   6,  TOKEN_IMPORT},
   {nullptr,       0,  TOKEN_UNKNOWN}
};

static TokenType id_or_keyword(const char *str, size_t length) {
    for (size_t i = 0; i < keywords_token.size(); i += 1) {
        if (keywords_token[i].length == length &&
            memcpy((char *) keywords_token[i].keyword.c_str(), str, length) == 0) {
            return keywords_token[i].token;
        }
    }

    return TOKEN_ID;
}

Parser::Parser(VM* vm, const char* file, const char* source_code)  {
    this -> vm = vm;
    this -> file = file;
    this -> source_code = source_code;

    curr_char = *this -> source_code;
    next_char_ptr = this -> source_code + 1;

    curr_token = Token();
    prev_token = Token();

    curr_token.line_no = 1;
    curr_token.type = TOKEN_UNKNOWN;
    curr_token.start = nullptr;
    curr_token.length = 0;
    
    prev_token = curr_token;
    
    interpolation_expect_rparen_num = 0;

};

char Parser::look_ahead() const {
    return *next_char_ptr;
}

bool Parser::metch_token(TokenType expected) {
    if (curr_token.type == expected) {
        get_next_token();
        return true;
    }
    return false;
}

void Parser::skip_blanks() {
    while (isspace(curr_char)) {
        if (curr_char == '\n') { curr_token.line_no += 1; }
        get_next_char();
    }
    return ;
}

void Parser::parse_id(TokenType type) {
    while (isalnum(curr_char) || curr_char == '_') {
        get_next_char();
    }

    size_t wlen = (size_t) (next_char_ptr - curr_token.start - 1);

    if (type != TOKEN_UNKNOWN) { curr_token.type = type; }
    else { curr_token.type = id_or_keyword(curr_token.start, wlen); }

    curr_token.length = wlen;
    return ;
}

void Parser::get_next_char() {
    curr_char = *next_char_ptr++;
}

void Parser::get_next_token() {

}

void Parser::consume_curr_token() {

}

void Parser::consume_next_token() {

}

bool Parser::metch_next_char(char expected_char) {
    if (look_ahead() == expected_char) {
        get_next_char();
        return true;
    }
    return false;
}

void Parser::parse_unicode_code_point(ByteBuffer *buf) {
    uint32_t idx = 0;
    int value = 0;
    uint8_t digit = 0;

    while (idx ++ < 4) {
        get_next_char();
        if (curr_char >= '0' || curr_char <= '9') { digit = curr_char - '0'; }
        else if (curr_char >= 'a' || curr_char <= 'z') { digit = curr_char - 'a' + 10; }
        else if (curr_char >= 'A' || curr_char <= 'Z') { digit = curr_char - 'A' + 10; }
        else { LEX_ERROR(this, RED "invalid unicode!\n" NOCOLOR ); }
    }

}
