/*
 * @Author: Nestcc
 * @Date: 2021-03-12 16:19:21
 * @LastEditors: Nestcc
 * @LastEditTime: 2022-01-24 01:59:07
 * @Description:  < file content >
 */

#include "core/vm.h"

#include <sys/stat.h>

#include <algorithm>
#include <cstdint>

#include "compiler/compiler.h"
#include "compiler/headers.h"
#include "object/base_class.h"
#include "object/obj_closure.h"
#include "object/obj_function.h"
#include "object/obj_map.h"
#include "object/obj_module.h"
#include "object/obj_thread.h"
#include "object/value.h"
#include "core/core_script.h"
#include "core/primitive_methods.h"

VM::VM() : allocated_byte(0), curr_parser(nullptr), all_objects(nullptr) {
    all_modules = new ObjMap(this);
    _build_core();
}

VM::~VM() {
    // delete curr_parser;

    ObjHeader *curr_obj = all_objects;
    ObjHeader *tmp;
    while (curr_parser != nullptr) {
        tmp = curr_obj;
        curr_obj = curr_obj -> next;
        curr_obj -> prev = nullptr;
        delete tmp;
    }
    // delete all_objects;
    delete str_cls;
    delete func_cls;
    delete class_of_class;
    delete object_class;
    delete string_class;
    delete map_class;
    delete range_class;
    delete list_class;
    delete null_class;
    delete bool_class;
    delete num_class;
    delete fn_class;
    delete thread_class;
    delete all_modules;
    delete curr_thread;

    all_method_name.clear();
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
        obj->next = obj->prev = obj;
        all_objects = obj;
        obj_cnt += 1;
        return;
    }
    obj->prev = all_objects->prev;
    obj->next = all_objects;
    obj->prev->next = obj;
    obj->next->prev = obj;
    all_objects = obj;
    obj_cnt += 1;
}

void VM::remove_object(ObjHeader *obj) {
    if (obj_cnt == 0) {
        MEM_ERROR("object () not in vm.", obj->type);
        return;
    }
    if (obj_cnt == 1) {
        all_objects = nullptr;
        obj_cnt = 0;
        return;
    }
    if (obj == all_objects) {
        all_objects = all_objects->next;
    }
    obj->prev->next = obj->next;
    obj->next->prev = obj->prev;
    obj->next = obj->prev = nullptr;
    obj_cnt -= 1;
}

uint64_t VM::get_method_index(const std::string &name) {
    return std::find(all_method_name.begin(), all_method_name.end(), name) -
           (all_method_name.begin());
}

char *VM::read_file(const char *fpath) {
    FILE *srcf = fopen(fpath, "r");

    if (srcf == nullptr) {
        IO_ERROR(RED "Cannot open file %s.\n" NOCOLOR, fpath);
        exit(EXIT_FAILURE);
    }

    struct stat file_status {};
    stat(fpath, &file_status);
    size_t fsize = file_status.st_size;
    char *fcontent = (char *)malloc(sizeof(char) * (fsize + 5));

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

ObjModule *VM::_get_module(Value *module_name) {
    Value *val = this->all_modules->get_item(*module_name);
    if (val == nullptr || val->type == VT_UNDEFINED) {
        return nullptr;
    }
    return dynamic_cast<ObjModule *>(val->obj_header);
}

ObjThread *VM::_load_module(Value *module_name, const char *module_code) {
    ObjModule *module = _get_module(module_name);

    if (module == nullptr) {
        auto *obj_str_module_name = dynamic_cast<ObjString *>(module_name->obj_header);

        module = new ObjModule(this, obj_str_module_name->value);
        all_modules->add_item(*module_name, Value(dynamic_cast<ObjHeader *>(module)));

        auto *core_module_name = new Value(VT_NULL);
        ObjModule *core_module = _get_module(core_module_name);
        delete core_module_name;

        if (core_module == nullptr) {
            COMPILE_ERROR(nullptr, "Cannot find core module.");
        }

        for (uint64_t index = 0; index < core_module->module_var_name.size(); index += 1) {
            module->define_value(core_module->module_var_name[index],
                               &core_module->module_var_value[index]);
        }
    }

    ObjFunction *obj_fn = module->compile_module(module_code);
    auto *obj_closure = new ObjClosure(this, obj_fn);
    auto *obj_thread = new ObjThread(this, obj_closure);
    return obj_thread;
}

void VM::_build_core() {
    auto *core_module = new ObjModule(this, "__core_module__");
    all_modules = new ObjMap(this);
    all_modules->add_item(Value(VT_NULL), Value(core_module));

    object_class = new BaseClass(this, "__object__", 0);
    core_module -> define_value("__object__", new Value(core_module));

    object_class->bind_func("!", obj_not);
    object_class->bind_func("==(_)", obj_equal);
    object_class->bind_func("!=(_)", obj_not_equal);
    object_class->bind_func("type", obj_type);
    object_class->bind_func("type_name", obj_type_name);
    object_class->bind_func("super_type", obj_super_type);

    class_of_class = new BaseClass(this, "__class__", 0);
    class_of_class->bind_func("type", obj_type);
    class_of_class->bind_func("type_name", obj_type_name);
    class_of_class->bind_func("super_type", obj_super_type);

    auto *obj_meta_class = new BaseClass(this, "__obj_meta__", 0);
    obj_meta_class -> bind_super_class(class_of_class);

    object_class->cls = obj_meta_class;
    obj_meta_class->cls = class_of_class;
    class_of_class->cls = nullptr;

    auto *core_module_name = new Value(VT_NULL);
    core_module_name -> execute_module(core_module_code);
}
