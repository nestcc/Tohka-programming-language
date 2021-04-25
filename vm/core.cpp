/*
 * @Author: Nestcc
 * @Date: 2021-03-12 16:33:56
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-25 17:39:00
 * @Description:  < file content > 
 */

#include <string>
#include <sys/stat.h>
#include "core.h"
#include "../object/ObjMap.h"
#include "../object/Value.h"
#include "../object/ObjModule.h"
// #include "vm.h"

char *root_dir = nullptr;

// 读源码文件
char *read_file(const char *fpath) {
    FILE *srcf = fopen(fpath, "r");

    if (srcf == nullptr) {
        IO_ERROR(RED "Cannot open file %s.\n" NOCOLOR, fpath);
        exit(EXIT_FAILURE);
    }

    struct stat file_status;
    stat(fpath, &file_status);

    size_t fsize = file_status.st_size;

    char *fcontent = (char *) malloc(sizeof(char) * (fsize + 5));

    if (fcontent == nullptr) {
        MEM_ERROR(RED "Allocate memory for source file %s failed.\n" NOCOLOR, fpath);
        exit(EXIT_FAILURE);
    }


    size_t read_size = fread(fcontent, sizeof(char), fsize, srcf);

    if (read_size < fsize) {
        IO_ERROR(RED "Read file failed, total %d, get %d.\n" NOCOLOR, fsize, read_size);
        exit(EXIT_FAILURE);
    }

    fcontent[fsize] = EOF;

    fclose(srcf);

    return fcontent;

}

VM::VmResult exec_module(VM *vm, Value module_name, const char *module_code) {
    return VM::VmResult::VM_RESULT_ERROR;
}

void build_core(VM *vm) {
    ObjModule *core_module = new ObjModule(vm, "__core__module__");
    vm -> all_modules = new ObjMap(vm, 8);
    vm -> all_modules -> add_item(Value(VT_NULL), Value(core_module));
}
