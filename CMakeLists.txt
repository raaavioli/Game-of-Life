cmake_minimum_required(VERSION 3.10)

project(Game-of-Life VERSION 1.0)

include_directories(${PROJECT_SOURCE_DIR}/include)

#add_library(sparse_blas ${PROJECT_SOURCE_DIR}/src/nist_spblas.cc)

add_executable(main ${PROJECT_SOURCE_DIR}/src/main.cpp ${PROJECT_SOURCE_DIR}/src/simulation_utils.cpp)
#target_link_libraries(main PUBLIC sparse_blas)


set_target_properties(main #sparse_blas
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "lib/"
	LIBRARY_OUTPUT_DIRECTORY "lib/"
	RUNTIME_OUTPUT_DIRECTORY "bin/")
