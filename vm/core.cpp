/*
 * @Author: Nestcc
 * @Date: 2021-03-12 16:33:56
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-05-08 15:59:25
 * @Description:  < file content > 
 */

#include <string>
#include <sys/stat.h>
#include <algorithm>
#include "core.h"
#include "primitive_methods.h"
#include "../object/ObjMap.h"
#include "../object/Value.h"
#include "../object/ObjModule.h"
#include "../object/BaseClass.h"
#include "../object/Method.h"
#include "../compiler/compiler.h"

char *root_dir = nullptr;

static inline void func_bind_class(VM *vm, BaseClass *base_cls, std::string method_name, Primitive prim_func) {
    if (method_name == "") {
        COMPILE_ERROR(nullptr, "method_name is empty.");
        return;
    }
    else if (prim_func == nullptr) {
        COMPILE_ERROR(nullptr, "primitive function is nullptr.");
        return;
    }

    uint64_t global_index = get_index_from_symbol_table(&vm -> all_method_name, method_name);
    Method *method = new Method();
    method -> prim_func = prim_func;
    method -> type = MT_PRIMITIVE;
    bind_method(base_cls, global_index, method);
}

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

int get_index_from_symbol_table(MethodNameList *table, std::string &name) {
    return std::find(table -> begin(), table -> end(), name) - table -> begin();
}

void bind_method(BaseClass *base_class, uint64_t index, Method *method) {
    if (index >= base_class -> methods.size()) {
        base_class -> methods.fill_wirte(Method(), index - base_class -> methods.size() + 1);
    }
    base_class -> methods[index] = *method;
}

void bind_super_class(BaseClass *sub_class, BaseClass *super_class) {
    sub_class -> super_class = super_class;
    sub_class -> field_num += super_class -> field_num;
    for (uint64_t idx = 0; idx < super_class -> methods.size(); idx += 1) {
        bind_method(sub_class, idx, &(super_class -> methods[idx]));
    }
}

void build_core(VM *vm) {
    ObjModule *core_module = new ObjModule(vm, "__core_module__");
    vm -> all_modules = new ObjMap(vm);
    vm -> all_modules -> add_item(Value(VT_NULL), Value(core_module));

    vm -> object_class = new BaseClass(vm, "__object__", 0);
    define_module_value(vm, core_module, "__object__", Value(core_module));

    func_bind_class(vm, vm -> object_class, "!", obj_not);
    func_bind_class(vm, vm -> object_class, "==(_)", obj_equal);
    func_bind_class(vm, vm -> object_class, "!=(_)", obj_not_equal);

    vm -> class_class = new BaseClass(vm, "__class__", 0);
    
    BaseClass *obj_meta_class = new BaseClass(vm, "__obj_meta__", 0);
    bind_super_class(obj_meta_class, vm -> class_class);

    vm -> object_class -> cls = obj_meta_class;
    obj_meta_class -> cls = vm -> class_class;
    vm -> class_class -> cls = nullptr;
}
