# where to put generated libraries
set(LIBRARY_OUTPUT_PATH "${BUILD_DIR}")

add_library(Object
        object_header.cpp
        frame.cpp
        base_class.cpp
        obj_range.cpp
        obj_closure.cpp
        obj_function.cpp
        obj_instance.cpp
        obj_list.cpp
        obj_map.cpp
        obj_module.cpp
        obj_range.cpp
        obj_string.cpp
        obj_thread.cpp
        obj_upvalue.cpp
        value.cpp)
