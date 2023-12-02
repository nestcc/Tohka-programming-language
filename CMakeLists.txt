cmake_minimum_required (VERSION 3.0.0)

project(Tohka)

#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -glldb")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g")

set(BUILD_DIR .)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (DEBUG)
    SET(CMAKE_BUILD_TYPE "Debug")
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -DNDEBUG")
endif ()

set(TOHKA_LINK_LIBS
        Includes
        Token
        Object
        Parser
        Symbol
        Compiler
        VM)

add_subdirectory(${PROJECT_SOURCE_DIR}/includes)
add_subdirectory(${PROJECT_SOURCE_DIR}/token)
add_subdirectory(${PROJECT_SOURCE_DIR}/object)
add_subdirectory(${PROJECT_SOURCE_DIR}/parser)
add_subdirectory(${PROJECT_SOURCE_DIR}/symbol)
add_subdirectory(${PROJECT_SOURCE_DIR}/compiler)
add_subdirectory(${PROJECT_SOURCE_DIR}/vm)
add_subdirectory(${PROJECT_SOURCE_DIR}/cli)
