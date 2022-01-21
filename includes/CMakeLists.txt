# where to put generated libraries
set(LIBRARY_OUTPUT_PATH "${BUILD_DIR}")

add_library(Includes
        utils.cpp
        unicode.cpp
        )
