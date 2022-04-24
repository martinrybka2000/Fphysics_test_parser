cmake_minimum_required(VERSION 3.0.0)
project(Fphyscs_test_my_parser VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CTest)
enable_testing()

add_executable(Fphyscs_test_my_parser 
    main.cpp 
    node.cpp 
    operations.cpp 
    functions.cpp 
    expression_visualizer.cpp 
    expression_parser.cpp 
    expression_composer.cpp 
    utils.cpp
    expression_simplifier.cpp
    equation_parser.cpp)

link_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)