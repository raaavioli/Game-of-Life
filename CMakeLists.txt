cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Game-of-Life VERSION 1.0)

include_directories(${PROJECT_SOURCE_DIR}/include)

#add_library(sparse_blas ${PROJECT_SOURCE_DIR}/src/nist_spblas.cc)

add_library(simulation_utils ${PROJECT_SOURCE_DIR}/src/simulation_utils.cpp)

add_executable(main ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(main PUBLIC simulation_utils)

add_subdirectory(googletest)

add_executable(simulation_test ${PROJECT_SOURCE_DIR}/test/simulation_test.cpp)
target_link_libraries(simulation_test gtest gtest_main simulation_utils)


set_target_properties(main simulation_test simulation_utils
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "lib/"
	LIBRARY_OUTPUT_DIRECTORY "lib/"
	RUNTIME_OUTPUT_DIRECTORY "bin/")
