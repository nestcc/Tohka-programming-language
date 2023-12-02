# where to put generated libraries
set(LIBRARY_OUTPUT_PATH "${BUILD_DIR}")

add_library(Core
        primitive_methods.cpp
        vm.cpp
        operand.cpp)
