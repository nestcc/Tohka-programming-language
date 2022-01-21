# where to put generated libraries
set(LIBRARY_OUTPUT_PATH "${BUILD_DIR}")

# where to put generated binaries
set(EXECUTABLE_OUTPUT_PATH "${BUILD_DIR}")

add_executable(toh cli.cpp)

target_link_libraries(toh ${TOHKA_LINK_LIBS})

