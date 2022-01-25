# where to put generated libraries
set(LIBRARY_OUTPUT_PATH "${BUILD_DIR}")

add_library(Symbol
        signature.cpp
        operator.cpp
        symbol_bind_rule.cpp)
