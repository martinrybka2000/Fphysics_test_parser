cmake_minimum_required(VERSION 3.0.0)
project(Fphyscs_test_my_parser VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Fphyscs_test_my_parser main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
