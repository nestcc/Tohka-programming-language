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
#include "../object/ObjFunction.h"
#include "../object/ObjModule.h"

void runFile(const char* path) {
    const char* lastSlash = strrchr(path, '/');
    if (lastSlash != nullptr) {
        char* root = (char*)malloc(lastSlash - path + 2);
        memcpy(root, path, lastSlash - path + 1);
        root[lastSlash - path + 1] = '\0';
        root_dir = root;
    }

    VM *vm = VM::getInstance();

    const char* sourceCode = read_file(path);

    Parser parser(vm, path, sourceCode);

//    #include "../parser/token.list"

    while (parser.curr_token.type != TOKEN_EOF) {
        parser.get_next_token();
        printf(" %llu L-tokenArray [%d] : [", parser.curr_token.line_no,
      	    parser.curr_token.type);
//        std::cout << tokenArray[parser.curr_token.type] << " [";
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

//    ObjModule module(VM::getInstance(), "new module5000");
//    LOG_INFO(" create module ok\n");
//    ObjFunction obj_func(VM::getInstance(), &module, 32);
//    LOG_INFO(" create function object ok\n");

    VM *vm = VM::getInstance();

    std::cout << " get all objects" << std::endl;
    ObjHeader *objs = vm -> all_objects;
//    std::cout << objs -> type << std::endl;

    while (objs != nullptr) {
        ObjString *str_obj = dynamic_cast<ObjString *> (objs);
        if (str_obj == nullptr) { continue; }
        std::cout << str_obj -> value << std::endl;
        objs = objs -> next;
    }

    return 0;
}
