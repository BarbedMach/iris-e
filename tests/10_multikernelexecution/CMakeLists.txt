cmake_minimum_required(VERSION 3.25)

project(example)

set(IRIS_ENHANCED_INSTALL_DIR /cta/users/fozdemir/dev/local_pckgs/usr/local)



add_library(OpenMPKernel SHARED kernel.openmp.h kernel.openmp.c)
target_include_directories(OpenMPKernel PRIVATE ${IRIS_ENHANCED_INSTALL_DIR}/include)
target_link_directories(OpenMPKernel PRIVATE ${IRIS_ENHANCED_INSTALL_DIR}/lib)
target_link_libraries(OpenMPKernel PRIVATE iris)
set_target_properties(OpenMPKernel PROPERTIES PREFIX "")
set_target_properties(OpenMPKernel PROPERTIES OUTPUT_NAME "kernel.openmp.so")
set_target_properties(OpenMPKernel PROPERTIES SUFFIX "")

add_executable(test test10_multikernelexecution.c)

target_include_directories(test PRIVATE ${IRIS_ENHANCED_INSTALL_DIR}/include)
target_link_directories(test PRIVATE ${IRIS_ENHANCED_INSTALL_DIR}/lib)
target_link_libraries(test PRIVATE iris)