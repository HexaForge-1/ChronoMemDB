cmake_minimum_required(VERSION 3.15)
project(chrono_mem_db LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(chrono_mem_db
    src/main.cpp
    src/storage.cpp
    src/bptree.cpp
    src/transaction_manager.cpp
    src/query_parser.cpp
)

target_include_directories(chrono_mem_db PRIVATE ${CMAKE_SOURCE_DIR}/src)

enable_testing()
add_executable(basic_tests tests/basic_tests.cpp src/storage.cpp src/bptree.cpp src/transaction_manager.cpp src/query_parser.cpp)
target_include_directories(basic_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
add_test(NAME basic COMMAND basic_tests)
