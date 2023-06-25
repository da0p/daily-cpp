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

add_executable(algorithm_reduce
    algorithm_reduce.cpp
)

add_executable(algorithm_accumulate
    algorithm_accumulate.cpp
)

add_executable(string_trimming
    string_trimming.cpp
)

add_executable(algorithm_remove_if
    algorithm_remove_if.cpp
)

add_executable(algorithm_partition
    algorithm_partition.cpp
)

add_executable(stream_iterator
    stream_iterator.cpp
)

add_executable(quoted
    quoted.cpp
)

add_executable(misc_fib_cache
    misc_fib_cache.cpp
)

add_executable(misc_generalized_memoization
    misc_generalized_memoization.cpp
)

add_executable(misc_recursive_memoization
    misc_recursive_memoization.cpp
)

add_executable(range_views_filter
    range_views_filter.cpp
)

add_executable(range_sort
    range_sort.cpp
)