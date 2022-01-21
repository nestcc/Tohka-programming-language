# where to put generated libraries
set(LIBRARY_OUTPUT_PATH "${BUILD_DIR}/src/object")

# where to put generated binaries
set(EXECUTABLE_OUTPUT_PATH "${BUILD_DIR}/src/object")

add_library(VM
        primitive_methods.cpp
        vm.cpp)
