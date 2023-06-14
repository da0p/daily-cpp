cmake_minimum_required(VERSION 3.21)
project(DailyCpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

add_executable(functional_count_lines
    functional_count_lines.cpp
)

add_executable(lambda_capture_global_var
    lambda_capture_global_var.cpp
)

add_executable(lambda_fold_expression
    lambda_fold_expression.cpp
)

add_executable(lambda_iife_invoke
    lambda_iife_invoke.cpp
)

add_executable(lambda_with_async
    lambda_with_async.cpp
)

add_executable(lambda_with_thread
    lambda_with_thread.cpp
)

add_executable(string_find_last_of
    string_find_last_of.cpp
)
