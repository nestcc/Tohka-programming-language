cmake_minimum_required (VERSION 3.0.0)

project(Tohka)

#SET(CMAKE_BUILD_TYPE "Debug")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -glldb")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCE_DIR)

aux_source_directory(${PROJECT_SOURCE_DIR}/client CLI_DIR)
aux_source_directory(${PROJECT_SOURCE_DIR}/includes INCLUDE_DIR)
aux_source_directory(${PROJECT_SOURCE_DIR}/vm VM_DIR)
aux_source_directory(${PROJECT_SOURCE_DIR}/parser PARSER_DIR)
aux_source_directory(${PROJECT_SOURCE_DIR}/gc GC_DIR)
aux_source_directory(${PROJECT_SOURCE_DIR}/object OBJECT_DIR)
aux_source_directory(${PROJECT_SOURCE_DIR}/compiler COMPILER_DIR)

if (DEBUG)
    SET(CMAKE_BUILD_TYPE "Debug")
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -DNDEBUG")
endif ()

add_executable(toh  ${CLI_DIR}
                    ${INCLUDE_DIR}
                    ${VM_DIR}
                    ${PARSER_DIR}
                    ${OBJECT_DIR})
#                    ${GC_DIR}
#                    ${COMPILER_DIR})
