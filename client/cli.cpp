/*
 * @Author: Nestcc
 * @Date: 2021-03-28 10:22:48
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-03-29 15:40:45
 * @Description:  < file content > 
 */

#include <iostream>
#include <cstring>
#include "cli.h"

void runFile(const char* path) {
    LOG_INFO("in run file\n");

    const char* lastSlash = strrchr(path, '/');
    if (lastSlash != nullptr) {
        char* root = (char*)malloc(lastSlash - path + 2);
        memcpy(root, path, lastSlash - path + 1);
        root[lastSlash - path + 1] = '\0';
        root_dir = root;
    }

    LOG_INFO("get resource code ok\n");

    VM *vm = VM::getInstance();

    LOG_INFO("get vm ok\n");

    const char* sourceCode = read_file(path);

    Parser parser(vm, path, sourceCode);

    #include "../parser/token.list"

    while (parser.curr_token.type != TOKEN_EOF) {
        parser.get_next_token();
        printf(" %d L-tokenArray [%d] : %s [", parser.curr_token.line_no,
      	    parser.curr_token.type, tokenArray[parser.curr_token.type].data());
        uint32_t idx = 0;
        while (idx < parser.curr_token.length) {
            printf("%c", *(parser.curr_token.start + idx++));
        }
        printf("]\n");
    }
}

int main(int argc, const char **argv) {
    LOG_INFO("in main\n");

    if (argc == 1) {
        fprintf(stderr, RED "use %s [ file name ] ...\n" NOCOLOR, argv[0]);
    } else {
        runFile(argv[1]);
    }

    return 0;
}
