# where to put generated libraries
set(LIBRARY_OUTPUT_PATH "${BUILD_DIR}")

add_library(Compiler
        compiler.cpp
        compiler_unit.cpp
        )
