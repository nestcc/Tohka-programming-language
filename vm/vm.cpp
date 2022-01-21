/*
 * @Author: Nestcc
 * @Date: 2021-03-12 16:19:21
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-25 17:43:29
 * @Description:  < file content > 
 */

#include <cstdint>
#include <sys/stat.h>
#include <algorithm>
#include "vm/vm.h"
#include "vm/primitive_methods.h"
#include "compiler/headers.h"
#include "object/value.h"
#include "object/obj_map.h"
#include "object/obj_module.h"
#include "object/base_class.h"

VM *VM::_instance = nullptr;

VM::VM() : root_dir(nullptr), allocated_byte(0), curr_parser(nullptr), all_objects(nullptr) {}

VM *VM::instance() {
    if (_instance == nullptr) {
        _instance = new VM();
        _instance->_build_core();
    }
    return _instance;
}

uint64_t VM::realloc_memory(uint64_t old_size, uint64_t new_size) {
    allocated_byte += (new_size - old_size);
    return new_size - old_size;
}

uint64_t VM::alloc_memory(uint64_t new_size) {
    allocated_byte += new_size;
    return new_size;
}

void VM::add_object(ObjHeader *obj) {
    if (all_objects == nullptr) {
        obj -> next = obj -> prev = obj;
        all_objects = obj;
        obj_cnt += 1;
        return;
    }
    obj -> prev = all_objects -> prev;
    obj -> next = all_objects;
    obj -> prev -> next = obj;
    obj -> next -> prev = obj;
    all_objects = obj;
    obj_cnt += 1;
}

void VM::remove_object(ObjHeader *obj) {
    if (obj_cnt == 1) {
        MEM_ERROR("object () not in vm.", obj -> type);
        return;
    }
    if (obj_cnt == 1) {
        all_objects = nullptr;
        obj_cnt = 0;
        return;
    }
    if (obj == all_objects) {
        all_objects = all_objects -> next;
    }
    obj -> prev -> next = obj -> next;
    obj -> next -> prev = obj -> prev;
    obj -> next = obj -> prev = nullptr;
    obj_cnt -= 1;
}

uint64_t VM::get_method_index(const std::string &name) {
    return std::find(all_method_name.begin(), all_method_name.end(), name) - (all_method_name.begin());
}

char *VM::read_file(const char *fpath) {
    FILE *srcf = fopen(fpath, "r");

    if (srcf == nullptr) {
        IO_ERROR(RED "Cannot open file %s.\n" NOCOLOR, fpath);
        exit(EXIT_FAILURE);
    }

    struct stat file_status{};
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

VM::VmResult VM::exec_module(Value *module_name, const char *module_code) {
    return VM::VmResult::VM_RESULT_ERROR;
}

uint64_t VM::_define_module_value(ObjModule *obj_module, std::string name, Value *val) {
    if (name.size() > MAX_ID_LEN) {
        if (curr_parser != nullptr) {
            COMPILE_ERROR(curr_parser, "Identifier %s is longer than MAX_ID_LEN(%d)",
                          name.c_str(), MAX_ID_LEN);
        }
        else {
            MEM_ERROR("Identifier %s is longer than MAX_ID_LEN(%d)",
                      name.c_str(), MAX_ID_LEN);
        }
    }

    // std::string module_name(name, length);
    uint64_t symbol_index = get_method_index(name);
    if (symbol_index == obj_module -> module_var_name.size()) {
        obj_module -> module_var_name.buff_add(name);
    }
    else if (obj_module -> module_var_value[symbol_index].type == VT_NULL) {
        obj_module -> module_var_value[symbol_index] = *val;
    }
    else {
        symbol_index = -1;
    }
    return symbol_index;
}

void VM::_bind_method(BaseClass *base_class, uint64_t index, method *pMethod) {
    if (index >= base_class -> methods.size()) {
        base_class -> methods.fill_wirte(method(), index - base_class -> methods.size() + 1);
    }
    base_class -> methods[index] = *pMethod;
}

void VM::_func_bind_class(BaseClass *base_cls, const std::string &method_name, Primitive prim_func) {
    if (method_name.empty()) {
        COMPILE_ERROR(nullptr, "method_name is empty.");
        return;
    }
    else if (prim_func == nullptr) {
        COMPILE_ERROR(nullptr, "primitive function is nullptr.");
        return;
    }

    uint64_t global_index = get_method_index(method_name);
    auto *pMethod = new method();
    pMethod -> prim_func = prim_func;
    pMethod -> type = MT_PRIMITIVE;
    _bind_method(base_cls, global_index, pMethod);
}

void VM::_bind_super_class(BaseClass *sub_class, BaseClass *super_class) {
    sub_class -> super_class = super_class;
    sub_class -> field_num += super_class -> field_num;
    for (uint64_t idx = 0; idx < super_class -> methods.size(); idx += 1) {
        _bind_method(sub_class, idx, &(super_class -> methods[idx]));
    }
}

void VM::_build_core() {
    auto *core_module = new ObjModule(this, "__core_module__");
    all_modules = new ObjMap(this);
    all_modules -> add_item(Value(VT_NULL), Value(core_module));

    object_class = new BaseClass(this, "__object__", 0);
    _define_module_value(core_module, "__object__", new Value(core_module));

    _func_bind_class(object_class, "!", obj_not);
    _func_bind_class(object_class, "==(_)", obj_equal);
    _func_bind_class(object_class, "!=(_)", obj_not_equal);
    _func_bind_class(object_class, "type", obj_type);
    _func_bind_class(object_class, "type_name", obj_type_name);
    _func_bind_class(object_class, "super_type", obj_super_type);

    class_of_class = new BaseClass(this, "__class__", 0);
    _func_bind_class(class_of_class, "type", obj_type);
    _func_bind_class(class_of_class, "type_name", obj_type_name);
    _func_bind_class(class_of_class, "super_type", obj_super_type);

    auto *obj_meta_class = new BaseClass(this, "__obj_meta__", 0);
    _bind_super_class(obj_meta_class, class_of_class);

    object_class -> cls = obj_meta_class;
    obj_meta_class -> cls = class_of_class;
    class_of_class -> cls = nullptr;
}

