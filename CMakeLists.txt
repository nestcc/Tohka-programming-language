cmake_minimum_required (VERSION 3.0.0)

project(Tohka)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCE_DIR)

aux_source_directory(${PROJECT_SOURCE_DIR}/client CLI_DIR)
aux_source_directory(${PROJECT_SOURCE_DIR}/includes INCLUDE_DIR)
aux_source_directory(${PROJECT_SOURCE_DIR}/vm VM_DIR)
aux_source_directory(${PROJECT_SOURCE_DIR}/parser PARSER_DIR)
aux_source_directory(${PROJECT_SOURCE_DIR}/gc GC_DIR)
aux_source_directory(${PROJECT_SOURCE_DIR}/object OBJECT_DIR)
aux_source_directory(${PROJECT_SOURCE_DIR}/compiler COMPILER_DIR)


add_executable(toh ${CLI_DIR} ${INCLUDE_DIR} ${VM_DIR} ${PARSER_DIR})
